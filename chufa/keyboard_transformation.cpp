#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include<highgui.h>

using namespace std;
using namespace cv;

void keyboard_transformation(vector<Point> &point, Mat &image_input, Mat &image_output, Mat &tran)
{
	Point2f point_temp[4];
	float center_x,center_y;
	center_x = 0.5*(point[0].x + point[1].x);
	center_y = 0.5*(point[0].y + point[2].y);
	for (int i = 0; i < 4; i++)
	{
		if (point[i].x<center_x)
		{
			if (point[i].y < center_y)
			{
				point_temp[2] = point[i];
			}
			else if (point[i].y > center_y)
			{
				point_temp[0] = point[i];
			}
		}
		else if (point[i].x > center_x)
		{
			if (point[i].y < center_y)
			{
				point_temp[3] = point[i];
			}
			else if (point[i].y > center_y)
			{
				point_temp[1] = point[i];
			}
		}
	}

	Point2f point_keyboard[4];
	point_keyboard[0] = { 0, 450 };
	point_keyboard[1] = { 1000,450 };
	point_keyboard[2] = { 0, 0 };
	point_keyboard[3] = { 1000, 0 };

	tran = getPerspectiveTransform(point_temp, point_keyboard);

	warpPerspective(image_input, image_output, tran, image_output.size(), CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, 0);

}