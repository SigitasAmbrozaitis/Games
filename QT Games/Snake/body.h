#ifndef BODY_H
#define BODY_H

#include <QGraphicsPixmapItem>

class Body : public QGraphicsPixmapItem
{
public:
    Body(int x, int y, QGraphicsPixmapItem * parent = nullptr);
    void setDirrection(char c);
    char dir;
    bool corner;
    //int angle;

    QPixmap image;
    QPixmap *imageCopy;
};

#endif // BODY_H
