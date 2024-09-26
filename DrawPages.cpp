#pragma once
#include "DrawPages.h";

extern bool isImportant, isToBuy;

void DrawPages::DrawImportantThings()
{
    cleardevice();
    
    setlinecolor(RGB(0, 0, 0));
    setfillcolor(RGB(255, 255, 255));
    //重要事项图标
    settextcolor(RGB(255, 0, 0));
    settextstyle(30, 0, _T("宋体"));
    outtextxy(60, 20, _T("IMPORTANT"));

    //增减事项
    fillrectangle(50, 80, 110, 110);
    fillrectangle(130, 80, 190, 110);

    //返回图标
    setfillcolor(RGB(255, 255, 255));
    fillrectangle(520, 420, 620, 460);
    settextcolor(RGB(0, 0, 0));
    settextstyle(30, 0, _T("宋体"));
    outtextxy(540, 425, _T("Back"));

    //增添删减待办事项图标
    settextcolor(RGB(0, 255, 0));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(65, 85, _T("add"));
    settextcolor(RGB(255, 0, 0));
    settextstyle(18, 0, _T("宋体"));
    outtextxy(133, 86, _T("delete"));
}

void DrawPages::DrawBasicPage(GetTime time, int x, bool isBatch)
{
    cleardevice();

    setlinecolor(RGB(0, 0, 0));
    setfillcolor(RGB(255, 255, 255));

    //年月日，重置
    fillrectangle(50, 20, 120, 60);
    fillrectangle(130, 20, 200, 60);
    fillrectangle(210, 20, 280, 60);
    fillrectangle(290, 20, 360, 60);
    //增添事项
    fillrectangle(50, 80, 110, 110);
    fillrectangle(130, 80, 190, 110);
    isBatch ? setfillcolor(RGB(200, 200, 200)) : setfillcolor(RGB(255, 255, 255));
    fillrectangle(210, 80, 270, 110);

    //菜单图标
    setfillcolor(RGB(255, 255, 255));
    fillrectangle(500, 80, 585, 120);
    settextcolor(RGB(0, 0, 0));
    settextstyle(25, 0, _T("宋体"));
    outtextxy(517, 88, _T("Menu"));

    switch (x)
    {
    case 1:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(50, 20, 120, 60);
        break;
    case 2:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(130, 20, 200, 60);
        break;
    case 3:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(210, 20, 280, 60);
        break;
    case 4:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(290, 20, 360, 60);
        break;
    case 5:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(50, 80, 110, 110);
        break;
    case 6:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(130, 80, 190, 110);
        break;
    case 7:
        setfillcolor(RGB(200, 200, 200));
        fillrectangle(210, 80, 270, 110);
        break;
    }

    //年月日，时分秒
    settextcolor(RGB(0, 0, 0));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(300, 30, _T("Reset"));
    //时间
    PrintTime(time);

    //增添删减待办事项图标
    settextcolor(RGB(0, 255, 0));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(65, 85, _T("add"));
    settextcolor(RGB(255, 0, 0));
    settextstyle(18, 0, _T("宋体"));
    outtextxy(133, 86, _T("delete"));
    settextcolor(RGB(0, 255, 0));
    outtextxy(217, 86, _T("batch"));
}

void DrawPages::DrawAddThingPage(GetTime time, bool isBatch)
{
    int largerSize = isBatch ? 60 : 0;

    setfillcolor(RGB(255, 255, 255));
    fillrectangle(100, 120, 540, 360 + largerSize);

    settextstyle(25, 0, _T("宋体"));
    settextcolor(RGB(0, 0, 0));
    outtextxy(130, 173, _T("名称："));
    fillrectangle(210, 170, 500, 200);
    if(isToBuy)
        outtextxy(130, 243, _T("价格："));
    else 
        outtextxy(130, 243, _T("数量："));
    fillrectangle(210, 240, 500, 270);

    //批量增加模式
    if (isBatch)
    {
        outtextxy(130, 303, _T("持续到："));
        fillrectangle(230, 300, 300, 340);
        fillrectangle(310, 300, 380, 340);
        fillrectangle(390, 300, 460, 340);

        settextcolor(RGB(0, 0, 0));
        settextstyle(20, 0, _T("宋体"));
        swprintf_s(ch_year, _T("%d"), time.dueYear);
        swprintf_s(ch_month, _T("%d"), time.dueMon);
        swprintf_s(ch_mday, _T("%d"), time.dueMDay);
        outtextxy(235, 302, ch_year);
        outtextxy(315, 302, ch_month);
        outtextxy(395, 302, ch_mday);
    }

    fillrectangle(190, 300 + largerSize, 250, 330 + largerSize);
    fillrectangle(270, 300 + largerSize, 330, 330 + largerSize);
    settextstyle(20, 0, _T("宋体"));
    settextcolor(RGB(0, 255, 0));
    outtextxy(200, 305 + largerSize, _T("add"));
    settextcolor(RGB(255, 0, 0));
    outtextxy(272, 305 + largerSize, _T("cancel"));
}

