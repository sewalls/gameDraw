#ifndef ENEMY_H
#define ENEMY_H

#include "grelement.h"

class Enemy : public Grelement
{
public:
    Enemy();
    void draw(QPainter *painter) override;
    void update() override;
    void targetize(QPointF pos) {target = pos;}
    void grow(unsigned int growth) {size += growth;}
    void randomDirection();
    void reset();
    void setColor(QColor color) {this->color = color;}
    unsigned int getSize() {return size;}
    int getWait() {return wait;}

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    std::vector<QPointF> prevPos;

private:
    QPointF target = {0, 0};
    QColor color = Qt::red;
    double acelX = 0;
    double acelY = 0;
    double velX = 0;
    double velY = 0;
    int jerkX = 0;
    int jerkY = 0;
    double brake = 0.99;
    unsigned int size = 10;
    int wait = 200;
};

#endif // ENEMY_H
