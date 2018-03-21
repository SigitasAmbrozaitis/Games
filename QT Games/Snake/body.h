#ifndef BODY_H
#define BODY_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Body :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Body(QGraphicsPixmapItem * parent = 0);
};

#endif // BODY_H
