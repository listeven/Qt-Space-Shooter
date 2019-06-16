#ifndef BOSS_H
#define BOSS_H
#include "GameObj.h"
#include <QTimer>
#include <QList>
#include "BossHealth.h"

class Boss:public GameObj
{
    Q_OBJECT
public:
    Boss();
    Boss(int vertStep, int horizStep);
private:
    bool movingLeft; // Used for moveMode = 1. If true, Boss is moving left until it reaches the edge. Then movingLeft will be changed to false and Boss will move right until edge.
    int moveMode;   // 0 = Initial movement from top to y = 150. | 1 = Move side to side. | 2 = Move down towards player. | 3 = Move back up to y = 150.
    BossHealth * bossHealth;
    int verticalStep = 5;
    int horizontalStep = 5;
    bool collidedAlready;
    QTimer * attackTimer;
    QTimer * moveTimer;
public slots:
    void move();
    void attack();
    void decreaseHealth();
};

#endif // BOSS_H
