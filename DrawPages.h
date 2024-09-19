#pragma once
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>
#include "GetTime.h"

class DrawPages
{
public :
	void DrawImportantThings();
	void PrintTime(GetTime time);
	void DrawBasicPage(GetTime time, int x, bool isBatch);
	void DrawAddThingPage(GetTime time, bool isBatch);
	void DrawYearChoosePage(int currentYear, int choosingYear);
	void DrawMonChoosePage(int choosingMon);
	void DrawMDayChoosePage(int choosingMDay, int currentMon, int currentYear);
	float x1 = -1, x2 = -1;
	TCHAR ch_year[10] = _T(""), ch_month[10] = _T(""), ch_mday[10] = _T(""), ch_wday[10] = _T("");
	TCHAR detailTime[20] = _T("");
};

