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

#define MAIN_PAGE   0
#define YEAR_PAGE   1
#define MON_PAGE    2
#define MDAY_PAGE   3
#define ADDTHING_PAGE   5
#define IMPORTANT_PAGE  7
#define MENU_PAGE   8
#define TOBUY_PAGE  9

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
void AddThingChance(int curYear, int curMon, int curMDay, bool isBatch);
void OutPutCurrentThings(int curYear, int curMon, int curMDay);
void TimeWait(timer *t);
void ThingsAction(int curYear, int curMon, int curMDay);
void DeleteThing(int x);