    #include "Game.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>
#include <QBrush>
#include <QImage>
#include <typeinfo>

// Enemy counter. Boss "mode" vs regular enemies mode. Save high score? Fix art of power up. Maybe make art for boss.
// Game over screen
// add list of objects

Game::Game(QWidget *)
{

    drawWindow();
    runGame();
    show();
}

// Function to draw the game window
void Game::drawWindow()
{
    // Create our Scene
    // Container of all my game objects. Kinda like a world?
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setStickyFocus(true);
    setBackgroundBrush(QBrush(QImage(":/res/images/StarryBG.png")));

    // Set the window to open at 800x600. Set View and Scene to match.
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    // Create a Player to place into our scene.
    player = new Player();

    // Player starts centered at bottom.
    player->setPos(width()/2 - player->pixmap().width()/2, height() - player->pixmap().height());

    // Make our rect focusable and focused for our key events
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // Add the item to scene
    scene->addItem(player);

    // Create and add high score text
    highScoreText = new Score();
    highScoreText->setText(QString("High Score: "));
    scene->addItem(highScoreText);

    // Create the score
    score = new Score();
    score->setPos(score->x(), score->y() + 25);
    scene->addItem(score);


    // Create the health
    playerHealth = new Health();
    playerHealth->setPos(playerHealth->x(), playerHealth->y() + 50);
    scene->addItem(playerHealth);
}

void Game::runGame()
{
    enemyCounter = 0;
    wave = 0;
    // Spawn Enemies using a QTimer
    enemyTimer = new QTimer();
    QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawn()));
    enemyTimer->start(4000);


    // Use timer to perform actions based on what keys are being pressed
    actionTimer = new QTimer();
    QObject::connect(actionTimer, SIGNAL(timeout()), player, SLOT(performAction()));
    actionTimer->start(10);

    movementTimer = new QTimer();
    QObject::connect(movementTimer, SIGNAL(timeout()), player, SLOT(performMovement()));
    movementTimer->start(40);

}

void Game::endGame()
{
    enemyTimer->stop();
    actionTimer->stop();
    movementTimer->stop();
    QList<QGraphicsItem *> sceneItems = items();
    qDebug() << "SIZE: " << sceneItems.size();
    for(int i = 0; i < sceneItems.size(); ++i){
        auto tempPtr = sceneItems[i];

        qDebug() << "FOR LOOP: " << i << " " << typeid(*tempPtr).name();

        if( typeid(*tempPtr) == typeid(Enemy) || typeid(*tempPtr) == typeid(Boss)
                || typeid(*tempPtr) == typeid(Bullet) || typeid(*tempPtr) == typeid(PowerUp)
                || typeid(*tempPtr) == typeid(Player)){
            qDebug() << "DELETING";
            scene->removeItem(sceneItems[i]);
            static_cast<GameObj*>(tempPtr)->deleteLater();
        }
        else if( typeid(*tempPtr) == typeid(BossHealth)){
            qDebug() << "Deleting BOSSHEALTH";
            scene->removeItem(sceneItems[i]);
            static_cast<BossHealth*>(tempPtr)->deleteLater();
        }
    }
    if(score->getScore() > highScore){
        highScore = score->getScore();
    }
    // Draw game over msg
    drawGameOverMsg();

}

void Game::drawGameOverMsg(){
    gameOverMsg = new GameMsg();
    scene->addItem(gameOverMsg);
    gameOverMsg->setFlag(QGraphicsItem::ItemIsFocusable);
    gameOverMsg->setFocus();

}

void Game::resetGame()
{

    scene->removeItem(gameOverMsg);
    gameOverMsg->deleteLater();

    highScoreText->setScore(highScore);

    player = new Player();
    player->setPos(width()/2 - player->pixmap().width()/2, height() - player->pixmap().height());
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    playerHealth->setHealth(1);
    score->setScore(0);
    wave = 0;
    enemyCounter = 0;
    enemyTimer->start();
    QObject::connect(actionTimer, SIGNAL(timeout()), player, SLOT(performAction()));
    actionTimer->start();
    QObject::connect(movementTimer, SIGNAL(timeout()), player, SLOT(performMovement()));
    movementTimer->start();
}

void Game::spawn()
{
    if(wave == 5){
        enemyTimer->stop();
        wave = 0;
        QTimer::singleShot(3000, this, SLOT(spawnBoss()));
        if(enemySpeed < 10){
            enemySpeed += 1;
        }
    }
    else{
        // Spawn in a wave of 5 enemies
        int enemyWidth = 100;
        Enemy * enemy1 = new Enemy(scene->width()/2 - 2.5* enemyWidth - 40, 0, enemySpeed);
        Enemy * enemy2 = new Enemy(scene->width()/2 - 1.5*enemyWidth - 20, 0, enemySpeed);
        Enemy * enemy3 = new Enemy(scene->width()/2 - enemyWidth/2, 0, enemySpeed);
        Enemy * enemy4 = new Enemy(scene->width()/2 + enemyWidth/2 + 20, 0, enemySpeed);
        Enemy * enemy5 = new Enemy(scene->width()/2 + 1.5*enemyWidth + 40, 0, enemySpeed);
        scene->addItem(enemy1);
        scene->addItem(enemy2);
        scene->addItem(enemy3);
        scene->addItem(enemy4);
        scene->addItem(enemy5);
        wave++;

    }
}

void Game::spawnBoss()
{
    Boss * theBoss = new Boss(bossSpeed, bossSpeed);
    scene->addItem(theBoss);
    if(bossSpeed < 16){
        bossSpeed+=2;
    }
}

/*
 * //OLD SPAWN METHOD
void Game::spawn()
{
    // Create a boss every 10 enemies
    if(enemyCounter == 10){
        enemyTimer->stop();
        enemyCounter = 0;
        Boss * theBoss = new Boss();
        scene->addItem(theBoss);
    }
    else{
        // Create enemy to spawn in
        Enemy * enemy = new Enemy();
        scene->addItem(enemy);
        enemyCounter++;
    }

    qDebug() << "Enemy Counter: " << enemyCounter;


}
*/
