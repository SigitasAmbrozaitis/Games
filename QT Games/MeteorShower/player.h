#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>


class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void movePlayer();
public slots:
    void spawn();
private:
    bool keyLeft;
    bool keyRight;
    bool keyUp;
    bool keyDown;
    bool keySpace;


};

#endif // PLAYER_H
