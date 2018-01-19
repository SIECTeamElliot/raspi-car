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

    thread capture() {
        return thread([this] { this->_capture(); });
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
	double getLastCommand();

protected:
	tuple<double, double, double> lastResult;
	bool isRaspberry;
	bool running;
	double lastCommand;
	int width;
	int height;
	int heightCropped;
	int counter;
	Rect subSize;
	VideoCapture camera;
    Mat lastImage;
	void init();
	void _run();
    void _capture();
	tuple<double, double, double> sampleList[5];

	mutex mut_lastResult;

	

};
