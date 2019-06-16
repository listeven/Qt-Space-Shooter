#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include <QObject>
#include <QGraphicsPixmapItem>

// Base class for our game objects. Makes it easier to delete them
class GameObj:public QObject, public QGraphicsPixmapItem
{
public:
    GameObj();
};

#endif // GAMEOBJ_H
