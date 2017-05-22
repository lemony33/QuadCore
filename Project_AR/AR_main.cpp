#include <opencv2/opencv.hpp>
using namespace cv;


int main()
{

	Mat img = imread("test_img.png", IMREAD_COLOR);
	imshow("image", img);
	waitKey(0);
	return 0;
}