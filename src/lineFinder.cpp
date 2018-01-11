
//#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

#include <math.h>
#include <vector>
#include <ctime>
#include <iostream>

#include "lineFinder.h"

using namespace cv;
using namespace std;
#define ISRASPBERRY 0
#define DOWN_SECTION 1.0
#define DISPLAY_ON	0


tuple<double, double, double> linReg(vector<int> & vect, int width, int height);



void LineFinder::init() {

	// camera detection
	camera.open(1); 
	if (!camera.isOpened()) {
		cout << "cannot oppen windows camera : must be raspberry" << endl;
		isRaspberry = true;
		camera.open(0);
		if (!camera.isOpened()) {
			cout << "cannot oppen any camera camera :" << endl;
		}
	}
	// image dimensions 
	Mat srcI;
	camera.read(srcI);
	height = srcI.size().height;
	width = srcI.size().width;
	heightCropped = int(height * DOWN_SECTION);
	subSize = Rect(0, height - heightCropped, width, heightCropped - 1);
}

void LineFinder::_run() {
	if (!camera.isOpened()) {
		cout << "unable to run with no camera" << endl;
		return;
	}
	Mat srcI, trimI, bluredI, csvI, threshI, maxI;

	// kernel definition : used to blur the image along a single line 
	Point anchor(-1, -1);
	double delta = 0;
	int ddepth = -1;
	int kernel_size = (width / 8) * 2 + 1; // ensures odd number
	Mat kernel = getGaussianKernel(kernel_size, -1); // TODO : pyramid shaped objects
	kernel.convertTo(kernel, -1, 50, 0);
	transpose(kernel, kernel);

	if (running)
	{
		cout << "Already running" << endl;
		return;
	}
	running = true;
	while (running)
	{
		camera.read(srcI);

		// image subsizing
		trimI = srcI(subSize);

		// gaussian blur to smooth out noise
		GaussianBlur(trimI, bluredI, Size(9, 9), 0, 0);

		// convert to HSV color space
		cvtColor(bluredI, csvI, CV_BGR2HSV);

		// threshold for a color
		inRange(csvI, cv::Scalar(0, 0, 150), cv::Scalar(255, 63, 255), threshI);

		//decrease the contrast to avoid saturation
		threshI.convertTo(threshI, -1, 1.0 / 255.0, 0);

		// personalized gaussian filter
		filter2D(threshI, maxI, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

		int nRows = maxI.rows;
		int nCols = maxI.cols *  maxI.channels();
		int row, col;
		uchar* p;
		vector<int> maximums(trimI.rows, 0);
		for (row = 0; row < nRows; ++row)
		{
			maximums[row] = -1;
			uchar maxValue = 25;
			p = maxI.ptr<uchar>(row);
			for (col = 0; col < nCols; ++col)
			{
				if (maxValue < p[col]) {
					maxValue = p[col];
					maximums[row] = col;
				}
			}
		}

		// linear regression
		tuple <double, double, double> coefs = linReg(maximums, width, height);
		Point pt1((int)get<1>(coefs), 0);
		int origin = int(nRows* get<0>(coefs) + get<1>(coefs));
		Point pt2(origin, nRows);
		double angle = atan(get<0>(coefs));

		// display line
		//cout << "coefs : " << coefs.first << ", " << coefs.second << endl;
		//line(bluredI, pt1, pt2, Scalar(255, 0, 0));
		Point offset(0, int((1.0 - DOWN_SECTION) * height));
		line(srcI, pt1 + offset, pt2 + offset, Scalar(255, 0, 0), 2);

		// display text
		double origin_d = 2.0 * (double(origin) - double(width) / 2) / double(width);
		double angle_d = -180.0 * angle / 3.14159;
		int direction = 0;
		if (origin_d > 0.2)
			direction++;
		else if (origin_d < -0.2)
			direction--;
		if (angle_d > 10.0)
			direction++;
		else if (angle_d < -10.0)
			direction--;

#if (DISPLAY_ON == 1)
		Point textOrigin(10, 20);
		if (direction == 0) {
			putText(srcI, "Forward", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0));
		}
		else if (direction > 0) {
			putText(srcI, "Turn Right", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
		}
		else {
			putText(srcI, "Turn Left", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
		}
		textOrigin.x = 100;
		stringstream stream;
		stream << fixed << setprecision(2) << get<2>(coefs);
		string s = stream.str();
		putText(srcI, s, textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));

		imshow("source", srcI);

#endif // (DISPLAY_ON == 1)


		mut_lastResult.lock();
		lastResult = tuple<double, double, double>(origin_d, angle_d, get<2>(coefs));
		mut_lastResult.unlock();


		/*if (waitKey(1) == 27)
			break;*/
	}
	cout << "stopped" << endl;
	camera.release();
}




tuple<double, double, double> LineFinder::getLastResult() {
	mut_lastResult.lock();
	tuple<double, double, double> last = lastResult;
	mut_lastResult.unlock();
	return last;
}


// Compute the linear regression fit of the given vector
// Returns a pair conataining the slope and offset of the line
// the data are raw : they are based directly on pixel coordinates
tuple<double, double, double> linReg(vector<int> & vect, int width, int height){
	int n = 0;
	double a, b;
	double xsum = 0, x2sum = 0, ysum = 0, xysum = 0;		//variables for sums/sigma of xi,yi,xi^2,xiyi etc

	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i] > 0) {
			xsum = xsum + (double)i;						//calculate sigma(xi)
			ysum = ysum + (double)vect[i];					//calculate sigma(yi)
			x2sum = x2sum + pow((double)i, 2);				//calculate sigma(x^2i)
			xysum = xysum + (double)i * (double)vect[i];	//calculate sigma(xi*yi)
			n++;
		}
	}
	double yavg = ysum / (double)n;
	double SStot = 0;
	double SSreg = 0;
	a = (n*xysum - xsum*ysum) / (n*x2sum - xsum*xsum);		//calculate slope
	b = (x2sum*ysum - xsum*xysum) / (x2sum*n - xsum*xsum);	//calculate intercept


	// r calculation 
	double R = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		if (abs(vect[i] - (a*i + b)) < width / 10)
			R++;
	}
	R = R / height;
	/*
	for (int i = 0; i < vect.size(); i++)
	{
		if (vect[i] > 0) {
			SStot += pow((double)vect[i] - yavg, 2);
			SSreg += pow((double)vect[i] - (a*i + b), 2);
		}
	}
	//double R2 = 1 - (SSreg / SStot);
	R = SSreg/n;
	*/
	return tuple<double, double, double>(a, b, R);
}

