#include "GameMsg.h"
#include "Game.h"
#include <QFont>
#include <QDebug>
#include <QKeyEvent>

extern Game * game;

GameMsg::GameMsg(): QGraphicsItemGroup (), QObject ()
{
    /*
    msgBox = new QGraphicsPixmapItem();
    msgBox->setPixmap(QPixmap(":/res/images/textBox.png"));
    msgBox->setPos(game->scene->width()/2 - msgBox->pixmap().width()/2, game->scene->height()/2 - msgBox->pixmap().height()/2);
    */
    msg1 = new QGraphicsTextItem();
    msg1->setFont(QFont("ArcadeClassic", 18));
    msg1->setPlainText(QString("Game Over"));
    msg1->setDefaultTextColor(Qt::white);
    msg1->setZValue(1);
    msg1->setPos(game->scene->width()/2 - msg1->boundingRect().width()/2,  250);

    msg2 = new QGraphicsTextItem();
    msg2->setFont(QFont("ArcadeClassic", 18));
    msg2->setPlainText(QString("Press Space Bar To Start A New Game"));
    msg2->setDefaultTextColor(Qt::white);
    msg2->setZValue(1);
    msg2->setPos(game->scene->width()/2 - msg2->boundingRect().width()/2,  325);

    //addToGroup(msgBox);
    addToGroup(msg1);
    addToGroup(msg2);

}

void GameMsg::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        game->resetGame();
    }
}

