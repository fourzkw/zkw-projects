#pragma once
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>

class GetTime
{
public :
	int getYear();
	int getMon();
	int getMDay(int mon);
	void GetTheTime();
	void ResetTime();

	int curYear, curMon, curMDay, curWDay;
	int curChoosingYear, curChoosingMon, curChoosingMDay;
	int dueYear, dueMon, dueMDay;
	int tMon[14] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
	tm p;               //当前时间
private :
	time_t timep;		//当前时间
	ExMessage m;
};

