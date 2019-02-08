#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void image_enrode_dilate(Mat &image_input, Mat &image_result)
{
	//腐蚀膨胀的参数
	Mat element = getStructuringElement(MORPH_RECT, Size(4, 4));
	//进行腐蚀膨胀的操作，可以滤掉一些噪点
	erode(image_input, image_input, element);			
	dilate(image_input, image_result, element);
}