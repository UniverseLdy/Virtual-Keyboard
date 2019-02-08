/*inlcude里面的意思就是把库函数包括进来
比如：include<stdio.h>，就是标准库*/
#include <iostream>//可以运用cin和cout函数
#include <vector>
#include <windows.h>

//以下包括的为opencv里面的库函数，用于后面一些函数和类型的直接运用
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#define WINDOW_NAME "【轨迹条测试窗口】"  

//图中keyboard的绿色表示未按下，红色表示按下
//键盘每个一秒钟进行触发判定，两次连续触发指尖必须相差一秒钟
//采用凸包检测以及两帧图像指尖坐标插值方法来减小指尖检测的跳变

//使用命名空间
using namespace std;
using namespace cv;

//在MFC中，这些函数都必须是在对话框的类中来进行实现，也就是说必须在类中的头文件中进行声明，在类的cpp文件中进行实现
void image_binary(Mat &image_input, Mat &image_bin);	//将图像进行二值化处理

void image_contours(Mat &image_bin, vector<vector<Point> > &contours);	//将二值化图像转化为边缘图像

void skinExtract(const Mat &frame, Mat &skinArea, int&i);

void ellipse_detect(Mat &frame, Mat &skinArea);

void center_contours(vector<vector<Point> > &contours, vector<Point> &point);	//在提取标准键盘时候用到的，可以不看

void keyboard_transformation(vector<Point> &point, Mat &image_input, Mat &image_output, Mat &tran);	//可以不看

void keyboard_detect(vector<Point> point, bool &flag, bool &key_shift);		//判断键位的输出

void keyboard_detect1(Point point, bool &flag, bool &uptoo);

void image_enrode_dilate(Mat &image_input, Mat &image_result);		//进行腐蚀膨胀操作

void big_contours(Mat &image_input, vector<vector<Point>> &contours, int &index);	//判断最大的轮廓，并得到相应的轮廓索引

void convexHull_detection(Mat &show_img, Mat &image_bin, vector<Point> &point, Point &fingertip, Point &center, vector<vector<Point>> contours, int index, bool &Flag_out, int &distant1);//凸包检测函数，检测指尖的位置

void k_fingertip(Mat &image, Mat &image1, vector<Point> &point, vector<vector<Point>> contours, int index,bool &Flag_out,bool &flag_in);//k向量判断指尖位置，可以不看

void keyboard_pointtran(vector<Point> point_input, vector<Point> &point_output, Mat &tran);//用于标准键盘的得到，可以不看

void fingertip_image(vector<vector<Point>> &contourscontours, Mat &fingertip, Mat &finger_image, int index);//用于将指尖图像提取出来可以不看

void image_add(Mat image_background, Mat image, Mat &image_add);//用于将指尖图像和键盘混合在一起，可以不看

void HSV_detector(Mat &frame, Mat &skinArea);



//用于滑动条的全局变量及回调函数
int g_nAlphaValueSlider=16;
int i = 16;
Mat image;
Mat imageCopy; //绘制矩形框时用来拷贝原图的图像  
bool leftButtonDownFlag = false; //左键单击后视频暂停播放的标志位  
Point originalPoint; //矩形框起点  
Point processPoint; //矩形框终点  
void on_Trackbar(int, void*)
{
	i = g_nAlphaValueSlider;
}


void onMouse(int event, int x, int y, int flags, void* ustc); //鼠标回调函数  

