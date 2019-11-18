#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QPainterPath>
#include "grelement.h"

class Player : public Grelement
{
public:
    Player();

    void draw(QPainter *painter) override;
    void update() override;
    void grow(unsigned int growth) {size += growth;}
    void randomDirection();
    void target(Player target);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    double acelX = 0;
    double acelY = 0;
    double velX = 0;
    double velY = 0;
    int jerkX = 0;
    int jerkY = 0;
    double brake = 0.99;
    unsigned int size = 10;

    std::vector<QPointF> prevPos;
    QPainterPath poses;
};

#endif // PLAYER_H
