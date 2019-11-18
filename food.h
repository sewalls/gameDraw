#ifndef FOOD_H
#define FOOD_H

#include "grelement.h"

class Food : public Grelement
{
public:
    Food();
    Food(QPointF pos) {this->pos = pos;}

    void draw(QPainter *painter) override;
    void update() override;
    void move();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // FOOD_H
