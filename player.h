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
    void bumpScore() {score += 100;}
    void reset();
    unsigned int getSize() {return size;}
    int getScore() {return score;}
    std::vector<QPointF> getPrevPos() {return prevPos;}

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    double acelX = 0;
    double acelY = 0;
    double velX = 0;
    double velY = 0;
    int jerkX = 0;
    int jerkY = 0;
    double brake = 0.99;
    unsigned int size = 10;
    int score = 0;

    std::vector<QPointF> prevPos;
};

#endif // PLAYER_H
