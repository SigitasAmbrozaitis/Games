#include "food.h"
#include <cstdlib>
#include "game.h"
extern Game * game;
Food::Food(QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/colors/red.png").scaled(SIZE,SIZE, Qt::KeepAspectRatio));
    int rnd1 =rand() % (WIDTH/SIZE);
    int rnd2 =rand() % (HEIGHT/SIZE);
    setPos(rnd1 * SIZE, rnd2 * SIZE);
}
