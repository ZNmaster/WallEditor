#ifndef NAVPOINT_H
#define NAVPOINT_H

#include <Geometry.h>


class NavPoint : public EPoint_int
{
    public:
        NavPoint();
        NavPoint(unsigned int x1, unsigned int y1);
        virtual ~NavPoint();

    protected:

    private:
};

#endif // NAVPOINT_H
