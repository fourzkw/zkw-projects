#pragma once
#include "Main.h"
#include "Window.h"

using namespace std;

DrawPages drawPages;
GetTime getTime;

ExMessage mouseMessage;
int currentPage, lastPage;
int currentm;       //��ǰ���λ��    1�� 2�� 3��


int thingNum[100][13][32];
theThing tThing[100][13][32][10];
int currentFirstNumber = 0;
int currentChooseThing = -1;

bool isImportant = 0;
bool isBatch = 0;

TCHAR currentAddName[30], currentAddNum[30];

timer downLoadtimer;

WindowSize wS = { 640,480 };

int main()
{
    OnLoad();

    srand((int)time(0));
	initgraph(640, 480, EX_DBLCLKS);
    setbkmode(TRANSPARENT);
    setbkcolor(RGB(255, 255, 255));
    BeginBatchDraw();
    getTime.ResetTime();

    while (1)
    {
       getTime.GetTheTime();

        //��ҳ��
        if (currentPage == 0)
        {
            drawPages.DrawBasicPage(getTime, currentm, isBatch);

            OutPutCurrentThings(getTime.curYear, getTime.curMon, getTime.curMDay);

            ThingsAction(getTime.curYear, getTime.curMon, getTime.curMDay);

            FlushBatchDraw();
        }
        //���ѡ��
        if (currentPage == 1)
        {
            getTime.curYear = getTime.getYear();
            currentPage = 0;
            currentm = -1;
        }
        //�·�ѡ��
        if (currentPage == 2)
        {
            getTime.curMon = getTime.getMon();
            currentPage = 0;
            currentm = -1;
        }
        //����ѡ��
        if (currentPage == 3)
        {
            getTime.curMDay = getTime.getMDay(getTime.curMon);
            currentPage = 0;
            currentm = -1;
        }
        //��������
        if (currentPage == 5)
        {
            currentm = 0;

            //����״̬�ͷ���Ҫ״̬���������ģʽ
            drawPages.DrawBasicPage(getTime, currentm, isBatch);
            drawPages.DrawAddThingPage(getTime, (isBatch && !isImportant));

            if (isImportant)
                AddThingChance(2077, 12, 4, false);
            else
                AddThingChance(getTime.curYear, getTime.curMon, getTime.curMDay, isBatch);

            settextcolor(RGB(0, 0, 0));
            outtextxy(215, 173, currentAddName);
            outtextxy(215, 243, currentAddNum);

            FlushBatchDraw();
        }
        //��Ҫ����
        if (currentPage == 7) 
        {
            drawPages.DrawImportantThings();
            OutPutCurrentThings(2077, 12, 4);
            ThingsAction(2077, 12, 4);

            FlushBatchDraw();
        }

        PageChoose();
        flushmessage(EX_MOUSE);
    }

    EndBatchDraw();
	closegraph();
	return 0;
}

//����ҳ��
void PageChoose()
{
    //��ȡ��Ϣ
    getmessage(&mouseMessage, EX_MOUSE);
    if (mouseMessage.message == WM_LBUTTONDOWN)
    {
         if (Tools::InRectangle(50, 20, 120, 60, mouseMessage) && currentPage == 0)        //���ѡ��
                currentPage = 1;
         if (Tools::InRectangle(130, 20, 200, 60, mouseMessage) && currentPage == 0)       //�·�ѡ��
                currentPage = 2;
         if (Tools::InRectangle(210, 20, 280, 60, mouseMessage) && currentPage == 0)       //����ѡ��
                currentPage = 3;
         if (Tools::InRectangle(50, 80, 110, 110, mouseMessage) && (currentPage == 0 || currentPage == 7))     //��������ҳ��
         {
             if (isBatch)
             {
                 getTime.dueYear = getTime.curYear;
                 getTime.dueMon = getTime.curMon;
                 getTime.dueMDay = getTime.curMDay;
             }
                currentPage = 5;
         }
         //��Ҫ����ҳ��
         if (Tools::InRectangle(500, 80, 585, 120, mouseMessage) && currentPage == 0)
         {
             currentPage = 7;
             currentFirstNumber = 0;
             isImportant = true;
         }

         //��Ҫ����ҳ�淵����ҳ��
         if (Tools::InRectangle(500, 420, 585, 460, mouseMessage) && currentPage == 7)
         {
             currentPage = 0;
             currentFirstNumber = 0;
             isImportant = false;
         }

        //ɾ����ǰ����
        if (Tools::InRectangle(130, 80, 190, 110, mouseMessage) && (isImportant ? (thingNum[77][12][4] > 0) : (thingNum[getTime.curYear - 2000][getTime.curMon][getTime.curMDay] > 0)) && (currentPage == 0 || currentPage == 7))
        {
            DeleteThing(currentChooseThing);
            currentChooseThing = -1;
            OnDownLoad();
        }

        //���õ�ǰʱ��
        if (Tools::InRectangle(290, 20, 360, 60, mouseMessage))
        {
            getTime.ResetTime();
        }
        
        //ת���Ƿ�������������
        if (Tools::InRectangle(210, 80, 270, 110, mouseMessage) && currentPage == 0)
            isBatch = !isBatch;
    }

    if (mouseMessage.message == WM_MOUSEMOVE)
    {
        //�ж�ǿ����ť
        //���
        if (Tools::InRectangle(50, 20, 120, 60, mouseMessage))
            currentm = 1;
        //�·�
        else if (Tools::InRectangle(130, 20, 200, 60, mouseMessage))
            currentm = 2;
        //����
        else if (Tools::InRectangle(210, 20, 280, 60, mouseMessage))
            currentm = 3;
        //����ʱ��
        else if (Tools::InRectangle(290, 20, 360, 60, mouseMessage))
            currentm = 4;
        //add
        else if (Tools::InRectangle(50, 80, 110, 110, mouseMessage))
            currentm = 5;
        //delete
        else if (Tools::InRectangle(130, 80, 190, 110, mouseMessage))
            currentm = 6;
        //batch
        else if (Tools::InRectangle(210, 80, 270, 110, mouseMessage))
            currentm = 7;
        else currentm = 0;
    }
    //���ҳ
    if (mouseMessage.message == WM_MOUSEWHEEL)
    {
        if (currentPage == 0 || currentPage == 7)
        {
            currentFirstNumber += ((mouseMessage.wheel > 0) ? -1 : 1);
            if (isImportant && currentFirstNumber >= thingNum[77][12][4] - 5)currentFirstNumber = thingNum[77][12][4] - 5;
            if (!isImportant && currentFirstNumber >= thingNum[getTime.curYear - 2000][getTime.curMon][getTime.curMDay] - 5)currentFirstNumber = thingNum[getTime.curYear - 2000][getTime.curMon][getTime.curMDay] - 5;
            if (currentFirstNumber < 0)currentFirstNumber = 0;
        }
    }
}

