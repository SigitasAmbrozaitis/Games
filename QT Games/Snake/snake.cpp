#include "snake.h"
#include "game.h"
#include "food.h"

#include <QTimer>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsItem>
#include <QDebug>

extern Game * game;

Snake::Snake(QGraphicsPixmapItem * parent) : QObject(), QGraphicsPixmapItem(parent)
{

    setPixmap(QPixmap(":/images/Recources/snake.png").scaled(MOVE_SIZE, MOVE_SIZE,Qt::KeepAspectRatio));
    setPos(SCENE_WIDTH/2,SCENE_HEIGHT/2);
    timer = new QTimer();
    flag = 1;
    Body * temp = new Body();
    //game->scene->addItem(body[0]);

    body.append(temp);
    //scene()->addItem(temp);

}

void Snake::keyPressEvent(QKeyEvent *event)
{
    switch(flag)
    {
        case 1:
            QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(moveLeft()));
            flag = 0;
            break;
        case 2:
            QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(moveRight()));
            flag = 0;
            break;
        case 3:
            QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(moveUp()));
            flag = 0;
            break;
        case 4:
            QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(moveDown()));
            flag = 0;
            break;
    }

    if(event->key()==Qt::Key_Left)
    {
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveLeft()));
        flag = 1;
    }

    else if(event->key()==Qt::Key_Right && flag == 0)
    {
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveRight()));
        flag = 2;
    }
    else if(event->key()==Qt::Key_Up && flag == 0)
    {
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveUp()));
        flag = 3;
    }
    else if(event->key()==Qt::Key_Down && flag == 0)
    {
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveDown()));
        flag = 4;
    }

    timer ->start(SPEED);
}

void Snake::moveUp()
{
    setPos(x(), y()-MOVE_SIZE);
    checkCollision();
    checkBorder();
}

void Snake::moveDown()
{
    setPos(x(), y()+MOVE_SIZE);
    checkCollision();
    checkBorder();
}

void Snake::moveLeft()
{
    setPos(x()-MOVE_SIZE, y());
    checkCollision();
    checkBorder();
}

void Snake::moveRight()
{
    setPos(x()+MOVE_SIZE, y());
    checkCollision();
    checkBorder();
}

void Snake::checkCollision()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    for(int i = 0, n = collisions.size(); i<n; ++i)
    {
        if(typeid(*(collisions[i])) == typeid(Food))
        {
            game->scene->removeItem(collisions[i]);
            delete collisions[i];
            Food * temp = new Food();
            game->scene->addItem(temp);

        }
    }
}

void Snake::checkBorder()
{
    if(this->x()<0 || this->x()>SCENE_WIDTH || this->y()<0  || this->y()>SCENE_WIDTH)
    {

        game->scene->clear();
    }else
    {
        qDebug()<< this->x() << this->y();
    }
}

void Snake::appendBody()
{

}

void Snake::moveBody()
{

}