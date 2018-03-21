#include "score.h"
#include <QFont>
#include "game.h"
#include <cstdlib>

#include <QTimer>
extern Game * game;

Score::Score(QGraphicsItem * parent) : QGraphicsTextItem(parent)
{
    points =1;

    setPlainText("Score: " + QString::number(points));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times", 10));
}

void Score::increase()
{
    ++points;
    setPlainText("Score: " + QString::number(points));
    if(points%100 == 0)
    {
        int random_number = rand()%5000+1500;
        QTimer * timer2 = new QTimer;
        QObject::connect(timer2,SIGNAL(timeout()),game->player,SLOT(spawn()));
        timer2->start(random_number);
    }


}

int Score::getScore()
{
    return points;
}
