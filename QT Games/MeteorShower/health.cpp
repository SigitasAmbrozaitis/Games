#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem * parent):QGraphicsTextItem(parent)
{
    hp = 5;

    setPlainText("HP: " + QString::number(hp));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 10));

}

void Health::decrease()
{
    --hp;
    setPlainText("HP: " + QString::number(hp));
}

int Health::getHealth()
{
    return hp;
}
