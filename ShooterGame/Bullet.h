#ifndef BULLET_H
#define BULLET_H
#include "GameObj.h"

class Bullet : public GameObj
{
    // Macro? Need QObject to use Signals/Slots.
    Q_OBJECT

public:
    Bullet();
signals:
    void enemyDefeated(int totalKills);     // Pass total kills so we can spawn the power up based on the score.
    void bossHit();
public slots:
    void move();
};

#endif // BULLET_H
