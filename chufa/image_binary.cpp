#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;

using namespace cv;


//这里主要介绍关于YCbCr的颜色空间，将RGB颜色空间转化到YCbCr颜色空间中，然后将YCbCr颜色空间进行分割，对每一个通道的色彩进行研究
void image_binary(Mat &image_input, Mat &image_bin)
{
	//Mat型矩阵，变量表示为一个图像
	Mat Y, Cr, Cb;
	//这里的vector<int>可以看成是数组的意思
	vector<Mat> channels;
	/*转换颜色YCrCb空间并分割颜色通道*/
	//运用opencv库中的函数将颜色空间从RGB转化到YCbCr中
	cvtColor(image_input, image_input, CV_BGR2YCrCb);

	//将颜色YCbCr颜色空间进行分割,划分为三个通道Y通道，Cb通道和Cr通道
	split(image_input, channels);
	Y = channels.at(0);//Y表示亮度
	Cr = channels.at(1);//Cr表示红色
	Cb = channels.at(2);//Cb表示绿色

	//GaussianBlur(Cr, Cr, Size(5, 5), 0, 0);

	//threhold(输入图像，输出图像，小于阈值时输出像素值，大于阈值时候输出像素值，参数：指定二值化的方法);
	//该函数是在opencv的库中有实现的，调用即可
	threshold(Cr, image_bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//对Cr采用otsu算法进行分离
}