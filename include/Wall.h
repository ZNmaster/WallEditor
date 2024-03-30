#ifndef WALL_H
#define WALL_H

#include <LineA.h>


class Wall : public LineA
{
    public:
        Wall();
        Wall(float x1, float y1, float x2,  float y2);
        bool deleted;
        virtual ~Wall();

    protected:

    private:
};

#endif // WALL_H
