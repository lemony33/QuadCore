#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{

	Mat img = imread("test_img.png", IMREAD_COLOR);
	imshow("image", img);
	waitKey(0);
	return 0;
}