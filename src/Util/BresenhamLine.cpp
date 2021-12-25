#include "BresenhamLine.h"

#include <algorithm>

void BresenhamLineCaseA(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints)
{
    int x;
    int y;

    int endX;
    int endY;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int doubleDx = dx + dx;
    int doubleDy = dy + dy;

    int pointBound;
    int incrementor = 1;

    if (dy < dx)
    {
        // 기울기가 완만하면(1보다 작으면) 예각이다.
        // 이 경우에는 x축을 기준으로 p값을 체크해서 y를 증가시켜야 한다.
        // -----
        
        // 처리 기준이 x축 양의 방향이기 때문에 x값이 작은 점을 기준으로 삼는다.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 제 3팔분면, 제 4팔분면, 제 5팔분면, 제 6팔분면을 무효화시킨다.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dy가 음수였던 상황(abs()를 적용시키면 dy는 x축 대칭이 되기 때문에 incrementor도 대칭시켜야 한다.)
        if (endY - y < 0)
        {
            incrementor = -1;
        }

        pointBound = doubleDy - dx; // p0 = 2dy - dx

        while (x <= endX)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            x++;

            if (pointBound < 0)
            {
                pointBound = pointBound + doubleDy; // pnext = pk + 2dy
            }
            else
            {
                pointBound = pointBound + doubleDy - doubleDx; // pnext = pk + 2dy - 2dx

                y += incrementor;
            }
        }
    }
    else
    {
        // 기울기가 가파르면(1보다 크면) 둔각이다.
        // 이 경우에는 y축을 기준으로 p값을 체크해서 x를 증가시켜야 한다.
        // -----

        // 처리 기준이 y축 양의 방향이기 때문에 x값이 작은 점을 기준으로 삼는다.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 제 3팔분면, 제 4팔분면, 제 5팔분면, 제 6팔분면을 무효화시킨다.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dx가 음수였던 상황(abs()를 적용시키면 dx는 y축 대칭이 되기 때문에 incrementor도 대칭시켜야 한다.)
        if (endX - x < 0)
        {
            incrementor = -1;
        }

        pointBound = doubleDx - dy; // p0 = 2dx - dy

        while (y <= endY)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            y++;

            if (pointBound < 0)
            {
                pointBound = pointBound + doubleDx; // pnext = pk + 2dx
            }
            else
            {
                pointBound = pointBound + doubleDx - doubleDy; // pnext = pk + 2dx - 2dy

                x += incrementor;
            }
        }
    }
}

void BresenhamLineCaseB(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints)
{
    // 항상 팔분면을 떠올리자.
    // -----
    int width  = abs(x2 - x1);
    int height = abs(y2 - y1);

    int doubleWidth  = width + width;
    int doubleHeight = height + height;

    int dx;
    int dy;

    int x;
    int y;

    int endX;
    int endY;

    int incrementor = 1;

    if (width > height)
    {
        // 처리 기준이 x축 양의 방향이기 때문에 x값이 작은 점을 기준으로 삼는다.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 제 3팔분면, 제 4팔분면, 제 5팔분면, 제 6팔분면을 무효화시킨다.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // 기울기가 음수인 상황
        if (endY - y < 0)
        {
            incrementor = -1;
        }

        // 기울기가 완만하여 예각을 이룬다.
        // -----
        dx = width;
        dy = doubleHeight; // 2 * h

        while (x <= endX)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            if (dy - dx < 0)
            {
                // 평행 이동 -> 2h 누적
                dy += doubleHeight;
            }
            else
            {
                // 평행 이동 후 아래로 한 칸 -> 2h - 2w 누적
                dy += doubleHeight;
                dx += doubleWidth; // dy - dx라 결국 빼기 때문에 덧셈으로 누적

                y += incrementor;
            }

            x++;
        }
    }
    else
    {
        // 처리 기준이 y축 양의 방향이기 때문에 x값이 작은 점을 기준으로 삼는다.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // 제 3팔분면, 제 4팔분면, 제 5팔분면, 제 6팔분면을 무효화시킨다.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // 기울기가 음수인 상황
        if (endX - x < 0)
        {
            incrementor = -1;
        }

        // 기울기가 가파라 둔각을 이룬다.
        // -----
        dx = doubleWidth; // 2 * w
        dy = height;

        while (y <= endY)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);
    
            if (dx - dy < 0)
            {
                // 평행 이동 -> 2w 누적
                dx += doubleWidth;
            }
            else
            {
                // 평행 이동 후 아래로 한 칸 -> 2w - 2h 누적
                dx += doubleWidth;
                dy += doubleHeight; // dx - dy라 결국 빼기 때문에 덧셈으로 누적
    
                x += incrementor;
            }
    
            y++;
        }
    }
}
