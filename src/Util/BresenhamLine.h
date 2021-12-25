#pragma once

#include <vector>

struct BresenhamPoint
{
    int x;
    int y;
};

void BresenhamLineCaseA(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints);
void BresenhamLineCaseB(int x1, int y1, int x2, int y2, std::vector<BresenhamPoint>* outPoints);
