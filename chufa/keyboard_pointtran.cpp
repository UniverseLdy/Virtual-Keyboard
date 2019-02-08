#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void keyboard_pointtran(vector<Point> point_input, vector<Point> &point_output, Mat &tran)
{
	for (int index = 0; index < point_input.size(); index++)
	{
		Point point_temp;
		double w1 = (point_input[index].x)*(tran.at<double>(2, 0)) + (point_input[index].y)*(tran.at<double>(2, 1)) + (tran.at<double>(2, 2));
		point_temp.x = ((point_input[index].x)*(tran.at<double>(0, 0)) + (point_input[index].y)*(tran.at<double>(0, 1)) + tran.at<double>(0, 2)) / (w1);
		point_temp.y = ((point_input[index].x)*(tran.at<double>(1, 0)) + (point_input[index].y)*(tran.at<double>(1, 1)) + tran.at<double>(1, 2)) / (w1);

		//point_output[index].x = ((point_input[index].x)*(tran.at<double>(0, 0)) + (point_input[index].y)*(tran.at<double>(0, 1)) + tran.at<double>(0, 2)) / (w1);*/
		if (point_temp.x < 0)
		{
			point_temp.x = 0;
		}
		//point_output[index].y = ((point_input[index].x)*(tran.at<double>(1, 0)) + (point_input[index].y)*(tran.at<double>(1, 1)) + tran.at<double>(1, 2)) / (w1);
		if ((point_temp.y) < 0)
		{
			point_temp.y = 0;
		}
		point_output.push_back(point_temp);

	}
}