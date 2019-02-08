#include <iostream>
#include <vector>
#include<windows.h>

#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void HSV_detector(Mat &frame, Mat &skinArea)
{
	Mat ycrcb_image;
	cvtColor(frame, ycrcb_image, CV_BGR2YCrCb); //首先转换成到YCrCb空间
	vector<Mat> channels;
	split(ycrcb_image, channels);
	skinArea = channels[1];
	threshold(skinArea, skinArea, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//dilate(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));
	//erode(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));

}
