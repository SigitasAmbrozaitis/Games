#ifndef METEOR_H
#define METEOR_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Meteor :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Meteor(QGraphicsPixmapItem * parent = nullptr);
public slots:
    void move();
private:
};

#endif // METEOR_H
