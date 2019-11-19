#include "enemy.h"
#include <random>

Enemy::Enemy()
{
    pos = {300, 300};
}

void Enemy::draw(QPainter *painter) {
    painter->drawEllipse(pos, 10, 10);
    for(unsigned int i = prevPos.size() - size; i < prevPos.size(); i++) {
        painter->drawEllipse(prevPos[i], 9, 9);
    }
}
void Enemy::keyPressEvent(QKeyEvent *event) {

}

void Enemy::keyReleaseEvent(QKeyEvent *event) {

}

void Enemy::randomDirection() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> dist(-1, 1);

    jerkX = dist(e2);
    jerkY = dist(e2);
}

void Enemy::update() {
    prevPos.push_back(pos);

    if(pos.x() > 1200) {
        pos.setX(0);
    }
    if(pos.y() > 800) {
        pos.setY(0);
    }
    if(pos.x() < 0) {
        pos.setX(1200);
    }
    if(pos.y() < 0) {
        pos.setY(800);
    }

    if(target.x() - pos.x() > 0) {
        jerkX = 1;
    }
    else if(target.x() - pos.x() < 0) {
        jerkX = -1;
    }
    else {
        jerkX = 0;
    }

    if(target.y() - pos.y() > 0) {
        jerkY = 1;
    }
    else if(target.y() - pos.y() < 0) {
        jerkY = -1;
    }
    else {
        jerkY = 0;
    }

    if(jerkX >= 1) {
        acelX += 0.005;
    }
    if(jerkX <= -1) {
        acelX += -0.005;
    }
    if(jerkY >= 1) {
        acelY += 0.005;
    }
    if(jerkY <= -1) {
        acelY += -0.005;
    }

    velX += acelX;
    velY += acelY;

    acelX += -acelX * 0.05;
    acelY += -acelY * 0.05;

    velX = velX * brake;
    velY = velY * brake;

    pos.setX(pos.x() + velX);
    pos.setY(pos.y() + velY);
}
