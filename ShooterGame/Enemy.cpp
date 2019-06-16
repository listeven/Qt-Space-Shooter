#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> // rand()
#include <QDebug>
#include "Game.h"
#include <QList>
#include "PowerUp.h"

extern Game * game;

// Default constructor
Enemy::Enemy(): GameObj ()
{

    setPixmap(QPixmap(":/res/images/EnemyUFO.png"));

    // Get a random starting x position for our enemy
    int random_num = rand() % static_cast<int>(game->scene->width() - pixmap().width());
    setPos(random_num, 0);
    moveSpeed = 5.0;
    // Connect a timer to move the enemy
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);
}

// Creates an enemy at the specified x and y values with specified speed
Enemy::Enemy(double x, double y, double speed) : GameObj ()
{
    setPixmap(QPixmap(":/res/images/EnemyUFO.png"));
    setPos(x,y);
    moveSpeed = speed;
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(100);
}

Enemy::~Enemy(){
    qDebug() << "ENEMY DELETED!!!";
}
void Enemy::move(){
    // Move down
    setPos(x(), y() + moveSpeed);
    if(y() > game->scene->height()){
        scene()->removeItem(this);
        this->deleteLater();
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    //for(int i = 0; i < colliding_items.size(); ++i){
    foreach(QGraphicsItem* gItem, colliding_items){
        //auto tempPtr = colliding_items[i];
        if(typeid(*gItem) == typeid(Player)){
            game->playerHealth->decrease();
            if(game->playerHealth->getHealth() != 0){
                scene()->removeItem(this);
                this->deleteLater();
            }

        }
    }
}

void Enemy::spawnPowerUp(int totalKills){
    if(totalKills % 5 == 0){
        PowerUp * powerUp = new PowerUp();
        powerUp->setPos(x() + pixmap().width()/2, y());
        scene()->addItem(powerUp);
    }
}
