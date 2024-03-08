#ifndef LINEA_H
#define LINEA_H

#include "LineEq.h"
#include "Point_float.h"


class LineA : public LineEq
{
    public:
        LineA();
        LineA(float x1, float y1, float x2,  float y2);
        void calcABC();
        bool parallel(LineEq line);
        bool almost_equal(float a, float b);
        Point_float intersection(LineEq line);
        bool in_range(float x, float y);
        float shortest_dist(float x, float y);
        virtual ~LineA();

        // returns a perpendicular to this line passing via (x1, y1)
        LineA normal(float x1, float y1);
        //Point_float intersection_point;

    protected:

    private:
};

#endif // LINEA_H
