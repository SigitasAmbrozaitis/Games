#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "sounds.h"
#include "health.h"
#include "score.h"

#include <QGraphicsView>
#include <QGraphicsScene>

#define SCENE_HEIGHT 1200
#define SCENE_WIDTH 800
#define PLAYER_SIZE 60
#define MOVE_SPEED 20
#define BULLET_HEIGHT 10
#define BULLET_WIDTH 20
#define BULLET_SPEED 30
#define METEOR_SPEED 40

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = 0);
    ~Game();

    QGraphicsScene * scene;
    Player * player;
    Sounds * sounds;
    Health * health;
    Score * score;
    int dificulty;
    void increasePenalty();
public slots:



};

#endif // GAME_H
