#include "body.h"
#include "game.h"
#include <QDebug>
extern Game * game;


Body::Body(QGraphicsPixmapItem * parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/Recources/snake.png").scaled(MOVE_SIZE, MOVE_SIZE,Qt::KeepAspectRatio));
    qDebug() <<"nauja: ";
    //setPos(0,0);
    //qDebug() <<"nauja: ";
    //game->scene->addItem(this);
    //qDebug() <<"nauja: ";

}
