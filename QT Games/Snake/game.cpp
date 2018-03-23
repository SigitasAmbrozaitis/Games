#include "game.h"

Game::Game()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,WIDTH, HEIGHT);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WIDTH, HEIGHT);

    head = nullptr;
    head = new Head(  ((WIDTH/SIZE) * SIZE)/2  ,  ((HEIGHT/SIZE)*SIZE)/2  );
    head->setFlag(QGraphicsItem::ItemIsFocusable);
    head->setFocus();
    scene->addItem(head);

    body.append(new Body(head->x(), head->y()+SIZE));
    scene->addItem(body[0]);

    food = new Food();
    scene->addItem(food);
}
