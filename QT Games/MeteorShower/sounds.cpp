#include "sounds.h"

Sounds::Sounds()
{
    bulletSound = new QMediaPlayer();
    background = new QMediaPlayer();
    explosion = new QMediaPlayer();
    collision = new QMediaPlayer();

    bulletSound->setMedia(QUrl("qrc:/sounds/sounds/bullet1.mp3"));
    background->setMedia(QUrl("qrc:/sounds/sounds/background.mp3"));
    explosion->setMedia(QUrl("qrc:/sounds/sounds/explode2.mp3"));
    collision->setMedia(QUrl("qrc:/sounds/sounds/explode.mp3"));

}

Sounds::~Sounds()
{
    delete bulletSound;
    delete background;
    delete explosion;
    delete collision;
}
