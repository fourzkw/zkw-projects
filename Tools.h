#pragma once
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <graphics.h>
#include <direct.h>

class Tools
{
public:
	//判断鼠标是否在矩形范围内
	static bool InRectangle(int x1, int y1, int x2, int y2, ExMessage m);
};

