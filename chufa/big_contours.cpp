#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

//�õ���Ӧ�������������бȽϣ�������������ȡ����
void big_contours(Mat &image_input, vector<vector<Point> > &contours, int &index)
{
	double area, maxArea(0);
	for (int i = 0; i < contours.size(); i++)
	{
		//opencv��������������ĺ���
		area = contourArea(Mat(contours[i]));

		if (area > maxArea)
		{
			maxArea = area;
			index = i;
		}
	}

	//���������ĺ���
//	drawContours(image_input, contours, index, Scalar(0, 0, 255), 4);
}