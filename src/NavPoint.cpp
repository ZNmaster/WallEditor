#include "NavPoint.h"

NavPoint::NavPoint()
{
    //ctor
}

NavPoint::NavPoint(unsigned int x1, unsigned int y1)
                   : EPoint_int::EPoint_int(x1, y1)
{

}

NavPoint::~NavPoint()
{
    //dtor
}
