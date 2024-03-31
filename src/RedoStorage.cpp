#include "RedoStorage.h"
#define WALL 1
#define NAVPOINT 2

RedoStorage::RedoStorage()
{
    //ctor
    saved_object = 0;
}

RedoStorage::RedoStorage(Wall wall)
                         : RedoStorage::RedoStorage()
{
    obj.wall = wall;
    saved_object = WALL;
}

RedoStorage::RedoStorage(NavPoint point)
                         : RedoStorage::RedoStorage()
{
    obj.navpoint = point;
    saved_object = NAVPOINT;
}

RedoStorage::~RedoStorage()
{
    //dtor
}
