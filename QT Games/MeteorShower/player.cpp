#include "player.h"
#include "bullet.h"
#include "game.h"
#include "meteor.h"
#include <cstdlib>

#include <QDebug>

extern Game * game;

Player::Player(QGraphicsItem *parent): QObject(),QGraphicsPixmapItem(parent)
{

    setPixmap(QPixmap(":/Images/images/spaceship2.png").scaled(PLAYER_SIZE,PLAYER_SIZE, Qt::KeepAspectRatio));
    keyLeft = false;
    keyRight = false;
    keyUp = false;
    keyDown = false;
    keySpace = false;


}

void Player::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Left:
    keyLeft = true;
    setPos(x()-10,y());
    break;
    case Qt::Key_Right:
    keyRight = true;
    setPos(x()+10,y());
    break;
    case Qt::Key_Up:
    keyUp = true;
    setPos(x(),y()-10);
    break;
    case Qt::Key_Down:
    keyDown = true;
    setPos(x(),y()+10);
    break;
    case Qt::Key_Space:
    keySpace = true;
    break;
    }
    movePlayer();
}

void Player::keyReleaseEvent(QKeyEvent *event) {

    if (!event->isAutoRepeat()) {
    switch(event->key()) {
    case Qt::Key_Left:
    keyLeft = false;
    break;
    case Qt::Key_Right:
    keyRight = false;
    break;
    case Qt::Key_Up:
    keyUp = false;
    break;
    case Qt::Key_Down:
    keyDown = false;
    break;
    case Qt::Key_Space:
    keySpace = false;
    break;
    }
  }

}


void Player::spawn()
{
    int random_number = rand()%(SCENE_HEIGHT-PLAYER_SIZE);
    Meteor * meteor = new Meteor();
    meteor->setPos(random_number,0);
    game->scene->addItem(meteor);
    if(game->sounds->background->state()==QMediaPlayer::StoppedState)
    {
        game->sounds->background->play();
    }

}

void Player::movePlayer() {


    if(keyLeft) setPos(x()-10,y());
    if(keyRight) setPos(x()+10,y());
    if(keyUp) setPos(x(),y()-10);
    if(keyDown) setPos(x(),y()+10);
    if(keySpace)
    {
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+PLAYER_SIZE/2-BULLET_HEIGHT/2, y());
        game->scene->addItem(bullet);

        if(game->sounds->bulletSound->state()== QMediaPlayer::PlayingState)
        {
            game->sounds->bulletSound->setPosition(0);
        }else
        {
            game->sounds->bulletSound->play();
        }
    }
//    else if(keyLeft && keyUp) setPos(x()-10, y()-10);
//    else if(keyLeft && keyDown) setPos(x()-10, y()+10);
//    else if(keyRight && keyUp) setPos(x()+10, y()-10);
//    else if(keyRight && keyDown) setPos(x()+10, y()+10);


}

/*
 * void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        if(x()>MOVE_SPEED)
        {
            setPos(x()-MOVE_SPEED,y());
        }
    }else if(event->key() == Qt::Key_Right)
    {
        if(x()+PLAYER_SIZE+MOVE_SPEED<SCENE_HEIGHT)
        {
            setPos(x()+MOVE_SPEED,y());
        }

    }else if(event->key() == Qt::Key_Up)
    {
        if(y()>MOVE_SPEED)
        {
            setPos(x(),y()-MOVE_SPEED);
        }

    }else if(event->key() == Qt::Key_Down)
    {
        if(y()+PLAYER_SIZE+MOVE_SPEED<SCENE_WIDTH)
        {
            setPos(x(),y()+MOVE_SPEED);
        }
    }else if(event->key() == Qt::Key_Space)
    {
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+PLAYER_SIZE/2-BULLET_HEIGHT/2, y());
        game->scene->addItem(bullet);

        if(game->sounds->bulletSound->state()== QMediaPlayer::PlayingState)
        {
            game->sounds->bulletSound->setPosition(0);
        }else
        {
            game->sounds->bulletSound->play();
        }
    }
}
 *
 * */



