#include "Wall.h"

Wall::Wall()
{
    //ctor
}

Wall::Wall(float x1, float y1, float x2,  float y2)
           : LineA::LineA(x1, y1, x2, y2)
{
    deleted = 0;
}

Wall::~Wall()
{
    //dtor
}
