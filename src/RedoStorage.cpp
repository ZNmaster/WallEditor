#include "RedoStorage.h"
#define WALL 1
#define NAVPOINT 2
#define MARKDELETED 3

RedoStorage::RedoStorage()
{
    //ctor
    saved_object = 0;
    obj.object_to_mark_deleted = nullptr;
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

RedoStorage::RedoStorage(void *to_delete)
                         : RedoStorage::RedoStorage()
{
    obj.object_to_mark_deleted = to_delete;
    saved_object = MARKDELETED;
}

RedoStorage::~RedoStorage()
{
    //dtor
}
