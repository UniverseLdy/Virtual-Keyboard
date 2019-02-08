//本段代码采用了OpenCV库的Convex 函数对肤色分割后的手部图像进行凸包检测，计算出手部轮廓的形态学凸包位置并进行跟踪

#include <iostream>
#include <vector>
#include <windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;


//凸包检测（输入轮廓，输出凸包的点），函数中添加了相应的指尖映射值
void convexHull_detection(Mat &show_img, Mat &image_bin, vector<Point> &point, Point &fingertip, Point &center, vector<vector<Point>> contours, int index, bool &Flag_out, int &distant1)
{




	/*以下进行凸包检测并绘制，记住以下函数就可以了*/
	vector<vector<Point> >hull(1);//初始化一个向量，第一个索引为0
	// Int type hull  
	vector<vector<int>>hullsI(1);
	// Convexity defects  
	vector<vector<Vec4i>>defects(1);

	convexHull(Mat(contours[index]), hull[0], false);//该函数得到轮廓的凸包点并储存在hull里
	// find int type hull  
	convexHull(Mat(contours[index]), hullsI[0], false);
	// get convexity defects  
	convexityDefects(Mat(contours[index]), hullsI[0], defects[0]);

	//迭代器，用于对整个序列进行遍历
	vector<Vec4i>::iterator d = defects[0].begin();

	//最后在defects中保存的有相应的凸包位置

	while (d != defects[0].end())
	{
		Vec4i& v = (*d);
		int startidx = v[0];
		Point ptStart(contours[index][startidx]);// point of the contour where the defect begins  
		int endidx = v[1];
		Point ptEnd(contours[index][endidx]);// point of the contour where the defect ends  
		int faridx = v[2];
		Point ptFar(contours[index][faridx]);// the farthest from the convex hull point within the defect  
		int depth = v[3] / 256;// distance between the farthest point and the convex hull 
		
	//	if (depth > 50)
		//{

			if (fingertip.y > ptStart.y)
			{
				fingertip = ptStart;
			}
			//circle(image, ptStart, 4, Scalar(0, 0, 255), 2);
			//circle(input, ptEnd, 4, Scalar(255, 0, 100), 2);
			//circle(input, ptFar, 4, Scalar(100, 0, 255), 2);
		//}
		d++;
	}
	distant1 = (fingertip.x - center.x) * (fingertip.x - center.x) + (fingertip.y - center.y) * (fingertip.y - center.y);







	//以上通过凸包算法，得到所有指尖的位置

	//由相应点到中心点的x方向和y方向移动的距离来计算在键盘上的点的位置
	Point keyboard_center = { 500, 300 };
	Point point_center1 = { 320, 240 };
	Point _vector = { (fingertip.x - point_center1.x), (fingertip.y - point_center1.y) };
	Point point_keyboard = { (int)(keyboard_center.x + 2.2*_vector.x), (int)(keyboard_center.y + 2.2*_vector.y) };
	if (point_keyboard.x < 0)
		point_keyboard.x = 0;
	if (point_keyboard.y < 0)
		point_keyboard.y = 0;
	if (point_keyboard.x >1000)
		point_keyboard.x = 1000;
	if (point_keyboard.y > 600)
		point_keyboard.y = 600;


	point.push_back({ (1000 - point_keyboard.x), point_keyboard.y });

	//line(image, fingertip, couPoint[flag_fingertip + 20], Scalar(0, 0, 225));
	//line(image, fingertip, couPoint[flag_fingertip - 20], Scalar(0, 0, 225));
	//line(image, couPoint[flag_fingertip - 20], couPoint[flag_fingertip + 20], Scalar(0, 0, 225));

	////画圆圈的函数，用于在键盘上绘制一个小点进行表示指尖的位置
	/*circle(show_img, fingertip, 6, Scalar(0, 255, 0), CV_FILLED);*/

	//circle(image, couPoint[flag + 20], 5, Scalar(0, 0, 225), CV_FILLED);
	//circle(image, couPoint[flag - 20], 5, Scalar(0, 0, 225), CV_FILLED);

	//vector<Point> point_low;
	//int length = 70;		//用于判定矩形框大小用
	//int width = 100;
/*

	if ((fingertip.x - length) > 0 && (fingertip.x + length) < 640 && ((fingertip.y) + width) < 480)*/
	/*{*/
		//if (flag_in)
		//{
		//得到矩形框的四个位置点的坐标
			//point_low.push_back({ (fingertip.x - length), fingertip.y });
			//point_low.push_back({ (fingertip.x + length), fingertip.y });
			//point_low.push_back({ (fingertip.x - length), (fingertip.y) + width });
			//point_low.push_back({ (fingertip.x + length), (fingertip.y) + width });

		//绘制四根直线得到矩形框的图形
			//line(image, point_low[0], point_low[1], Scalar(0, 0, 225));
			//line(image, point_low[0], point_low[2], Scalar(0, 0, 225));
			//line(image, point_low[2], point_low[3], Scalar(0, 0, 225));
			//line(image, point_low[1], point_low[3], Scalar(0, 0, 225));


			//自行定义一个小矩形进行操作
			//由图中640X480，设置长为100，高度为80的矩形


			//计算矩形框中的手部区域的面积大小
			//int y0 = fingertip.y + width;
			//int y1 = fingertip.y;

			//if (y0 < y1)
			//{
			//	int temp = y0;
			//	y0 = y1;
			//	y1 = temp;
			//}

			//int x1 = fingertip.x - length, x2 = fingertip.x + length;

			////对列和行进行遍历，求出面积
			//for (int i1 = x1; (i1 < x2); i1++)
			//{
			//	for (int j1 = y1; j1 < y0; j1++)
			//	{
			//		if ((image_bin.at<uchar>(j1, i1)) != 0)//判断每个点的像素是否为0，不为0则进行计数操作，最终计数的大小即为面积的大小
			//		{
			//			countArea1 = countArea1 + 1;
			//		}
			//	}
			//}

			//

			//采用单纯的对countArea进行阈值判定，发现阈值得到的效果中误触很大，采取新的触发方法，判定相邻两帧图像中countArea的差值大小来进行判定
			//在image watch中对像素进行分析得到比较好的阈值
			//if (countArea1>5000)
			//{
			//	Flag_out = true;//Flag_out 表示的标志是输入
			//}
		}

		
	//}
		
//}

