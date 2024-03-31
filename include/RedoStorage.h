#ifndef REDOSTORAGE_H
#define REDOSTORAGE_H

#include "Wall.h"

#include "NavPoint.h"

struct Object
{

    Wall wall;
    NavPoint navpoint;

    //after deletion (mark deleted) and then undo deletion (unmark deleted), this object is to be marked deleted again
    void *object_to_mark_deleted;
};

class RedoStorage
{
    public:
        RedoStorage();
        RedoStorage(Wall wall); //type 1
        //replace NavPoint with real class
        RedoStorage(NavPoint);
        //and so on
        unsigned int saved_object;

        Object obj;

        virtual ~RedoStorage();

    protected:

    private:
};

#endif // REDOSTORAGE_H
