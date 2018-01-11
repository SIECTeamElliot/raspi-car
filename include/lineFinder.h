#pragma once

#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <thread>
#include <mutex>

using namespace std;
using namespace cv;

//tuple<double, double, double> findLine(cv::Mat img);

class LineFinder {
public :
	LineFinder():isRaspberry(false), counter(0), camera(){
		init();
	}

	int counter;

	void test() {
		Mat srcFrame;
		while (true)
		{
			camera.read(srcFrame);
			imshow("camera",srcFrame);
			counter++;
			if (waitKey(1) == 27)
				break;
		}
	}

	thread run() {
		return thread([this] { this->_run(); });
	}

	void stop() {
		// TODO : clean stop
		// TODO : close camera
		running = false;
	}

	thread spawn() {
		return thread([this] { this->test(); });
	}
	
	

	tuple<double, double, double> getLastResult();

protected:
	tuple<double, double, double> lastResult;
	int width;
	int height;
	int heightCropped;
	Rect subSize;
	VideoCapture camera;
	bool isRaspberry;
	bool running;
	void init();
	// TODO : split into pieces w/ attributes
	void _run();
	tuple<double, double, double> sampleList[5];

	mutex mut_lastResult;

	

};
