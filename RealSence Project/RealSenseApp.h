#pragma once

#include <opencv2/opencv.hpp>
#include <pxcsession.h>


class RealSenseApp
{
public:
	RealSenseApp();
	virtual ~RealSenseApp();

	void initialize();
	void run();

	void updateFrame();
	bool showImage();
	void updateColorImage(PXCImage* colorFrame);

private:
	cv::Mat colorImage;
	PXCSenseManager* senseManager = nullptr;

	const int COLOR_WIDTH = 640;
	const int COLOR_HEIGHT = 480;
	const int COLOR_FPS = 30;

	//const int COLOR_WIDTH = 1920;
	//const int COLOR_HEIGHT = 1080;
	//const int COLOR_FPS = 30;
};

