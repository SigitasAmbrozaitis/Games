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
    //angle = 270;
    setDirrection('U');
    //setPixmap(*imageCopy);


}

/*QTransform transform;
QTransform trans = transform.rotate(45);
pixmap = new QPixmap(pixmap->scaled(sqrt(pixmap->size().width()), sqrt(pixmap->size().height())));
QPixmap *transPixmap = new QPixmap(pixmap->transformed(trans));*/

/*QPixmap rotatedPixmap(m_pixOriginal.size());
rotatedPixmap.fill(QColor::fromRgb(0, 0, 0, 0)); //the new pixmap must be transparent.
QPainter* p = new QPainter(&rotatedPixmap);
QSize size = m_pxOriginal.size();
p->translate(size.height()/2,size.height()/2);
p->rotate(m_iAngle);
p->translate(-size.height()/2,-size.height()/2);
p->drawPixmap(0, 0, m_pxOriginal);
p->end();
delete p;
m_pxItem->setPixmap(rotatedPixmap);
*/
/*QPixmap temp = image.copy().scaled(SIZE,SIZE, Qt::KeepAspectRatio);
imageCopy = &temp;
//QTransform transform;
//QTransform trans = transform.rotate(180);
//imageCopy = new QPixmap(imageCopy->transformed(trans));


QTransform transform;
QTransform trans = transform.scale(sqrt(imageCopy->size().width()), sqrt(imageCopy->size().height()));
trans = transform.rotate(90);
QPixmap(imageCopy->transformed(trans));
setPixmap(*imageCopy);*/


void Body::setDirrection(char c)
{
    dir = c;
    QPixmap rotatedPixmap(image.size());
    rotatedPixmap.fill(QColor::fromRgb(0, 0, 0, 0)); //the new pixmap must be transparent.
    QPainter* p = new QPainter(&rotatedPixmap);
    QSize size = image.size();
    p->translate(size.height()/2,size.height()/2);
    qDebug() << corner;
    if(corner==true)
    {
        image = QPixmap(":/colors/BodyCorner.png").scaled(SIZE,SIZE, Qt::KeepAspectRatio);

        //corner = false;
    }else
    {
        switch(dir)
        {
            case 'U':
                p->rotate(0);
                break;
            case 'D':
                p->rotate(180);
                break;
            case 'R':
                p->rotate(90);
                break;
            case 'L':
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

/*
 *
 *     if(game->head == nullptr)
    {
        dir = 'U';
    }else if(game->body.size()==0)
    {
        if(game->head->y()==y && game->head->x()-x<0)
        {
            setDirrection('R');
        }else if(game->head->y()==y && game->head->x()-x>0)
        {
            setDirrection('L');
        }
        if(game->head->x()==x && game->head->y()-y>0)
        {
            setDirrection('U');
        }else if(game->head->x()==x && game->head->y()-y<0)
        {
            setDirrection('D');
        }
    }else
    {
        if(game->body[game->body.size()-1]->y()==y && game->body[game->body.size()-1]->x()-x<0)
        {
            setDirrection('R');
        }else if(game->body[game->body.size()-1]->y()==y && game->body[game->body.size()-1]->x()-x>0)
        {
            setDirrection('L');
        }
        if(game->body[game->body.size()-1]->x()==x && game->body[game->body.size()-1]->y()-y>0)
        {
            setDirrection('U');
        }else if(game->body[game->body.size()-1]->x()==x && game->body[game->body.size()-1]->y()-y<0)
        {
            setDirrection('D');
        }
    }
 *
 *
 *
 *
 *
 *
 *     if(dir != c)
    {
       dir = c;
       switch (dir)
       {
           case 'U':
           //image = image->rotated(45);
           break;
           case 'D':

           break;

           case 'R':

           break;

           case 'L':

           break;
       }
    }
 * */
