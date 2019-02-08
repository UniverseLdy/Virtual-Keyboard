#include<windows.h>  
#include <iostream>
#include <vector>


#include <highgui.h>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;

void k_fingertip(Mat &image, Mat &image_bin, vector<Point> &point, vector<vector<Point>> contours, int index, bool &Flag_out, bool &flag_in)
{
	
		//寻找指尖
		vector<Point> couPoint = contours[index];		//将最大的轮廓提取出来保存在couPoint中
		int max(0), count(0), notice(0);
		vector<Point> fingerTips;
		Point p, q, r, fingertip;			//p点为指尖所在点
		int min_y = 1000;
		int flag_fingertip;

		int K = 1;

		for (int i = 1; (i < (couPoint.size() - K)) && couPoint.size(); i++)
		{
			//采用K轮廓法来得到指尖
			q = couPoint[i - K];
			p = couPoint[i];
			r = couPoint[i + K];

			int dot = (q.x - p.x) * (q.y - p.y) + (r.x - p.x) * (r.y - p.y);
			if (dot < 20 && dot > -20)
			{
				int cross = (q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y);
				if (cross > 0)
				{
					if (min_y > p.y)
					{
						min_y = p.y;
						fingertip = p;
						flag_fingertip = i;
					}
				}
			}
		}


		point.push_back({ 1000 - (int)((fingertip.x)*1.5), (int)((fingertip.y)*1.5) });

		//line(image, fingertip, couPoint[flag_fingertip + 20], Scalar(0, 0, 225));
		//line(image, fingertip, couPoint[flag_fingertip - 20], Scalar(0, 0, 225));
		//line(image, couPoint[flag_fingertip - 20], couPoint[flag_fingertip + 20], Scalar(0, 0, 225));

		circle(image, fingertip, 5, Scalar(0, 225, 0), CV_FILLED);

		//circle(image, couPoint[flag + 20], 5, Scalar(0, 0, 225), CV_FILLED);
		//circle(image, couPoint[flag - 20], 5, Scalar(0, 0, 225), CV_FILLED);

		vector<Point> point_low;
		int length = 100;

		
		if ((fingertip.x - length) > 0 && (fingertip.x + length) < 640 && ((fingertip.y) + length) < 480)
		{
			if (flag_in)
			{
				point_low.push_back({ (fingertip.x - length), fingertip.y });
				point_low.push_back({ (fingertip.x + length), fingertip.y });
				point_low.push_back({ (fingertip.x - length), (fingertip.y) + length });
				point_low.push_back({ (fingertip.x + length), (fingertip.y) + length });


				line(image, point_low[0], point_low[1], Scalar(0, 0, 225));
				line(image, point_low[0], point_low[2], Scalar(0, 0, 225));
				line(image, point_low[2], point_low[3], Scalar(0, 0, 225));
				line(image, point_low[1], point_low[3], Scalar(0, 0, 225));


				//自行定义一个小矩形进行操作
				//由图中640X480，设置长为100，高度为80的矩形



				int y0 = fingertip.y + length;
				int y1 = fingertip.y;

				if (y0 < y1)
				{
					int temp = y0;
					y0 = y1;
					y1 = temp;
				}

				int x1 = fingertip.x - length, x2 = fingertip.x + length;


				int countArea = 0;

				for (int i1 = x1; (i1 < x2); i1++)
				{
					for (int j1 = y1; j1 < y0; j1++)
					{
						if ((image_bin.at<uchar>(j1, i1)) != 0)
						{
							countArea = countArea + 1;
						}
					}
				}

				//在image watch中对像素进行分析得到比较好的阈值
				if (countArea>5000)
				{
					Flag_out = true;
				}
			}
			//circle(image1, point[0], 5, Scalar(0, 225, 0), CV_FILLED);
		}
	flag_in = false;
}