void DrawPages::DrawYearChoosePage(int currentYear, int choosingYear)
{
    cleardevice();
    int linex = 1, liney = 1;

    for (int i = currentYear - 12; i <= currentYear + 12; i++)
    {
        TCHAR ch[10];

        if (choosingYear != i) setfillcolor(RGB(255, 255, 255));
        else setfillcolor(RGB(200, 200, 200));
        fillrectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney);

        swprintf_s(ch, _T("%d"), i);
        settextcolor(RGB(0, 0, 0));
        settextstyle(30, 0, _T("宋体"));
        outtextxy(-40 + 110 * linex, 60 * liney + 10, ch);

        linex++;
        if (linex > 5)
        {
            liney++;
            linex = 1;
        }
    }

    FlushBatchDraw();
}

void DrawPages::DrawMonChoosePage(int choosingMon)
{
    cleardevice();
    int linex = 1, liney = 1;

    for (int i = 1; i <= 12; i++)
    {
        TCHAR ch[10];

        if (choosingMon != i) setfillcolor(RGB(255, 255, 255));
        else setfillcolor(RGB(200, 200, 200));
        fillrectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney);

        swprintf_s(ch, _T("%d"), i);
        settextcolor(RGB(0, 0, 0));
        settextstyle(30, 0, _T("宋体"));
        outtextxy(-40 + 110 * linex, 60 * liney + 10, ch);

        linex++;
        if (linex > 5)
        {
            liney++;
            linex = 1;
        }
    }

    FlushBatchDraw();
}

void DrawPages::DrawMDayChoosePage(int choosingMDay, int currentMon, int currentYear)
{
    cleardevice();

    int d = 0;
    //闰年2月加1
    if (currentMon == 2)
    {
        int y1 = currentYear / 4, y2 = currentYear / 100, y3 = currentYear / 400;
        if (y3 * 400 == currentYear || (y1 * 4 == currentYear && y2 * 100 != currentYear))
            d = 1;
    }

    int linex = 1, liney = 1;
    GetTime x;

    for (int i = 1; i <= x.tMon[currentMon] + d; i++)
    {
        TCHAR ch[10];

        if (choosingMDay != i) setfillcolor(RGB(255, 255, 255));
        else setfillcolor(RGB(200, 200, 200));
        fillrectangle(-55 + 110 * linex, 60 * liney, 35 + 110 * linex, 50 + 60 * liney);

        swprintf_s(ch, _T("%d"), i);
        settextcolor(RGB(0, 0, 0));
        settextstyle(30, 0, _T("宋体"));
        outtextxy(-40 + 110 * linex, 60 * liney + 10, ch);

        linex++;
        if (linex > 5)
        {
            liney++;
            linex = 1;
        }
    }

    FlushBatchDraw();
}

void DrawPages::PrintTime(GetTime time)
{
    swprintf_s(ch_year, _T("%d"), time.curYear);
    swprintf_s(ch_month, _T("%d"), time.curMon);
    swprintf_s(ch_mday, _T("%d"), time.curMDay);
    //swprintf_s(ch_wday, _T("%d"), currentWday);

    settextcolor(RGB(0, 0, 0));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(65, 32, ch_year);
    outtextxy(155, 32, ch_month);
    outtextxy(235, 32, ch_mday);

    swprintf_s(detailTime, L"%d: %d: %d", time.p.tm_hour, time.p.tm_min, time.p.tm_sec);
    outtextxy(490, 20, detailTime);
}

void DrawPages::DrawMenu(int choosing)
{
    //菜单栏
    setfillcolor(RGB(255, 255, 255));
    for (int i = 1; i <= menuNum; i++)
        fillrectangle(500, 40 + 40 * i, 585, 80 + 40 * i);
    settextcolor(RGB(0, 0, 0));
    settextstyle(18, 0, _T("宋体"));
    outtextxy(502, 90, _T("Important"));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(517, 130, _T("ToBuy"));
}

void DrawPages::DrawToBuyPage()
{
    cleardevice();

    setlinecolor(RGB(0, 0, 0));
    setfillcolor(RGB(255, 255, 255));

    //TOBUY标题
    settextcolor(RGB(255, 0, 0));
    settextstyle(30, 0, _T("宋体"));
    outtextxy(40, 20, _T("TO BUY ITEMS"));

    //返回图标
    setfillcolor(RGB(255, 255, 255));
    fillrectangle(520, 420, 620, 460);
    settextcolor(RGB(0, 0, 0));
    settextstyle(30, 0, _T("宋体"));
    outtextxy(540, 425, _T("Back"));

    //增添删减ITEM图标
    fillrectangle(50, 80, 110, 110);
    fillrectangle(130, 80, 190, 110);
    settextcolor(RGB(0, 255, 0));
    settextstyle(20, 0, _T("宋体"));
    outtextxy(65, 85, _T("add"));
    settextcolor(RGB(255, 0, 0));
    settextstyle(18, 0, _T("宋体"));
    outtextxy(133, 86, _T("delete"));
}