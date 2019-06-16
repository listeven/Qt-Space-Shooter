#include "BossHealth.h"
#include <QFont>

BossHealth::BossHealth(QGraphicsItem * parent, int desiredHealth): QGraphicsTextItem (parent)
{
    health = desiredHealth;
    setPlainText(QString("Boss Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("ArcadeClassic", 20));
    setZValue(1);

}

void BossHealth::decrease(){
    health--;
    setPlainText(QString("Boss Health: ") + QString::number(health));
}

int BossHealth::getHealth(){
    return health;
}
