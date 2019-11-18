#include "enemy.h"
#include <random>

Enemy::Enemy()
{
    pos = {300, 300};
}

void Enemy::draw(QPainter *painter) {
    painter->drawEllipse(pos, 20, 20);
}
void Enemy::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case (Qt::Key_W):
        break;
    }
}

void Enemy::keyReleaseEvent(QKeyEvent *event) {

}

void Enemy::update() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<> dist(-0.0000001, 0.0000001);

    velX = velX * 0.9;
    velY = velY * 0.9;

    acelX = acelX * 0.98;
    acelY = acelY * 0.98;

    acelX += (pos.x() - target.x()) / -100000; //unitize then multiplize
    acelY += (pos.y() - target.y()) / -100000;

    velX += acelX;
    velY += acelY;

    pos.setX(pos.x() + velX);
    pos.setY(pos.y() + velY);
}
