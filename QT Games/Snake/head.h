#ifndef HEAD_H
#define HEAD_H

#include "body.h"
#include <QKeyEvent>
#include <QObject>

class Head:public QObject,  public Body
{
    Q_OBJECT
public:
    Head(int x, int y,QGraphicsPixmapItem * parent=nullptr);
    void keyPressEvent(QKeyEvent * event);  //sets head dirrection

public slots:
    void move();    //connected to timer, moves head in set dirrection, updates body, ckecks collisions and viability

private:
    char moving;    //head direction
    int X;          //head x location
    int Y;          //head y location
    bool flag;      //true if key event is registered
    QTimer * timer;

    void updateBody();      //updates body nodes, starts from the tail up to head
    void stopGame();        //stops game, epties scene and deletes all elements, called when exists given view or snake head collides with body
    void checkViability();  //checks if snake is not out of bounds, if it is stopGame() is called
};

#endif // HEAD_H
