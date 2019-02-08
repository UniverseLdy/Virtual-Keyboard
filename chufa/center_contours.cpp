#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void center_contours(vector<vector<Point> > &contours, vector<Point> &point)
{
	Moments moment[4];
	for (int i = 0; i < 4; i++)
	{
		moment[i] = moments(contours[i], true);
		Point center(moment[i].m10 / moment[i].m00, moment[i].m01 / moment[i].m00);
		point.push_back (center);
	}
}