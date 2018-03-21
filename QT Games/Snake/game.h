#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "snake.h"
#include "food.h"
#include "body.h"

#define SCENE_HEIGHT 800
#define SCENE_WIDTH 800
#define SPEED 100
#define MOVE_SIZE 20


class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = 0);

    QGraphicsScene * scene;
    Snake * snake;
    Food * food;
    //QList<QGraphicsPixmapItem *> body;


};

#endif // GAME_H
