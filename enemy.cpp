#include "enemy.h"
#include <random>

Enemy::Enemy()
{
    pos = {300, 300};
}

void Enemy::draw(QPainter *painter) {
    if(wait >= 0) {
        painter->setBrush(Qt::BrushStyle::BDiagPattern);
    }
    else {
        painter->setBrush(QBrush(color));
    }
    for(unsigned int i = prevPos.size() - size; i < prevPos.size(); i++) {
        painter->drawEllipse(prevPos[i], 9, 9);
        painter->drawEllipse(QPointF{prevPos[i].x() + 1400, prevPos[i].y()}, 9, 9);
        painter->drawEllipse(QPointF{prevPos[i].x() - 1400, prevPos[i].y()}, 9, 9);
        painter->drawEllipse(QPointF{prevPos[i].x(), prevPos[i].y() + 700}, 9, 9);
        painter->drawEllipse(QPointF{prevPos[i].x(), prevPos[i].y() - 700}, 9, 9);
    }


    painter->drawEllipse(pos, 10, 10);
    painter->drawEllipse(QPointF{pos.x() + 1400, pos.y()}, 10, 10);
    painter->drawEllipse(QPointF{pos.x() - 1400, pos.y()}, 10, 10);
    painter->drawEllipse(QPointF{pos.x(), pos.y() + 700}, 9, 9);
    painter->drawEllipse(QPointF{pos.x(), pos.y() - 700}, 9, 9);
}

void Enemy::keyPressEvent(QKeyEvent *event) {

}

void Enemy::keyReleaseEvent(QKeyEvent *event) {

}

void Enemy::randomDirection() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<> dist(-1, 1);

    acelX = dist(e2) / 2.0;
    acelY = dist(e2) / 2.0;

    velX = velX * 0.9;
    velY = velY * 0.9;
}

void Enemy::update() {
    prevPos.push_back(pos);

    if(pos.x() > 1500) {
        pos.setX(100);
    }
    if(pos.y() > 800) {
        pos.setY(100);
    }
    if(pos.x() < 100) {
        pos.setX(1500);
    }
    if(pos.y() < 100) {
        pos.setY(800);
    }

    if(target.x() - pos.x() > 0) {
        jerkX = 1;
        velY = velY * 0.98;
    }
    else if(target.x() - pos.x() < 0) {
        jerkX = -1;
        velY = velY * 0.98;
    }
    else {
        jerkX = 0;
    }

    if(target.y() - pos.y() > 0) {
        jerkY = 1;
        velX = velX * 0.98;
    }
    else if(target.y() - pos.y() < 0) {
        jerkY = -1;
        velX = velX * 0.98;
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

    velX = velX * brake;
    velY = velY * brake;

    velX += acelX;
    velY += acelY;

    acelX += -acelX * 0.05;
    acelY += -acelY * 0.05;

    pos.setX(pos.x() + velX);
    pos.setY(pos.y() + velY);

    wait -= 1;
}

void Enemy::reset() {
    wait = 200;
    acelX = 0;
    acelY = 0;
    velX = 0;
    velY = 0;
    size = 10;
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<> X(0, 1200);
    std::uniform_real_distribution<> Y(0, 800);

    pos = {X(e2), Y(e2)};
}