void main()
{
	bool key_shift = true;		//用于判定是否摁下shift键位，初始化为摁下

	int count = 0;				//进行时间使能计数，得到触发间隔

	bool Flag_center = false;   //用于判断重心位置变化

	bool Flag_in = false;		//用于判断每一秒钟后再进行触发，当Flag_in为true表示可以触发，若false表示不触发

	bool Flag_0 = false;

	bool insert_flag = false;	//标志判定是否进行第一帧进行视频的读取

	VideoCapture cap(0);		//用于得到所采用的摄像头

	vector<Point> point_insert; //用于存储中心插值的两个点

	vector<Point> center_temp;

	vector<int> countArea;		//用于存放相邻两帧的countArea并进行做差求值

	vector<int> distant;

	int count_voice = 0;		//提示音时间使能计数

	bool Flag_voice = true;		//提示音使能标志
	const int g_nMaxAlphaValue = 32;
	//在MFC中通过，setTimer()函数和onTimer()函数配合使用实现程序的大循环
	while (1)
	{


		Mat frame, image1, fingertip_input, fingertip_bin, image_bin, keyboard, skinArea, Skin;

		vector<vector<Point> > contours;//存储轮廓点用
		vector<Point> point;			//存储指尖点的位置
		Point point_temp,point_fingertip;
		Point fingertip = { 1000, 1000 };
		int index;				//存储轮廓的索引
		bool Flag = false;		//用于判断是否进行按下的操作
	
		int distant1 = 0;			//用于子函数中存储手部区域的面积大小
		int centerdistant;

		keyboard = imread("keyboard.jpg");//用于读入键盘的图像

		cap >> frame;						//将视频的每一帧存入frame中
		Mat show_img;	

		namedWindow(WINDOW_NAME);

		String TrackbarName = "灵敏度";

		createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
		on_Trackbar(g_nAlphaValueSlider,0);
		skinArea.create(frame.rows, frame.cols, CV_8UC1);

		/*ellipse_detect(frame, skinArea);*/
		HSV_detector(frame, skinArea);
		/*skinExtract(frame, skinArea,i);*/

		frame.copyTo(show_img, skinArea);
		show_img.copyTo(image);
		fingertip_input = frame.clone();
		Moments moment = moments(skinArea, true);
		Point center(moment.m10 / moment.m00, moment.m01 / moment.m00);
		circle(show_img, center, 8, Scalar(0, 0, 255), CV_FILLED);
		image_binary(fingertip_input, fingertip_bin);//图形进行二值化操作
		
		image_enrode_dilate(fingertip_bin, fingertip_bin);//腐蚀膨胀操作

		image_bin = fingertip_bin.clone();				//重新复制一个图像

		image_contours(fingertip_bin, contours);//得到二值图像的轮廓

		big_contours(frame,contours, index);//提取最大的轮廓

		//flag的标志是按下的标志，Flag_in的标志是每一秒钟一次触发的标志，且直接制约flag
		//k_fingertip(frame, image_bin, point, contours, index, Flag);

		convexHull_detection(frame, show_img, point, fingertip, center, contours, index, Flag, distant1);
		circle(show_img, fingertip, 6, Scalar(0, 255, 0), CV_FILLED);
		line(show_img, center, fingertip, Scalar(255, 0, 0), 2);
		/*cout << "距离" << distant[0] << endl;*/
		if (!insert_flag)
		{
			center_temp.push_back(center);
			point_insert.push_back(point[0]);
			distant.push_back(distant1);
			insert_flag = true;
		}
		center_temp.push_back(center);
		centerdistant = (center.x - center_temp[0].x) * (center.x - center_temp[0].x) + (center.y - center_temp[0].y) * (center.y - center_temp[0].y);
		/*cout << "距离" << (distant[0] - distant1) << endl;*/
		if ((double)(centerdistant) < 200)
		{
			Flag_center = true;
		}
		//进行插值处理，减小指尖的跳变
		point_temp = { (int)(((point_insert[0].x) + (point[0].x)) / 2), (int)(((point_insert[0].y) + (point[0].y)) / 2) };

		if ((double)( (distant[0]-distant1)) > 3000) 
		{
			Flag_0 = true;
		}

		//用于提示音的时间使能限定
		if (((double)(distant[0] - distant1)/distant1 < 3000) && (Flag_in) && (Flag_voice))
		{
			sndPlaySoundA((LPCSTR)"concerning.wav", SND_ASYNC);
			Flag_voice = false;
			count_voice = 0;
		}

		//提示音时间使能计数
		count_voice++;
		if (count_voice > 20)
		{
			Flag_voice = true;
		}

		//当输入为使能状态且手指处理摁下状态时候，重写Flag标志为输出标志，并赋值为true
		if (Flag_in && Flag_0 && Flag_center)
		{
			Flag = true;
			circle(keyboard, point_temp, 5, Scalar(0, 0, 225), CV_FILLED);
		}
		else
		{
			Flag = false;
			circle(keyboard, point_temp, 5, Scalar(0, 255, 0), CV_FILLED);
		}
		//circle(keyboard, point_temp, 5, Scalar(0, 225, 0), CV_FILLED);
		point_insert.push_back(point_temp);
		distant.push_back(distant1);
		/*countArea.push_back(countArea1);*/

		//用于删除上一帧中的元素，便于后面的操作
		vector<Point>::iterator itr1 = point_insert.begin();

		point_insert.erase(itr1);

		vector<int>::iterator itr2 = distant.begin();

		distant.erase(itr2);

		vector<Point>::iterator itr3 =center_temp.begin();

		center_temp.erase(itr3);
		//这里的Flag已经判断了摁下与状态的Flag
		if (Flag)
		{
			//cout << "shuchu" << endl;
			point.push_back(point_temp);
			keyboard_detect1(point_temp, Flag, key_shift);
			count = 0;
			Flag_in = false;
			Flag_center = false;
			Flag_0 = false;
		}

		count++;

		if (count > 2)
		{
			Flag_in = true;
		}

		//在MFC中，通过DrawPicToHDC()函数来实现将图片画在控件上
		imshow(WINDOW_NAME, show_img);
		setMouseCallback(WINDOW_NAME, onMouse);
		imshow("2", keyboard);

		waitKey(100);
	}
}
void onMouse(int event, int x, int y, int flags, void *ustc)
{

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		leftButtonDownFlag = true; //标志位  
		originalPoint = Point(x, y);  //设置左键按下点的矩形起点  
		processPoint = originalPoint;
	}
	if (event == CV_EVENT_MOUSEMOVE&&leftButtonDownFlag)
	{
		processPoint = Point(x, y);
	}
	if (event == CV_EVENT_LBUTTONUP)
	{
		leftButtonDownFlag = false;
		Mat rectImage = image(Rect(originalPoint, processPoint));
		imshow("Sub Image", rectImage);
	}
}
