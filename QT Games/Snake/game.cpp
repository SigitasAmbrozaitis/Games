#include "game.h"

Game::Game(QWidget * parent)
{
    //creating scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0, SCENE_WIDTH, SCENE_HEIGHT);

    //creating view
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedHeight(scene->height());
    setFixedWidth(scene->width());

    snake =  new Snake();
    snake -> setFlag(QGraphicsItem::ItemIsFocusable);
    snake -> setFocus();
    scene -> addItem(snake);

    food = new Food();
    scene->addItem(food);

}
