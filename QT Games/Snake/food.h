#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsPixmapItem>

class Food: public QGraphicsPixmapItem
{
public:
    //contructor that sets image and position
    Food(QGraphicsPixmapItem * parent = nullptr);
};

#endif // FOOD_H
