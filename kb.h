//ͷ�ļ� 
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>

#define pause system("pause");/*pause���ϵͳ����Ĺ��ܼܺ򵥣�
�����������������һ�������ڡ��밴���������...�����֣��ȴ��û���һ������Ȼ�󷵻ء�*/
#define cls system("cls");//ϵͳ���� 
#define color1(C) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_##C)//���涨��SetConsoleTextAttribute�����޸�������ɫ 
#define color2(C1,C2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_##C1|FOREGROUND_##C2);
#define autocolor SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
//������ɫ 
#define RED color1(RED)
#define GREEN color1(GREEN)
#define BLUE color1(BLUE)
#define RG color2(RED,GREEN)
#define RB color2(RED,BLUE)
#define GB color2(GREEN,BLUE)

#define wait Sleep(500)
#define cle FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE))
//�������У��������� playsound
#include<Mmsystem.h> 
#pragma comment(lib,"WinMM.Lib")
