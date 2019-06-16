#ifndef POWERUP_H
#define POWERUP_H
#include "GameObj.h"

class PowerUp : public GameObj
{
    Q_OBJECT

public:
    PowerUp();
    ~PowerUp();
public slots:
    void move();
};

#endif // POWERUP_H
