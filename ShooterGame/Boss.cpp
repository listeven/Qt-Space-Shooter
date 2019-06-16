#include "Boss.h"
#include "Game.h"

extern Game * game;
const int attackInterval = 5*1000;
const int bossInitialHeight = 100;

Boss::Boss(): GameObj ()
{
    // Set image and starting position
    setPixmap(QPixmap(":/res/images/Boss.png"));
    setPos(game->scene->width()/2 - pixmap().width()/2, 0);

    // Set default values
    moveMode = 0;
    movingLeft = true;
    collidedAlready = false;

    // Set up the health
    bossHealth = new BossHealth();
    bossHealth->setPos(game->scene->width()/2 - bossHealth->boundingRect().width()/2, bossHealth->y() + 25);
    game->scene->addItem(bossHealth);

    moveTimer = new QTimer();
    connect(moveTimer,SIGNAL(timeout()),this, SLOT(move()));
    moveTimer->start(50);

    attackTimer = new QTimer();
    connect(attackTimer, SIGNAL(timeout()), this, SLOT(attack()));
}

Boss::Boss(int horizStep, int vertStep):Boss()
{
     horizontalStep = horizStep;
     verticalStep = vertStep;
}

void Boss::attack(){
    moveMode = 2;
    attackTimer->stop();
}

void Boss::decreaseHealth(){
    if(bossHealth->getHealth() > 1)
    {
        bossHealth->decrease();
    }
    else {
        bossHealth->decrease();
        for(int i = 0; i < 10; ++i){
            game->score->increase();
        }

        game->enemyTimer->start();
        scene()->removeItem(bossHealth);
        scene()->removeItem(this);
        bossHealth->deleteLater();
        this->deleteLater();
    }
}

void Boss::move(){
    // 0 = Initial movement from top to y = 150. | 1 = Move side to side. | 2 = Move down towards player. | 3 = Move back up to y = 150.
    switch (moveMode) {
    case 0:{
        if(y() < bossInitialHeight && y() < bossInitialHeight - verticalStep){
            setPos(x(), y() + verticalStep);
        }
        else if(y() < bossInitialHeight && y() >= bossInitialHeight - verticalStep){
            setPos(x(), bossInitialHeight);
        }
        else{
            moveMode = 1;
            attackTimer->start(attackInterval);
        }
        break;
    }
    case 1:{
        double rightBound = game->scene->width() - pixmap().width();

        if(movingLeft){
            if(x() > 0 && x() > horizontalStep){
                setPos(x()-horizontalStep, y());
            }
            else if(x() > 0 && x() <= horizontalStep){
                setPos(0, y());
                movingLeft = false;
            }
        }
        else{
            if(x() < rightBound && x() < rightBound - horizontalStep){
                setPos(x()+horizontalStep, y());
            }
            else if(x() < rightBound && x() >= rightBound - horizontalStep){
                setPos(rightBound, y());
                movingLeft = true;
            }
        }
        break;
    }
    case 2:{
        setPos(x(), y() + verticalStep);
        if(y() >= game->scene->height() - pixmap().height()){
            moveMode = 3;
        }

        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i = 0; i < colliding_items.size(); ++i){
            auto tempPtr = colliding_items[i];
            if(typeid(*tempPtr) == typeid(Player)){
                game->playerHealth->decrease();
                moveMode = 3;
                collidedAlready = true;
            }
        }
        break;
    }
    case 3:{
        if(y() > bossInitialHeight && y() > bossInitialHeight + verticalStep){
            setPos(x(), y() - verticalStep);
        }
        else if(y() > bossInitialHeight && y() <= bossInitialHeight + verticalStep){
            setPos(x(), bossInitialHeight);
        }
        else{
            moveMode = 1;
            attackTimer->start(attackInterval);
        }

        if(!collidedAlready){
            QList<QGraphicsItem *> colliding_items = collidingItems();
            for(int i = 0; i < colliding_items.size(); ++i){
                auto tempPtr = colliding_items[i];
                if(typeid(*tempPtr) == typeid(Player)){
                    game->playerHealth->decrease();
                    collidedAlready = true;
                }
            }
        }


        break;
    }

    }
}










