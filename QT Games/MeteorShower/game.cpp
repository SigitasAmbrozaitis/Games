#include "game.h"
#include "meteor.h"
#include <QTimer>
#include <cstdlib>
#include <time.h>
Game::Game(QWidget * parent)
{
    srand(time(NULL));
    dificulty = 0;

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,SCENE_HEIGHT,SCENE_WIDTH);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedHeight(scene->height());
    setFixedWidth(scene->width());
    setBackgroundBrush(QPixmap(":/Images/images/space1.jpg").scaled(SCENE_HEIGHT+100, SCENE_WIDTH,Qt::KeepAspectRatio));

    player = new Player();
    player->setPos(((scene->width()/2)-PLAYER_SIZE/2),(scene->height()-scene->height()/5));
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    sounds = new Sounds();
    if(sounds->background->state()==QMediaPlayer::StoppedState)
    {
        sounds->background->play();
    }


    health =new Health();
    scene->addItem(health);

    score = new Score();
    score->setPos(SCENE_HEIGHT-100,0);
    scene->addItem(score);

    QTimer * timer1 = new QTimer;
    QObject::connect(timer1,SIGNAL(timeout()),player,SLOT(spawn()));
    timer1->start(1500);







}

Game::~Game()
{
    delete scene;
    delete player;
    delete sounds;
    delete health;
    delete score;

}

void Game::increasePenalty()
{
    ++dificulty;
    if(dificulty % 20==0 && dificulty<400)
    {
        qDebug()<<"sunkinu!!";
        QTimer * timer = new QTimer;
        QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
        timer->start(1500);
    }
}