//��������ҳ��
void AddThingChance(int curYear,int curMon, int curMDay, bool isBatch)
{
    peekmessage(&mouseMessage, EX_MOUSE);
    if (mouseMessage.message == WM_LBUTTONDOWN)
    {
        //������������
        if (Tools::InRectangle(210, 170, wS.x - 140, 200, mouseMessage))
        {
            InputBox(currentAddName, 25);
        }
        //������������
        if (Tools::InRectangle(210, 240, wS.x - 140, 270, mouseMessage))
        {
            InputBox(currentAddNum, 25);
        }

        //���������
        if (!isBatch || isImportant)
        {
            //ȡ��
            if (Tools::InRectangle(270, 300, 330, 330, mouseMessage))
            {
                isImportant ? currentPage = 7 : currentPage = 0;
            }
            //ȷ��
            if (Tools::InRectangle(190, 300, 250, 330, mouseMessage))
            {
                isImportant ? currentPage = 7 : currentPage = 0;
                theThing x;
                _tcscpy_s(x.theName, 20, currentAddName);
                x.totalNum = _wtoi(currentAddNum);
                x.finishNum = 0;
                tThing[curYear - 2000][curMon][curMDay][thingNum[curYear - 2000][curMon][curMDay]] = x;
                thingNum[curYear - 2000][curMon][curMDay]++;
                _tcscpy_s(currentAddName, 20, _T(""));
                _tcscpy_s(currentAddNum, 20, _T(""));
                OnDownLoad();
            }
        }

        //�������
        if (isBatch && !isImportant)
        {
            //���Ľ�ֹʱ��
            //�������
            if (Tools::InRectangle(230, 300, 300, 340, mouseMessage))
                getTime.dueYear = getTime.getYear();
            //�����·�
            if (Tools::InRectangle(310, 300, 380, 340, mouseMessage))
                getTime.dueMon = getTime.getMon();
            //��������
            if (Tools::InRectangle(390, 300, 460, 340, mouseMessage))
                getTime.dueMDay = getTime.getMDay(getTime.dueMon);
            
            //ȡ��
            if (Tools::InRectangle(270, 360, 330, 390, mouseMessage))
            {
                currentPage = 0;
            }
            //ȷ��
            if (Tools::InRectangle(190, 360, 250, 390, mouseMessage))
            {
                currentPage = 0;
                theThing x;
                _tcscpy_s(x.theName, 20, currentAddName);
                x.totalNum = _wtoi(currentAddNum);
                x.finishNum = 0;

                int i = curYear - 2000, j = curMon, k = curMDay;
                while (1)
                {
                    tThing[i][j][k][thingNum[i][j][k]] = x;
                    thingNum[i][j][k]++;

                    if (i == getTime.dueYear - 2000 && j == getTime.dueMon && k == getTime.dueMDay)
                        break;
                    k++;
                    if (k > getTime.tMon[j])
                    {
                        k = 1;
                        j++;
                    }
                    if (j > 12)
                    {
                        j = 1;
                        i++;
                    }
                }


                _tcscpy_s(currentAddName, 20, _T(""));
                _tcscpy_s(currentAddNum, 20, _T(""));
                OnDownLoad();
            }
        }
    }
}

