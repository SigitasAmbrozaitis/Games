#include "bullet.h"
#include "game.h"
#include "meteor.h"
#include <QTimer>
#include <QList>
#include <QGraphicsItem>

extern Game * game;
Bullet::Bullet(QGraphicsPixmapItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/Images/images/bullet4.png").scaled(BULLET_HEIGHT, BULLET_WIDTH,Qt::KeepAspectRatio));

    QTimer * time = new QTimer();
    connect(time, SIGNAL(timeout()), this, SLOT(move()));
    time->start(BULLET_SPEED);
}

void Bullet::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n; ++i)
    {
        if(typeid(*(colliding_items[i]))==typeid(Meteor))
        {
            //game->score->increase();
            game->score->increase();
            game->scene->removeItem(colliding_items[i]);
            game->scene->removeItem(this);

            if(game->sounds->explosion->state()==QMediaPlayer::PlayingState)
            {
                game->sounds->explosion->setPosition(0);
            }else
            {
                game->sounds->explosion->play();
            }


            //delete explosion;
            delete colliding_items[i];
            delete this;

            return;
        }
    }



    if(y()<0)
    {
        game->scene->removeItem(this);
        delete this;
    }

    setPos(x(), y()-5);
}
