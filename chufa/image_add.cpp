#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void image_add(Mat image_background, Mat image2, Mat &image_add)
{
	Mat finger_add, image_backgray;
	image_backgray.create(image_background.size(), 0);
	float alpha = 0.4;
	float beta = 1 - alpha;
	finger_add.create(image_background.size(), 0);

	for (int i = 0; i < image2.cols; i++)
	{
		for (int j = 0; j < image2.rows; j++)
		{
			finger_add.at<uchar>(j, i) = image2.at<uchar>(j, i);
		}
	}

	cvtColor(image_background, image_backgray, CV_BGR2GRAY);
	addWeighted(finger_add, alpha, image_backgray, beta, 0, image_add);
}