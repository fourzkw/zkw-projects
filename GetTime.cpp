#pragma once
#include "GetTime.h"
#include "Tools.h"
#include "DrawPages.h"

DrawPages timeChoosePages;

int GetTime::getYear()
{
    timeChoosePages.DrawYearChoosePage(curYear, curChoosingYear);

    while (1)
    {
        getmessage(&m, EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            int linex = 1, liney = 1;
            for (int i = curYear - 12; i <= curYear + 12; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                {
                    //curYear = i;
                    return i; 
                }

                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }

        if (m.message == WM_MOUSEMOVE)
        {
            int linex = 1, liney = 1;
            for (int i = curYear - 12; i <= curYear + 12; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                    curChoosingYear = i;
                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }
        timeChoosePages.DrawYearChoosePage(curYear, curChoosingYear);
    }

}

int GetTime::getMon() 
{
    timeChoosePages.DrawMonChoosePage(curChoosingMon);

    while (1)
    {
        getmessage(&m, EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            int linex = 1, liney = 1;
            for (int i = 1; i <= 12; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                {
                    //curMon = i;
                    return i;
                }

                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }

        if (m.message == WM_MOUSEMOVE)
        {
            int linex = 1, liney = 1;
            for (int i = 1; i <= 12; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                    curChoosingMon = i;
                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }
        timeChoosePages.DrawMonChoosePage(curChoosingMon);
    }
}

int GetTime::getMDay(int mon)
{
    timeChoosePages.DrawMDayChoosePage(curChoosingMDay, curMon, curYear);

    while (1)
    {
        getmessage(&m, EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN)
        {
            int d = 0;
            //闰年2月加1
            if (mon == 2)
            {
                int y1 = curYear / 4, y2 = curYear / 100, y3 = curYear / 400;
                if (y3 * 400 == curYear || (y1 * 4 == curYear && y2 * 100 != curYear))
                    d = 1;
            }

            int linex = 1, liney = 1;
            GetTime x;

            for (int i = 1; i <= x.tMon[mon] + d; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                {
                    return i;
                }
                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }

        if (m.message == WM_MOUSEMOVE)
        {
            int d = 0;
            //闰年2月加1
            if (mon == 2)
            {
                int y1 = curYear / 4, y2 = curYear / 100, y3 = curYear / 400;
                if (y3 * 400 == curYear || (y1 * 4 == curYear && y2 * 100 != curYear))
                    d = 1;
            }

            int linex = 1, liney = 1;
            GetTime x;

            for (int i = 1; i <= x.tMon[mon] + d; i++)
            {
                if (Tools::InRectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney, m))
                    curChoosingMDay = i;
                linex++;
                if (linex > 5)
                {
                    liney++;
                    linex = 1;
                }
            }
        }
        timeChoosePages.DrawMDayChoosePage(curChoosingMDay, mon, curYear);
    }
}

void GetTime::GetTheTime()        //获取当前时间
{
    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    localtime_s(&p, &timep);//用localtime将秒数转化为struct tm结构体
    p.tm_year += 1900;
    p.tm_mon++;
}

void GetTime::ResetTime()
{
    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    localtime_s(&p, &timep);//用localtime将秒数转化为struct tm结构体
    p.tm_year += 1900;
    p.tm_mon++;
    curChoosingYear = curYear = p.tm_year;
    curChoosingMon = curMon = p.tm_mon;
    curChoosingMDay = curMDay = p.tm_mday;
    curWDay = p.tm_wday;
}