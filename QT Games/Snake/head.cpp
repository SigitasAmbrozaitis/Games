#include "head.h"
#include "game.h"
#include <QDebug>
#include <QTimer>

extern Game * game;

Head::Head(int x, int y, QGraphicsPixmapItem * parent):QObject(), Body(x, y, parent)
{
    image = QPixmap(":/colors/Head2.png").scaled(SIZE, SIZE, Qt::KeepAspectRatio);
    flag = false;
    //setPixmap(QPixmap(":/colors/Head.png").scaled(SIZE, SIZE, Qt::KeepAspectRatio));
    moving = 'T';

    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(SPEED);

}

void Head::keyPressEvent(QKeyEvent *event)
{

        if(!flag)
        {
            switch(event->key()){
            case Qt::Key_Up:
                if(moving !='D' && moving !='T') moving = 'T';
                break;
            case Qt::Key_Down:
                if(moving !='D' && moving !='T') moving = 'D';

                break;
            case Qt::Key_Right:
                if(moving !='R' && moving !='L') moving = 'R';
                break;
            case Qt::Key_Left:
                if(moving !='R' && moving !='L') moving = 'L';
                break;
            }
            //game->body[0]->corner = true;
            flag = true;
        }


}

void Head::move()
{

        updateBody();
        switch(moving){
        case 'T':
            setPos(this->x() , this->y() - SIZE);
            this->setDirrection('U');

            break;
        case 'D':
            setPos(this->x() , this->y() +SIZE);
            this->setDirrection('D');
            break;
        case 'R':
            setPos(this->x()+SIZE , this->y() );
            this->setDirrection('R');
            break;
        case 'L':
            setPos(this->x() -SIZE, this->y() );
            this->setDirrection('L');
            break;
        }

        flag = false;

    checkViability();

    QList<QGraphicsItem *> colliding = collidingItems();
    for(int i=0; i<colliding.size(); ++i)
    {
        if(typeid(*(colliding[i]))==typeid(Body))
        {
            stopGame();
        }
        if(typeid(*(colliding[i])) == typeid(Food))
        {
            scene()->removeItem(colliding[i]);
            delete colliding[i];

            game->body.append(new Body(X, Y));
            scene()->addItem(game->body[game->body.size()-1]);

            game->food = new Food();
            scene()->addItem(game->food);
        }
    }
}

void Head::checkViability()
{
    if(this->x()<0 || this->x() > WIDTH || this->y() < 0 || this->y()>HEIGHT)
    {
        stopGame();
        qDebug() << "STOP!!!";
    }
}

void Head::updateBody()
{
    int temp = game->body.size();
    X = game->body[temp-1]->x();
    Y = game->body[temp-1]->y();

    Body * kint;
    for(int i = temp-1; i > 0; --i)
    {
        kint = game->body[i-1];
        game->body[i]->setPos(kint->x(), kint->y());
        game->body[i]->corner = kint->corner;
        if(kint->corner)
        {
            kint->corner = false;
        }
        game->body[i]->setDirrection(kint->dir);


    }
    game->body[0]->setPos(this->x(), this->y());
    game->body[0]->corner = false;
    game->body[0]->setDirrection(this->dir);

}

void Head::stopGame()
{
    for(int i=0; i<game->body.size(); ++i)
    {
        scene()->removeItem(game->body[i]);
        delete(game->body[i]);
    }
    timer->stop();
    delete timer;

    scene()->removeItem(game->food);
    scene()->removeItem(this);

    delete game->food;
    delete this;
}