/*
tuple<double, double, double> findLine(Mat img) {

	Mat trimI, bluredI, csvI, threshI, maxI;

	// Trimming to extract the lower part of the image
	int height = img.size().height;
	int width = img.size().width;
	Rect subSize(0, (1.0 - DOWN_SECTION) * height, width, height * DOWN_SECTION - 1);
	trimI = img(subSize);

	// gaussian blur to smooth out noise
	GaussianBlur(trimI, bluredI, Size(9, 9), 0, 0);

	// convert to HSV color space
	cvtColor(bluredI, csvI, CV_BGR2HSV);

	// threshold for a color
	inRange(csvI, cv::Scalar(0, 0, 150), cv::Scalar(255, 63, 255), threshI);

	//decrease the contrast
	threshI.convertTo(threshI, -1, 1.0 / 255.0, 0);

	// kernel definition : used to blur the image along a single line 
	Point anchor(-1, -1);
	double delta = 0;
	int ddepth = -1;
	int kernel_size = (width / 8) * 2 + 1; // ensures odd number
	Mat kernel = getGaussianKernel(kernel_size, -1); // TODO : pyramid shaped objects
	kernel.convertTo(kernel, -1, 50, 0);
	transpose(kernel, kernel);

	// personalized gaussian filter
	filter2D(threshI, maxI, ddepth, kernel, anchor, delta, BORDER_DEFAULT);

	// Maximum detection for each line 
	CV_Assert(maxI.depth() == CV_8U);// accept only char type matrices
	int channels = maxI.channels();
	int nRows = maxI.rows;
	int nCols = maxI.cols * channels;
	int row, col;
	uchar* p;
	vector<int> maximums(trimI.rows, 0);
	for (row = 0; row < nRows; ++row)
	{
		maximums[row] = -1;
		uchar maxValue = 25;
		p = maxI.ptr<uchar>(row);
		for (col = 0; col < nCols; ++col)
		{
			if (maxValue < p[col]) {
				maxValue = p[col];
				maximums[row] = col;
			}
		}
	}

	// linear regression
	tuple <double, double, double> coefs = linReg(maximums);
	Point pt1(get<1>(coefs), 0);
	int origin = nRows* get<0>(coefs) + get<1>(coefs);
	Point pt2(origin, nRows);
	double angle = atan(get<0>(coefs));

	// display line
	//cout << "coefs : " << coefs.first << ", " << coefs.second << endl;
	//line(bluredI, pt1, pt2, Scalar(255, 0, 0));
	Point offset(0, (1.0 - DOWN_SECTION) * height);
	line(img, pt1 + offset, pt2 + offset, Scalar(255, 0, 0), 2);

	// display text
	double origin_d = 2.0 * (double(origin) - double(width) / 2) / double(width);
	double angle_d = -180.0 * angle / 3.14159;
	int direction = 0;
	if (origin_d > 0.2)
		direction++;
	else if (origin_d < -0.2)
		direction--;
	if (angle_d > 10.0)
		direction++;
	else if (angle_d < -10.0)
		direction--;

#if (DISPLAY_ON == 1)
	Point textOrigin(10, 20);
	if (direction == 0) {
		putText(img, "Forward", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 0, 0));
	}
	else if (direction > 0) {
		putText(img, "Turn Right", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0));
	}
	else {
		putText(img, "Turn Left", textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
	}
	textOrigin.x = 100;
	stringstream stream;
	stream << fixed << setprecision(2) << get<2>(coefs);
	string s = stream.str();
	putText(img, s, textOrigin, CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));

	imshow("source", img);
	//imshow("blur", bluredI);
	//imshow("out", maxI);
#endif // (DISPLAY_ON == 1)



	return tuple<double, double, double>(origin_d, angle_d, get<2>(coefs));
}

*/
