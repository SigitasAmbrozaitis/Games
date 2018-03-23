#include "body.h"
#include "game.h"
#include <QTransform>
#include <QDebug>
extern Game * game;

Body::Body(int x, int y,QGraphicsPixmapItem * parent):QGraphicsPixmapItem(parent)
{
    image = QPixmap(":/colors/Body2.png").scaled(SIZE,SIZE, Qt::KeepAspectRatio);
    corner = false;
    setPos(x, y);
    dir = 'U';
    setDirrection('U');
}

void Body::setDirrection(char c)
{
    dir = c;
    QPixmap rotatedPixmap(image.size());
    rotatedPixmap.fill(QColor::fromRgb(0, 0, 0, 0)); //the new pixmap must be transparent.
    QPainter* p = new QPainter(&rotatedPixmap);
    QSize size = image.size();
    p->translate(size.height()/2,size.height()/2);
    //qDebug() << corner;
    if(corner==true)
    {
        image = QPixmap(":/colors/BodyCorner.png").scaled(SIZE,SIZE, Qt::KeepAspectRatio);
    }else
    {
        switch(dir)
        {
            case 'U':   //up
                p->rotate(0);
                break;
            case 'D':   //down
                p->rotate(180);
                break;
            case 'R':   //right
                p->rotate(90);
                break;
            case 'L':   //left
                p->rotate(270);
                break;
        }
    }
    p->translate(-size.height()/2,-size.height()/2);
    p->drawPixmap(0, 0, image);
    p->end();
    delete p;
    setPixmap(rotatedPixmap);
}

