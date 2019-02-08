#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

//image(����ͼ�����ں��������������ֵ��ͼ�����ڲ��ҳ�������ֵ�����ҳ���������)
void image_contours(Mat &image_bin, vector<vector<Point> > &contours)
{
	vector<Vec4i> hierarchy;
	//findcontours(����Ķ�ֵ��ͼ�����������ͼ��...)
	findContours(image_bin, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	/*for (int i = 0; i < contours.size(); i++)
	{
		drawContours(image_input, contours, i, Scalar(0, 0, 255), 4, 8, hierarchy);
	}*/
}