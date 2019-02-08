#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void fingertip_image(vector<vector<Point>> &contours, Mat &finger_input, Mat &finger_image, int index)
{
	Point2f point_temp;
	Mat fingertip;
	cvtColor(finger_input, fingertip, CV_BGR2GRAY,0);
	for (int i = 0; i < fingertip.cols; i++)
	{
		for (int j = 0; j < fingertip.rows; j++)
		{
			point_temp = { (float)i, (float)j };
			if (pointPolygonTest(contours[index], point_temp, 0) == 1)
			{
				finger_image.at<uchar>(j, i) = 0;//fingertip.at<uchar>(j, i);
			}
			else
			{
				finger_image.at<uchar>(j, i) = 255;
			}
		}
	}
}