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

void ellipse_detect(Mat &frame, Mat &skinArea)
{
	Mat img = frame.clone();
	Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
	//����opencv�Դ�����Բ���ɺ���������һ����ɫ��Բģ��
	ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 15.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
	Mat ycrcb_image;
	skinArea = Mat::zeros(img.size(), CV_8UC1);
	cvtColor(img, ycrcb_image, CV_BGR2YCrCb); //����ת���ɵ�YCrCb�ռ�
	for (int i = 0; i < img.cols; i++)   //������ԲƤ��ģ�ͽ���Ƥ�����
		for (int j = 0; j < img.rows; j++)
		{
			Vec3b ycrcb = ycrcb_image.at<Vec3b>(j, i);
			if (skinCrCbHist.at<uchar>(ycrcb[1], ycrcb[2]) > 0)   //���������Ƥ��ģ����Բ�����ڣ��õ����Ƥ�����ص�
				skinArea.at<uchar>(j, i) = 255;
		}
	//dilate(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));
	/*erode(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));*/
}
