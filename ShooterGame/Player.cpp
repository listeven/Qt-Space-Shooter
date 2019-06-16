#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>


Player::Player(): GameObj ()
{
    setPixmap(QPixmap(":/res/images/Spaceship.png"));
    setZValue(1);
    shootDelayMS = 150;
    nextFire = QTime::currentTime();
    powerUpLevel = 0;
    powerUpTimer = new QTimer();

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        pressedKeys += event->key();
    }
    else if(event->key() == Qt::Key_Right){
        pressedKeys += event->key();
    }
    else if(event->key() == Qt::Key_Space){
        pressedKeys += event->key();
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left){
        pressedKeys -= event->key();
    }
    else if(event->key() == Qt::Key_Right){
        pressedKeys -= event->key();
    }
    else if(event->key() == Qt::Key_Space){
        pressedKeys -= event->key();
    }
}


// Maybe split the shoot action into separate function so the rate of fire is different from rate of movement
void Player::performAction(){
    if(pressedKeys.contains(Qt::Key_Space) && QTime::currentTime() > nextFire){
        if(powerUpLevel == 0){
            // Create a bullet
            Bullet * bullet = new Bullet();
            bullet->setPos(x() + pixmap().width()/2 - bullet->pixmap().width()/2 , y() - bullet->pixmap().height());
            scene()->addItem(bullet);
        }
        else if (powerUpLevel == 1) {
            // Power Up allows you to shoot two bullets at once.
            // Place bullets at the 1/4 and 3/4 mark of our player.
            Bullet * bullet1 = new Bullet();
            bullet1->setPos(x() + pixmap().width()/4 - bullet1->pixmap().width()/2 , y() - bullet1->pixmap().height());
            scene()->addItem(bullet1);

            Bullet * bullet2 = new Bullet();
            bullet2->setPos(x() + 3*(pixmap().width()/4) - bullet2->pixmap().width()/2 , y() - bullet2->pixmap().height());
            scene()->addItem(bullet2);
        }

        nextFire = QTime::currentTime().addMSecs(shootDelayMS);
    }
}

void Player::performMovement(){
    int step = 10;
    double rightBound = scene()->width() - pixmap().width();

    if(pressedKeys.contains(Qt::Key_Left)){
        if(x() > 0 && x() >= step){
            setPos(x()-step, y());
        }
        else if(x() > 0 && x() < step){
            setPos(0, y());
        }
    }

    if(pressedKeys.contains(Qt::Key_Right)){
        if(x() < rightBound && x() <= rightBound - step){
            setPos(x()+step,y());
        }
        else if(x() < rightBound && x() > rightBound - step){
            setPos(rightBound, y());
        }
    }
}

void Player::powerUp(){
    powerUpLevel = 1;

    powerUpTimer->start(10*1000);
    connect(powerUpTimer, SIGNAL(timeout()), this, SLOT(powerDown()));
}

void Player::powerDown(){
    powerUpLevel = 0;
}


