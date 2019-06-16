#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>


class Score: public QGraphicsTextItem
{
public:
    Score(QGraphicsItem * parent = nullptr);
    void increase();
    int getScore();
    void setScore(int newScore);
    void setText(QString newText);
private:
    int score;
    QString text;
};

#endif // SCORE_H
