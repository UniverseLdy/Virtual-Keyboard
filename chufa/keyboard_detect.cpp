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

//keyboard_detect(输入的点的位置，一个flag用于判断手指是否摁下,是否摁下shift)
//判断键位的位置，进而得到键盘的输出，
//在判断位置的同时，其实就是给键盘建了模型
//注意里面的keybd_event()函数，微软的标准输入函数

void keyboard_detect(vector<Point> point, bool &flag, bool &uptoo)
{
	//判断键位的输出，在微软键位输出函数中需要的参数
	int vk = NULL;
	char pchar = NULL;

	if (flag)	//如果手指摁下，则对键位的相应输出进行判断
	{
		for (int j = 0; j < point.size(); j++)
		{
			//第一行的键位
			if (0 < (point[j].y) && point[j].y < 45)
			{
				int key_count;

				if (0 < (point[j].x) && point[j].x < 63)
				{
					key_count = 0;
				}
				else if (70 < (point[j].x) && point[j].x < 135)
				{
					key_count = 1;
				}
				else if (145 < (point[j].x) && point[j].x < 205)
				{
					key_count = 2;
				}
				else if (215 < (point[j].x) && point[j].x < 280)
				{
					key_count = 3;
				}
				else if (290 < (point[j].x) && point[j].x < 350)
				{
					key_count = 4;
				}
				else if (360 < (point[j].x) && point[j].x < 425)
				{
					key_count = 5;
				}
				else if (435 < (point[j].x) && point[j].x < 495)
				{
					key_count = 6;
				}
				else if (505 < (point[j].x) && point[j].x < 568)
				{
					key_count = 7;
				}
				else if (577 < (point[j].x) && point[j].x < 641)
				{
					key_count = 8;
				}
				else if (650 < (point[j].x) && point[j].x < 712)
				{
					key_count = 9;
				}
				else if (722 < (point[j].x) && point[j].x < 785)
				{
					key_count = 10;
				}
				else if (795 < (point[j].x) && point[j].x < 857)
				{
					key_count = 11;
				}
				else if (866 < (point[j].x) && point[j].x < 930)
				{
					key_count = 12;
				}
				else if (940 < (point[j].x) && point[j].x < 1000)
				{
					key_count = 13;
				}
				else
				{
					key_count = 14;
				}

				//利用switch判断语句，判断键位是哪个，并相应的在控制台进行输出
				switch (key_count)
				{
				case 0:
				{
						  cout << "esc" << endl;
						  vk = VK_ESCAPE;
						  break;
				}
				case 1:
				{
						  cout << "f1" << endl;
						  vk = VK_F1;
						  break;
				}
				case 2:
				{
						  cout << "f2" << endl;
						  vk = VK_F2;
						  break;
				}
				case 3:
				{
						  cout << "f3" << endl;
						  vk = VK_F3;
						  break;
				}
				case 4:
				{
						  cout << "f4" << endl;
						  vk = VK_F4;
						  break;
				}
				case 5:
				{
						  cout << "f5" << endl;
						  vk = VK_F5;
						  break;
				}
				case 6:
				{
						  cout << "f6" << endl;
						  vk = VK_F6;
						  break;
				}

				case 7:
				{
						  cout << "f7" << endl;
						  vk = VK_F7;
						  break;
				}
				case 8:
				{
						  cout << "f8" << endl;
						  vk = VK_F8;
						  break;
				}
				case 9:
				{
						  cout << "f9" << endl;
						  vk = VK_F9;
						  break;
				}
				case 10:
				{
						   cout << "f10" << endl;
						   vk = VK_F10;
						   break;
				}
				case 11:
				{
						   cout << "f11" << endl;
						   vk = VK_F11;
						   break;
				}
				case 12:
				{
						   cout << "f12" << endl;
						   vk = VK_F12;
						   break;
				}
				case 13:
				{
						   cout << "backspace" << endl;
						   vk = VK_BACK;
						   break;
				}
				default: break;
				}
				//调用微软的标准键盘输入函数，实现键盘的功能
				if (vk != NULL)
				{
					BYTE key = vk;

					//keybd_event()键盘的事件相应函数
					keybd_event(key, 0, 0, 0);	//摁下一个键位
					sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);//摁下键位时候的音效反馈
					keybd_event(key, 0, KEYEVENTF_KEYUP, 0);//松开一个键位
				}

			}

			//第二行键位
			else if (55 < (point[j].y) && (point[j].y) < 125)
			{
				int key_count;

				if (0 < (point[j].x) && point[j].x < 60)
				{
					key_count = 0;
				}
				else if (70 < (point[j].x) && point[j].x < 130)
				{
					key_count = 1;
				}
				else if (140 < (point[j].x) && point[j].x < 200)
				{
					key_count = 2;
				}
				else if (210 < (point[j].x) && point[j].x < 270)
				{
					key_count = 3;
				}
				else if (280 < (point[j].x) && point[j].x < 340)
				{
					key_count = 4;
				}
				else if (350 < (point[j].x) && point[j].x < 410)
				{
					key_count = 5;
				}
				else if (420 < (point[j].x) && point[j].x < 480)
				{
					key_count = 6;
				}
				else if (490 < (point[j].x) && point[j].x < 550)
				{
					key_count = 7;
				}
				else if (560 < (point[j].x) && point[j].x < 620)
				{
					key_count = 8;
				}
				else if (630 < (point[j].x) && point[j].x < 690)
				{
					key_count = 9;
				}
				else if (698 < (point[j].x) && point[j].x < 760)
				{
					key_count = 10;
				}
				else if (768 < (point[j].x) && point[j].x < 830)
				{
					key_count = 11;
				}
				else if (838 < (point[j].x) && point[j].x < 900)
				{
					key_count = 12;
				}
				else if (907 < (point[j].x) && point[j].x < 1000)
				{
					key_count = 13;
				}
				else
				{
					key_count = 14;
				}

				switch (key_count)
				{
				case 0:
				{
						  cout << "~" << endl;
						  pchar = '`';
						  break;
				}
				case 1:
				{
						  cout << "1" << endl;
						  pchar = '1';
						  break;
				}
				case 2:
				{
						  cout << "2" << endl;
						  pchar = '2';
						  break;
				}
				case 3:
				{
						  cout << "3" << endl;
						  pchar = '3';
						  break;
				}
				case 4:
				{
						  cout << "4" << endl;
						  pchar = '4';
						  break;
				}
				case 5:
				{
						  cout << "5" << endl;
						  pchar = '5';
						  break;
				}
				case 6:
				{
						  cout << "6" << endl;
						  pchar = '6';
						  break;
				}
				case 7:
				{
						  cout << "7" << endl;
						  pchar = '7';
						  break;
				}
				case 8:
				{
						  cout << "8" << endl;
						  pchar = '8';
						  break;
				}
				case 9:
				{
						  cout << "9" << endl;
						  pchar = '9';
						  break;
				}
				case 10:
				{
						   cout << "0" << endl;
						   pchar = '0';
						   break;
				}
				case 11:
				{
						   pchar = '-';
						   break;
				}
				case 12:
				{
						   pchar = '=';
						   break;
				}
				case 13:
				{
						   cout << "delete" << endl;
						   vk = VK_DELETE;
						   BYTE key = vk;
						   keybd_event(key, 0, 0, 0);
						   sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						   keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						   break;
				}
				default: break;
				}
				if (pchar != NULL)
				{
					vk = VkKeyScan(pchar);
					BYTE key = vk;

					//uptoo判断shift是否摁下
					if (uptoo)
					{
						keybd_event(VK_SHIFT, 0, 0, 0);
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
						uptoo = false;
					}
					else
					{
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
					}

				}

			}


			//第三行键位
			else if (135 < (point[j].y) && point[j].y < 205)
			{
				int key_count;

				if (0 < (point[j].x) && (point[j].x) < 95)
				{
					key_count = 0;
				}
				else if (100 < (point[j].x) && (point[j].x) < 165)
				{
					key_count = 1;
				}
				else if (170 < (point[j].x) && (point[j].x) < 235)
				{
					key_count = 2;
				}
				else if (240 < (point[j].x) && (point[j].x) < 305)
				{
					key_count = 3;
				}
				else if (310 < (point[j].x) && (point[j].x) < 375)
				{
					key_count = 4;
				}
				else if (380 < (point[j].x) && (point[j].x) < 445)
				{
					key_count = 5;
				}
				else if (450 < (point[j].x) && (point[j].x) < 515)
				{
					key_count = 6;
				}
				else if (520 < (point[j].x) && (point[j].x) < 585)
				{
					key_count = 7;
				}
				else if (590 < (point[j].x) && (point[j].x) < 655)
				{
					key_count = 8;
				}
				else if (660 < (point[j].x) && (point[j].x) < 725)
				{
					key_count = 9;
				}
				else if (730 < (point[j].x) && (point[j].x) < 795)
				{
					key_count = 10;
				}
				else if (800 < (point[j].x) && (point[j].x) < 865)
				{
					key_count = 11;
				}
				else if (870 < (point[j].x) && (point[j].x) < 935)
				{
					key_count = 12;
				}
				else if (940 < (point[j].x) && (point[j].x) < 1000)
				{
					key_count = 13;
				}
				else
				{
					key_count = 14;
				}

				switch (key_count)
				{
				case 0:
				{
						  cout << "Tab" << endl;
						  vk = VkKeyScan(0x09) & 0xFF;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 1:
				{
						  cout << "Q" << endl;
						  pchar = 'Q';
						  break;
				}
				case 2:
				{
						  cout << "W" << endl;
						  pchar = 'W';
						  break;
				}
				case 3:
				{
						  cout << "E" << endl;
						  pchar = 'E';
						  break;
				}
				case 4:
				{
						  cout << "R" << endl;
						  pchar = 'R';
						  break;
				}
				case 5:
				{
						  cout << "T" << endl;

						  pchar = 'T';

						  break;
				}
				case 6:
				{
						  cout << "Y" << endl;

						  pchar = 'Y';

						  break;
				}
				case 7:
				{
						  cout << "U" << endl;

						  pchar = 'U';

						  break;
				}
				case 8:
				{
						  cout << "I" << endl;

						  pchar = 'I';

						  break;
				}
				case 9:
				{
						  cout << "O" << endl;

						  pchar = 'O';

						  break;
				}
				case 10:
				{
						   cout << "P" << endl;

						   pchar = 'P';

						   break;
				}
				case 11:
				{
						   cout << "[" << endl;

						   pchar = '[';

						   break;
				}
				case 12:
				{
						   cout << "]" << endl;

						   pchar = ']';

						   break;
				}
				case 13:
				{
						   cout << "\\" << endl;

						   pchar = '\\';

						   break;
				}
				default: break;
				}
				if (pchar != NULL)
				{				
					SHORT ks = VkKeyScan(pchar);
					BYTE key = ks & 0xFF;

					if (uptoo)
					{
						keybd_event(VK_SHIFT, 0, 0, 0);
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
						uptoo = false;
					}
					else
					{
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
					}
				}
			}

			//第四行键位
			else if (215 < (point[j].y) && point[j].y < 285)
			{
				int key_count;

				if (0 < (point[j].x) && point[j].x < 113)
				{
					key_count = 0;
				}
				else if (120 < (point[j].x) && point[j].x < 180)
				{
					key_count = 1;
				}
				else if (190 < (point[j].x) && point[j].x < 250)
				{
					key_count = 2;
				}
				else if (260 < (point[j].x) && point[j].x < 320)
				{
					key_count = 3;
				}
				else if (330 < (point[j].x) && point[j].x < 390)
				{
					key_count = 4;
				}
				else if (400 < (point[j].x) && point[j].x < 460)
				{
					key_count = 5;
				}
				else if (470 < (point[j].x) && point[j].x < 530)
				{
					key_count = 6;
				}
				else if (540 < (point[j].x) && point[j].x < 600)
				{
					key_count = 7;
				}
				else if (610 < (point[j].x) && point[j].x < 670)
				{
					key_count = 8;
				}
				else if (680 < (point[j].x) && point[j].x < 740)
				{
					key_count = 9;
				}
				else if (750 < (point[j].x) && point[j].x < 810)
				{
					key_count = 10;
				}
				else if (820 < (point[j].x) && point[j].x < 880)
				{
					key_count = 11;
				}
				else if (890 < (point[j].x) && point[j].x < 1000)
				{
					key_count = 12;
				}
				else
				{
					key_count = 14;
				}

				switch (key_count)
				{
				case 0:
				{
						  cout << "CapsLock" << endl;
						  vk = VK_CAPITAL;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 1:
				{
						  cout << "A" << endl;						 
							  pchar = 'A';						
						  break;
				}
				case 2:
				{
						  cout << "S" << endl;						
							  pchar = 'S';						
						  break;
				}
				case 3:
				{
						  cout << "D" << endl;						 
							  pchar = 'D';						
						  break;
				}
				case 4:
				{
						  cout << "F" << endl;						 
							  pchar = 'F';					
						  break;
				}
				case 5:
				{
						  cout << "G" << endl;						 
							  pchar = 'G';						
						  break;
				}
				case 6:
				{
						  cout << "H" << endl;
						  pchar = 'H';						 
						  break;
				}
				case 7:
				{
						  cout << "J" << endl;						 
							  pchar = 'J';						
						  break;
				}
				case 8:
				{
						  cout << "K" << endl;						 
							  pchar = 'K';						
						  break;
				}
				case 9:
				{
						  cout << "L" << endl;						 
							  pchar = 'L';						
						  break;
				}
				case 10:
				{
						   cout << ":" << endl;						  
							   pchar = ':';						
						   break;
				}
				case 11:
				{
						   cout << "'" << endl;						  
							   pchar = '\'';
						   break;
				}
				case 12:
				{
						   cout << "Enter" << endl;
						   vk = VkKeyScan(0x0D);
						   BYTE key = vk;
						   keybd_event(key, 0, 0, 0);
						   sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						   keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						   break;
				}
				default: break;
				}

				if (pchar != NULL)
				{
					vk = VkKeyScan(pchar);
					BYTE key = vk;

					if (uptoo)
					{
						keybd_event(VK_SHIFT, 0, 0, 0);
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
						uptoo = false;
						
					}
					else
					{
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
					}
				}
			}

			//第五行键位
			else if (295 < (point[j].y) && point[j].y < 365)
			{
				int key_count;

				if (0 < (point[j].x) && point[j].x < 147)
				{
					key_count = 0;
				}
				else if (155 < (point[j].x) && point[j].x < 217)
				{
					key_count = 1;
				}
				else if (225 < (point[j].x) && point[j].x < 287)
				{
					key_count = 2;
				}
				else if (295 < (point[j].x) && point[j].x < 357)
				{
					key_count = 3;
				}
				else if (365 < (point[j].x) && point[j].x < 427)
				{
					key_count = 4;
				}
				else if (435 < (point[j].x) && point[j].x < 497)
				{
					key_count = 5;
				}
				else if (505 < (point[j].x) && point[j].x < 567)
				{
					key_count = 6;
				}
				else if (575 < (point[j].x) && point[j].x < 637)
				{
					key_count = 7;
				}
				else if (625 < (point[j].x) && point[j].x < 707)
				{
					key_count = 8;
				}
				else if (695 < (point[j].x) && point[j].x < 777)
				{
					key_count = 9;
				}
				else if (765 < (point[j].x) && point[j].x < 847)
				{
					key_count = 10;
				}
				else if (855 < (point[j].x) && point[j].x < 1000)
				{
					key_count = 11;
				}
				else
				{
					key_count = 14;
				}

				switch (key_count)
				{
				case 0:
				{
						  cout << "Shift" << endl;
						  uptoo = true;
						  vk = VK_SHIFT;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 1:
				{
						  cout << "Z" << endl;
						 
							  pchar = 'Z';
						
						  break;
				}
				case 2:
				{
						  cout << "X" << endl;
						 
							  pchar = 'X';
						
						
						  break;
				}
				case 3:
				{
						  cout << "C" << endl;
						 
							  pchar = 'C';
							
						  break;
				}
				case 4:
				{
						  cout << "V" << endl;
						 
							  pchar = 'V';
							
						  break;
				}
				case 5:
				{
						  cout << "B" << endl;
						 
							  pchar = 'B';
							
						  break;
				}
				case 6:
				{
						  cout << "N" << endl;
						 
							  pchar = 'N';
						
						  break;
				}
				case 7:
				{
						  cout << "M" << endl;
						 
							  pchar = 'M';
						
						  break;
				}
				case 8:
				{
						  cout << "<" << endl;
						
							  pchar = '<';
						
						  break;
				}
				case 9:
				{
						  cout << ">" << endl;
						 
							  pchar = '>';
						
						  break;
				}
				case 10:
				{
						   cout << "?" << endl;
						  
							   pchar = '?';
							
						   break;
				}
				case 11:
				{
						   cout << "Shift" << endl;
						   uptoo = true;
						   vk = VK_SHIFT;
						   BYTE key = vk;
						   keybd_event(key, 0, 0, 0);
						   sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						   keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						   break;
				}
				default: break;
				}
				if (pchar != NULL)
				{
					vk = VkKeyScan(pchar);
					BYTE key = vk;

					if (uptoo)
					{
						keybd_event(VK_SHIFT, 0, 0, 0);
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
						uptoo = false;
					}
					else
					{
						keybd_event(key, 0, 0, 0);
						sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
					}
					
				}
			}

			//第六行键位
			else if (370 < (point[j].y) && point[j].y < 450)
			{
				int key_count;

				if (0 < (point[j].x) && point[j].x < 60)
				{
					key_count = 0;
				}
				else if (68 < (point[j].x) && point[j].x < 130)
				{
					key_count = 1;
				}
				else if (138 < (point[j].x) && point[j].x < 200)
				{
					key_count = 2;
				}
				else if (207 < (point[j].x) && point[j].x < 285)
				{
					key_count = 3;
				}
				else if (295 < (point[j].x) && point[j].x < 637)
				{
					key_count = 4;
				}
				else if (645 < (point[j].x) && point[j].x < 722)
				{
					key_count = 5;
				}
				else if (730 < (point[j].x) && point[j].x < 795)
				{
					key_count = 6;
				}
				else if (800 < (point[j].x) && point[j].x < 865 && 410 < (point[j].y) && point[j].y < 450)
				{
					key_count = 7;
				}
				else if (870 < (point[j].x) && point[j].x < 933 && 370 < (point[j].y) && point[j].y < 410)
				{
					key_count = 8;
				}
				else if (870 < (point[j].x) && point[j].x < 933 && 410 < (point[j].y) && point[j].y < 450)
				{
					key_count = 9;
				}
				else if (940 < (point[j].x) && point[j].x < 1000 && 410 < (point[j].y) && point[j].y < 450)
				{
					key_count = 10;
				}
				else
				{
					key_count = 14;
				}

				switch (key_count)
				{
				case 0:
				{
						  cout << "fn" << endl;
						  vk = VK_FINAL;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 1:
				{
						  cout << "Ctr" << endl;
						  vk = VK_CONTROL;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 2:
				{
						  cout << "Alt" << endl;
						  vk = VK_MENU;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 3:
				{
						  cout << "Windows" << endl;
						  vk = VK_LWIN;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 4:
				{
						  cout << "Space" << endl;
						  vk = VK_SPACE;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  sndPlaySound("beep", SND_ASYNC);
						  break;
				}
				case 5:
				{
						  cout << "Windows" << endl;
						  vk = VK_LWIN;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 6:
				{
						  cout << "Alt" << endl;
						  vk = VK_MENU;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 7:
				{
						  cout << "left" << endl;
						  vk = VK_LEFT;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 8:
				{
						  cout << "up" << endl;
						  vk = VK_UP;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 9:
				{
						  cout << "down" << endl;
						  vk = VK_DOWN;
						  BYTE key = vk;
						  keybd_event(key, 0, 0, 0);
						  sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						  keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						  break;
				}
				case 10:
				{
						   cout << "right" << endl;
						   vk = VK_RIGHT;
						   BYTE key = vk;
						   keybd_event(key, 0, 0, 0);
						   sndPlaySoundA((LPCSTR)"beep.wav", SND_ASYNC);
						   keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
						   break;
				}
				default: break;
				}
			}
		}
	}
	flag = false;
}
