#include "Health.h"
#include <QFont>
#include "Game.h"

extern Game * game;

Health::Health(QGraphicsItem * parent, int desiredHealth): QGraphicsTextItem (parent)
{
    health = desiredHealth;
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("ArcadeClassic", 16));
    setZValue(1);
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
    if(health == 0){
        game->endGame();
    }
}

int Health::getHealth(){
    return health;
}

void Health::setHealth(int newHealth)
{
    health = newHealth;
    setPlainText(QString("Health: ") + QString::number(health));
}

