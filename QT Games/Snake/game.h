#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "head.h"
#include "body.h"
#include "food.h"

#define WIDTH 1200
#define HEIGHT 900
#define SPEED 100
#define SIZE 30

class Game : public QGraphicsView
{
public:
   Game();

   QGraphicsScene * scene;  //game scene
   Head * head;             //snake head, all input from there
   QList<Body *> body;      //snake body, follows head
   Food * food;             //food randomly placed(loacation) in scene


};

#endif // GAME_H
