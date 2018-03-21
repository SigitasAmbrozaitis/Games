#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem
{
public:
    Health(QGraphicsItem *parent = 0 );
public:
    void decrease();
    int getHealth();
private:
    int hp;
};

#endif // HEALTH_H
