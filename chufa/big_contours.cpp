#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

//得到相应的最大面积并进行比较，并将其索引提取出来
void big_contours(Mat &image_input, vector<vector<Point> > &contours, int &index)
{
	double area, maxArea(0);
	for (int i = 0; i < contours.size(); i++)
	{
		//opencv中求轮廓内面积的函数
		area = contourArea(Mat(contours[i]));

		if (area > maxArea)
		{
			maxArea = area;
			index = i;
		}
	}

	//绘制轮廓的函数
//	drawContours(image_input, contours, index, Scalar(0, 0, 255), 4);
}