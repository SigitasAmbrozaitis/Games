#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>

class Sounds
{
public:
    Sounds();
    ~Sounds();
    QMediaPlayer * bulletSound;
    QMediaPlayer * background;
    QMediaPlayer * explosion;
    QMediaPlayer * collision;

};

#endif // SOUNDS_H
