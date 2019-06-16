#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>
#include <QObject>

class Health: public QGraphicsTextItem
{

public:
    Health(QGraphicsItem * parent = nullptr, int desiredHealth = 3);
    void decrease();
    int getHealth();
    void setHealth(int newHealth);
private:
    int health;
};

#endif // HEALTH_H
