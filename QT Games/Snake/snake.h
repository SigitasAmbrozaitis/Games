#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include "body.h"

class Snake :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Snake(QGraphicsPixmapItem * parent = 0);
    void keyPressEvent(QKeyEvent * event);


public slots:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
private:
    short int flag;
    QTimer * timer;
    void checkCollision();
    void checkBorder();

    //QList<Body *> * body;
    QList<QGraphicsPixmapItem *> body;

    void appendBody();
    void moveBody();
};

#endif // SNAKE_H
