#include "game.h"

Game::Game()
{
    //setting up scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WIDTH, HEIGHT);
    setScene(scene);

    //setting scene policies and size
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH, HEIGHT);

    //creating snake head in the middle of the scene
    head = new Head(  ((WIDTH/SIZE) * SIZE)/2  ,  ((HEIGHT/SIZE)*SIZE)/2  );
    head->setFlag(QGraphicsItem::ItemIsFocusable);
    head->setFocus();
    scene->addItem(head);

    //creating body node and connecting it to the head
    body.append(new Body(head->x(), head->y()+SIZE));
    scene->addItem(body[0]);

    //places first food in the scene
    food = new Food();
    scene->addItem(food);
}
