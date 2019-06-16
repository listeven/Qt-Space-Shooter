#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include "Game.h"

extern Game * game;

Bullet::Bullet(): GameObj ()
{
    // Set Pixmap
    setPixmap(QPixmap(":/res/images/Bullet.png"));

    // Connect
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this, SLOT(move()));
    timer->start(50);
}

void Bullet::move(){
    // Check if the bullet is colliding with enemy. Destroy both if it is.
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for(int i = 0; i < colliding_items.size(); ++i){
        auto tempPtr = colliding_items[i];
        if(typeid(*tempPtr) == typeid(Enemy)){
            // Increase score
            game->score->increase();
            //Enemy * enemyPtr = static_cast<Enemy*>(colliding_items[i]);

            connect(this, SIGNAL(enemyDefeated(int)), static_cast<Enemy*>(colliding_items[i]), SLOT(spawnPowerUp(int)));
            emit enemyDefeated(game->score->getScore());

            // Remove and delete items
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            static_cast<GameObj*>(colliding_items[i])->deleteLater();
            this->deleteLater();
            return;
        }
        else if(typeid(*tempPtr) == typeid(Boss)){
            //Boss * bossPtr = static_cast<Boss*>(colliding_items[i]);
            connect(this, SIGNAL(bossHit()), static_cast<Boss*>(colliding_items[i]), SLOT(decreaseHealth()));
            emit bossHit();

            scene()->removeItem(this);
            this->deleteLater();
            return;
        }
    }

    // Move the bullet up
    setPos(x(), y()-20);
    if(pos().y() + pixmap().height() < 0){
        scene()->removeItem(this);
        this->deleteLater();
    }
}
