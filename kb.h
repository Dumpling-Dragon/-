//头文件 
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>

#define pause system("pause");/*pause这个系统命令的功能很简单，
就是在命令行上输出一行类似于“请按任意键继续...”的字，等待用户按一个键，然后返回。*/
#define cls system("cls");//系统清屏 
#define color1(C) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_##C)//下面定义SetConsoleTextAttribute宏来修改字体颜色 
#define color2(C1,C2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_##C1|FOREGROUND_##C2);
#define autocolor SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
//字体颜色 
#define RED color1(RED)
#define GREEN color1(GREEN)
#define BLUE color1(BLUE)
#define RG color2(RED,GREEN)
#define RB color2(RED,BLUE)
#define GB color2(GREEN,BLUE)

#define wait Sleep(500)
#define cle FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE))
//（测试中）背景音乐 playsound
#include<Mmsystem.h> 
#pragma comment(lib,"WinMM.Lib")
