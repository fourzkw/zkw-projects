#pragma once
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>
#include<vector>
#include "DrawPages.h"
#include "GetTime.h"
#include "Tools.h"

struct theThing
{
	TCHAR theName[30];
	int totalNum;
	int finishNum;
};

struct timer
{
	float tStart;
	float tEnd;
};

void OnLoad();
void OnDownLoad();
void PageChoose();
//bool InRectangle(int x1, int y1, int x2, int y2, ExMessage m);
void AddThingChance(int curYear, int curMon, int curMDay, bool isBatch);
void OutPutCurrentThings(int curYear, int curMon, int curMDay);
void TimeWait(timer *t);
void ThingsAction(int curYear, int curMon, int curMDay);
void DeleteThing(int x);