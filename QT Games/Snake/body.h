#ifndef BODY_H
#define BODY_H

#include <QGraphicsPixmapItem>

class Body : public QGraphicsPixmapItem
{
public:
    Body(int x, int y, QGraphicsPixmapItem * parent = nullptr); //inicializes body node
    void setDirrection(char c);                                 //sets direction in whic body node is going
    char dir;       //direction
    bool corner;    //true if corner


    QPixmap image;      //node image
    QPixmap *imageCopy; //node image copy
};

#endif // BODY_H
