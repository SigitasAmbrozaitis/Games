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
    void keyPressEvent(QKeyEvent * event);

public slots:
    void move();

private:
    char moving;
    int X;
    int Y;
    bool flag;
    QTimer * timer;

    void updateBody();
    void stopGame();
    void checkViability();
};

#endif // HEAD_H
