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

void skinExtract(const Mat &frame, Mat &skinArea,int&i)
{ 
	Mat YCbCr;
	vector<Mat> planes;
	int i1 =(i - 2);
	//转换为YCrCb颜色空间    
	cvtColor(frame, YCbCr, CV_RGB2YCrCb);
	//将多通道图像分离为多个单通道图像    
	split(YCbCr, planes);

	//运用迭代器访问矩阵元素    
	MatIterator_<uchar> it_Cb = planes[1].begin<uchar>(),
		it_Cb_end = planes[1].end<uchar>();
	MatIterator_<uchar> it_Cr = planes[2].begin<uchar>();
	MatIterator_<uchar> it_skin = skinArea.begin<uchar>();

	//人的皮肤颜色在YCbCr色度空间的分布范围:100<=Cb<=127, 138<=Cr<=170    
	for (; it_Cb != it_Cb_end; ++it_Cr, ++it_Cb, ++it_skin)
	{
		if ((154-i) <= *it_Cr &&  *it_Cr <= (154+i) && (114-i1) <= *it_Cb &&  *it_Cb <= (114+i1))
			*it_skin = 255;
		else
			*it_skin = 0;
	}
	
	//膨胀和腐蚀，膨胀可以填补凹洞（将裂缝桥接），腐蚀可以消除细的凸起（“斑点”噪声）    
	dilate(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));
	erode(skinArea, skinArea, Mat(5, 5, CV_8UC1), Point(-1, -1));
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));   // 开运算去除噪点
	morphologyEx(skinArea, skinArea, MORPH_OPEN, element);


}