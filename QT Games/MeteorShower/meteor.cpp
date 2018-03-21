#include "meteor.h"
#include <cstdlib>
#include <QString>
#include <QTimer>
#include "game.h"
#include <QList>
#include "player.h"
#include <QDebug>

extern Game * game;

Meteor::Meteor(QGraphicsPixmapItem *parent):  QObject(), QGraphicsPixmapItem(parent)
{
    int random_size = rand()%100+30;
    int random = rand()%3;
    QString path[3];
    path[0] = ":/Images/images/meteor1.png";
    path[1] = ":/Images/images/meteor2.png";
    path[2] = ":/Images/images/meteor3.png";

    int random_speed = rand()%METEOR_SPEED+20;

    setPixmap(QPixmap(path[random]).scaled(random_size, random_size, Qt::KeepAspectRatio));
    QTimer * timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(random_speed);




}

void Meteor::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i<n; ++i)
    {
        if(typeid(*(colliding_items[i]))==typeid(Player))
        {
            if(game->sounds->collision->state()==QMediaPlayer::PlayingState)
            {
                game->sounds->collision->setPosition(0);
            }else
            {
                game->sounds->collision->play();
            }

            if(game->health->getHealth() >1)
            {
                game->health->decrease();
                game->scene->removeItem(this);
                delete this;
                return;
            }else
            {
                QGraphicsTextItem * gameOver = new QGraphicsTextItem();
                gameOver->setPlainText("GAME OVER");
                gameOver->setDefaultTextColor(Qt::red);
                gameOver->setFont(QFont("times", 124));
                gameOver->setPos(150, SCENE_WIDTH/3);
                game->scene->removeItem(colliding_items[i]);
                game->scene->removeItem(this);

                //delete explosion;
                delete colliding_items[i];
                delete this;
                game->scene->clear();
                game->scene->addItem(gameOver);
                game->sounds->background->stop();
                return;
            }
        }
    }


    if(pos().y()>SCENE_WIDTH)
    {
        game->scene->removeItem(this);
        game->increasePenalty();
        delete this;
    }
    setPos(x(), y()+5);
}
