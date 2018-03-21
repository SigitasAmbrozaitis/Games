#include "food.h"
#include "game.h"
#include <cstdlib>
#include <QDebug>
extern Game * game;
Food::Food(QGraphicsPixmapItem * parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/Recources/apple.png").scaled(MOVE_SIZE, MOVE_SIZE,Qt::KeepAspectRatio));

    int random1=(rand()%(SCENE_HEIGHT / MOVE_SIZE)) * MOVE_SIZE;
    int random2 = (rand()%(SCENE_WIDTH / MOVE_SIZE)) * MOVE_SIZE;
    setPos(random2,random1);
    qDebug() << random1 << random2;
}