//�����ǰ����
void OutPutCurrentThings(int curYear, int curMon, int curMDay)
{
    for (int i = currentFirstNumber; i < min(currentFirstNumber + 5, thingNum[curYear - 2000][curMon][curMDay]); i++)
    {
        if (tThing[curYear - 2000][curMon][curMDay][i].finishNum >= tThing[curYear - 2000][curMon][curMDay][i].totalNum)setfillcolor(RGB(0, 255, 0));
        else if (i != currentChooseThing)setfillcolor(RGB(255, 255, 255));
        else setfillcolor(RGB(200, 200, 200));
        fillrectangle(50, 130 + (i - currentFirstNumber) * 60, wS.x - 50, 190 + (i - currentFirstNumber) * 60);
        TCHAR ch[20];
        _tcscpy_s(ch, 20, tThing[curYear - 2000][curMon][curMDay][i].theName);
        settextcolor(RGB(0, 0, 0));
        outtextxy(60, 140 + (i - currentFirstNumber) * 60, ch);
        int totalNum = tThing[curYear - 2000][curMon][curMDay][i].totalNum;
        int finishNum = tThing[curYear - 2000][curMon][curMDay][i].finishNum;
        swprintf_s(ch, _T("%d / %d"), finishNum, totalNum);
        outtextxy(300, 140 + (i - currentFirstNumber) * 60, ch);
    }
}

//����
void OnLoad()
{
    FILE* file;
    errno_t err;
    err = fopen_s(&file, "data/things.bin", "rb");
    if (file != NULL)
    {   
        fseek(file, 0, SEEK_SET);
        fread(tThing, sizeof(tThing), 1, file);
        fclose(file);
    }
    
    err = fopen_s(&file, "data/thingsNum.bin", "rb");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_SET);
        fread(thingNum, sizeof(thingNum), 1, file);
        fclose(file);
    }
}

//����
void OnDownLoad()
{
    FILE* file;
    errno_t err;
    err = fopen_s(&file, "data/things.bin", "wb");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_SET);
        fwrite(tThing, sizeof(tThing), 1, file);
        fclose(file);
    }

    err = fopen_s(&file, "data/thingsNum.bin", "wb");
    if (file != NULL)
    {
        fseek(file, 0, SEEK_SET);
        fwrite(thingNum, sizeof(thingNum), 1, file);
        fclose(file);
    }
}

//��ʱ��
void TimeWait(timer *t)
{
    if (t->tStart == -1)t->tStart = (float)clock();
    else t->tEnd = (float)clock();
}

//��������в���
void ThingsAction(int curYear, int curMon, int curMDay)
{
    peekmessage(&mouseMessage, EX_MOUSE);
    if (mouseMessage.message == WM_LBUTTONDOWN)
    {
        for (int i = currentFirstNumber; i < min(currentFirstNumber + 5, thingNum[curYear - 2000][curMon][curMDay]); i++)
        {
            if (Tools::InRectangle(50, 130 + (i - currentFirstNumber) * 60, wS.x - 50, 190 + (i - currentFirstNumber) * 60, mouseMessage))
                currentChooseThing = i;
        }
    }
    if (mouseMessage.message == WM_LBUTTONDBLCLK)
    {
        if (Tools::InRectangle(50, 130 + (currentChooseThing - currentFirstNumber) * 60, wS.x - 50, 190 + (currentChooseThing - currentFirstNumber) * 60, mouseMessage) && tThing[curYear - 2000][curMon][curMDay][currentChooseThing].finishNum < tThing[curYear - 2000][curMon][curMDay][currentChooseThing].totalNum)
        {
            tThing[curYear - 2000][curMon][curMDay][currentChooseThing].finishNum++;
            OnDownLoad();
        }
    }
    if (mouseMessage.message == WM_RBUTTONDOWN)
    {
        if (Tools::InRectangle(50, 130 + (currentChooseThing - currentFirstNumber) * 60, wS.x - 50, 190 + (currentChooseThing - currentFirstNumber) * 60, mouseMessage) && tThing[curYear - 2000][curMon][curMDay][currentChooseThing].finishNum > 0)
        {
            tThing[curYear - 2000][curMon][curMDay][currentChooseThing].finishNum--;
            OnDownLoad();
        }
    }
    mouseMessage.message = NULL;
}

//ɾ����ǰѡ�������
void DeleteThing(int x)
{
    if (x < 0)return;
    if (isImportant)
    {
        for (int i = x; i < thingNum[77][12][4] - 1; i++)
        {
            tThing[77][12][4][i] = tThing[77][12][4][i + 1];
        }
        thingNum[77][12][4]--;
    }
    else
    {
        for (int i = x; i < thingNum[getTime.curYear - 2000][getTime.curMon][getTime.curMDay] - 1; i++)
        {
            tThing[getTime.curYear - 2000][getTime.curMon][getTime.curMDay][i] = tThing[getTime.curYear - 2000][getTime.curMon][getTime.curMDay][i + 1];
        }
        thingNum[getTime.curYear - 2000][getTime.curMon][getTime.curMDay]--;
    }
}