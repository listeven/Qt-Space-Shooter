#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem (parent)
{
    // Initialize score to 0
    score = 0;
    text = QString("Score: ");

    // Draw the text
    setPlainText(text + QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("ArcadeClassic", 16));
    setZValue(1);

}

void Score::increase()
{
    score++;
    setPlainText(text + QString::number(score));
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int newScore)
{
    score = newScore;
    setPlainText(text + QString::number(score));
}

void Score::setText(QString newText)
{
    text = newText;
    setPlainText(text + QString::number(score));
}
