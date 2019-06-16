#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "Enemy.h"
#include "Boss.h"
#include "Bullet.h"
#include "GameMsg.h"
#include "PowerUp.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:

    Game(QWidget * parent=nullptr);

    QGraphicsScene * scene;
    Player * player;
    Score * score;
    Score * highScoreText;
    Health * playerHealth;
    QTimer * enemyTimer;
    QTimer * actionTimer;
    QTimer * movementTimer;
    bool gameRunning;
    void endGame();
    void resetGame();

private:
    GameMsg * gameOverMsg;
    int highScore = 0;
    int enemyCounter;
    int wave;
    double enemySpeed = 4.0;
    int bossSpeed = 6;
    void drawWindow();
    void runGame();
    void drawGameOverMsg();
public slots:
    void spawn();
    void spawnBoss();
};

#endif // GAME_H
