#ifndef BOSSHEALTH_H
#define BOSSHEALTH_H
#include <QGraphicsTextItem>


class BossHealth: public QGraphicsTextItem
{
public:
    BossHealth(QGraphicsItem * parent = nullptr, int desiredHealth = 100);
    void decrease();
    int getHealth();
private:
    int health;
};

#endif // BOSSHEALTH_H
