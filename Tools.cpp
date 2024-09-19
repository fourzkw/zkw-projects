#include "Tools.h"

bool Tools::InRectangle(int x1, int y1, int x2, int y2, ExMessage m)
{
    if (x1 <= m.x && m.x <= x2 && y1 <= m.y && m.y <= y2)
        return 1;
    else return 0;
}