#include "LineA.h"
#include <cmath>
#include "Geometry.h"
#include <algorithm>
LineA::LineA()
{
    vertical = 0;
    horizontal = 0;
    x_start = 0;
    y_start = 0;
    x_end = 0;
    y_end = 0;
    //ctor
}

LineA::LineA(float x1, float y1, float x2,  float y2)
             : LineEq::LineEq(x1, y1, x2, y2)
{



    //ctor
}


LineA LineA::normal(float x1, float y1)
{

    if (vertical)
    {
        //return horizontal line passing via (x1, y1)
        return LineA(x1, y1, x_start, y1);

    }
    else if (horizontal)
    {
        //return vertical line passing via (x1, y1)
        return LineA(x1,y1, x1, y_start);

    }

    else
    {
        //calculating and returning normal line y=ax+b from | y - y1 = (-1/a)*(x - x1) or y = (-1/a)*x + b_new
        float a1 = a;
        float b1 = b;

        float a2 = -1 / a;
        float b2 = 1 / a * x1 + y1;

        float x0 = (b2 - b1) / (a1 - a2);
        float y0 = a * x0 + b;

        return LineA(x1, y1, x0, y0);

    }

}

bool LineA::parallel(LineEq line)
{
    if ((horizontal && line.horizontal) || (vertical && line.vertical))
        return true;
    else
        return almost_equal(a, line.a);
}

bool LineA::almost_equal(float a, float b)
{
    float sigfig = 0.0000001;

    return (abs(a-b) < sigfig) ? true : false;

}

Point_float LineA::intersection(LineEq line)
{
    if (parallel(line))
    {
        return EPoint_float(sqrt(-1), sqrt(-1));
    }
    else if(vertical)
    {
        float x = x_start;
        float y = line.a * x + line.b;

        return EPoint_float(x, y);
    }
    else if(line.vertical)
    {
        float x = line.x_start;
        float y = a * x + b;

        return EPoint_float(x, y);
    }
    else
    {
        float x = (line.b - b) / (a - line.a);
        float y = a * x + b;

        return EPoint_float(x, y);
    }
}

bool LineA::in_range(float x, float y)
{
    float x_max = x_end;
    float x_min = x_start;
    if (x_max < x_min)
    {
        std::swap(x_max, x_min);
    }

    float y_max = y_end;
    float y_min = y_start;
    if (y_max < y_min)
    {
        std::swap(y_max, y_min);
    }

    return (((x <= x_max) && (x >= x_min)) && ((y <= y_max) && (y >= y_min)));
}

float LineA::shortest_dist(float x, float y)
{
    if (!in_range(x, y))
    {
        Line line1(x, y, x_start, y_start);
        Line line2(x, y, x_end, y_end);

        return std::min(line1.len, line2.len);
    }

    else
    {
        LineA line = normal(x, y);

        return line.len;
    }
}

LineA::~LineA()
{
    //dtor
}
