#include "PowerUp.h"
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QGraphicsScene>
#include "Player.h"
#include "Game.h"

extern Game * game;

PowerUp::PowerUp() : GameObj ()
{
    setPixmap(QPixmap(":/res/images/PowerUpModel.png"));
    QTimer * moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(100);

}
PowerUp::~PowerUp(){
    //qDebug() << "POWERUP DELETED";
}

void PowerUp::move(){
    setPos(x(), y()+10);

    if(y() > game->scene->height()){
        scene()->removeItem(this);
        this->deleteLater();
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i){
        auto type_ptr = colliding_items[i];
        if(typeid(*type_ptr) == typeid(Player)){
            Player * myPlayerPtr = static_cast<Player*>(colliding_items[i]);
            connect(this, SIGNAL(destroyed()), myPlayerPtr, SLOT(powerUp()));
            scene()->removeItem(this);
            this->deleteLater();
        }
    }
}
