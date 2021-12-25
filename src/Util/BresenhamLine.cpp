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
        // ���Ⱑ �ϸ��ϸ�(1���� ������) �����̴�.
        // �� ��쿡�� x���� �������� p���� üũ�ؼ� y�� �������Ѿ� �Ѵ�.
        // -----
        
        // ó�� ������ x�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // �� 3�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 6�Ⱥи��� ��ȿȭ��Ų��.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dy�� �������� ��Ȳ(abs()�� �����Ű�� dy�� x�� ��Ī�� �Ǳ� ������ incrementor�� ��Ī���Ѿ� �Ѵ�.)
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
        // ���Ⱑ ���ĸ���(1���� ũ��) �а��̴�.
        // �� ��쿡�� y���� �������� p���� üũ�ؼ� x�� �������Ѿ� �Ѵ�.
        // -----

        // ó�� ������ y�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // �� 3�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 6�Ⱥи��� ��ȿȭ��Ų��.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // dx�� �������� ��Ȳ(abs()�� �����Ű�� dx�� y�� ��Ī�� �Ǳ� ������ incrementor�� ��Ī���Ѿ� �Ѵ�.)
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
    // �׻� �Ⱥи��� ���ø���.
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
        // ó�� ������ x�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (x1 < x2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // �� 3�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 6�Ⱥи��� ��ȿȭ��Ų��.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // ���Ⱑ ������ ��Ȳ
        if (endY - y < 0)
        {
            incrementor = -1;
        }

        // ���Ⱑ �ϸ��Ͽ� ������ �̷��.
        // -----
        dx = width;
        dy = doubleHeight; // 2 * h

        while (x <= endX)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);

            if (dy - dx < 0)
            {
                // ���� �̵� -> 2h ����
                dy += doubleHeight;
            }
            else
            {
                // ���� �̵� �� �Ʒ��� �� ĭ -> 2h - 2w ����
                dy += doubleHeight;
                dx += doubleWidth; // dy - dx�� �ᱹ ���� ������ �������� ����

                y += incrementor;
            }

            x++;
        }
    }
    else
    {
        // ó�� ������ y�� ���� �����̱� ������ x���� ���� ���� �������� ��´�.
        if (y1 < y2)
        {
            x = x1;
            y = y1;

            endX = x2;
            endY = y2;
        }
        else
        {
            // �� 3�Ⱥи�, �� 4�Ⱥи�, �� 5�Ⱥи�, �� 6�Ⱥи��� ��ȿȭ��Ų��.
            x = x2;
            y = y2;

            endX = x1;
            endY = y1;
        }

        // ���Ⱑ ������ ��Ȳ
        if (endX - x < 0)
        {
            incrementor = -1;
        }

        // ���Ⱑ ���Ķ� �а��� �̷��.
        // -----
        dx = doubleWidth; // 2 * w
        dy = height;

        while (y <= endY)
        {
            BresenhamPoint p{ x, y };
            outPoints->emplace_back(p);
    
            if (dx - dy < 0)
            {
                // ���� �̵� -> 2w ����
                dx += doubleWidth;
            }
            else
            {
                // ���� �̵� �� �Ʒ��� �� ĭ -> 2w - 2h ����
                dx += doubleWidth;
                dy += doubleHeight; // dx - dy�� �ᱹ ���� ������ �������� ����
    
                x += incrementor;
            }
    
            y++;
        }
    }
}
