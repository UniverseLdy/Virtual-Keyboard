#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;

using namespace cv;


//������Ҫ���ܹ���YCbCr����ɫ�ռ䣬��RGB��ɫ�ռ�ת����YCbCr��ɫ�ռ��У�Ȼ��YCbCr��ɫ�ռ���зָ��ÿһ��ͨ����ɫ�ʽ����о�
void image_binary(Mat &image_input, Mat &image_bin)
{
	//Mat�;��󣬱�����ʾΪһ��ͼ��
	Mat Y, Cr, Cb;
	//�����vector<int>���Կ������������˼
	vector<Mat> channels;
	/*ת����ɫYCrCb�ռ䲢�ָ���ɫͨ��*/
	//����opencv���еĺ�������ɫ�ռ��RGBת����YCbCr��
	cvtColor(image_input, image_input, CV_BGR2YCrCb);

	//����ɫYCbCr��ɫ�ռ���зָ�,����Ϊ����ͨ��Yͨ����Cbͨ����Crͨ��
	split(image_input, channels);
	Y = channels.at(0);//Y��ʾ����
	Cr = channels.at(1);//Cr��ʾ��ɫ
	Cb = channels.at(2);//Cb��ʾ��ɫ

	//GaussianBlur(Cr, Cr, Size(5, 5), 0, 0);

	//threhold(����ͼ�����ͼ��С����ֵʱ�������ֵ��������ֵʱ���������ֵ��������ָ����ֵ���ķ���);
	//�ú�������opencv�Ŀ�����ʵ�ֵģ����ü���
	threshold(Cr, image_bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//��Cr����otsu�㷨���з���
}