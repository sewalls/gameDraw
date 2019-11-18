#include "player.h"

Player::Player()
{
    pos = {250, 150};
}

void Player::draw(QPainter *painter) {
    painter->drawEllipse(pos, 10, 10);
    painter->drawText(QPointF{10, 10}, "P: " + QString::number(std::round(pos.x() * 1000) / 1000) + ", " + QString::number(std::round(pos.y() * 1000) / 1000));
    painter->drawText(QPointF{10, 25}, "V: " + QString::number(std::round(velX * 1000) / 1000) + ", " + QString::number(std::round(velY * 1000) / 1000));

    for(unsigned int i = prevPos.size() - size; i < prevPos.size(); i++) {
        painter->drawEllipse(prevPos[i], 9, 9);
    }
}

void Player::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case (Qt::Key_W):
        jerkY += -1;
        break;
    case (Qt::Key_S):
        jerkY += 1;
        break;
    case (Qt::Key_A):
        jerkX += -1;
        break;
    case (Qt::Key_D):
        jerkX += 1;
        break;
    case (Qt::Key_R):
        pos = {250, 150};
        break;
    case (Qt::Key_Shift):
        brake = 0.95;
        break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
    case (Qt::Key_W):
        jerkY += 1;
        break;
    case (Qt::Key_S):
        jerkY += -1;
        break;
    case (Qt::Key_A):
        jerkX += 1;
        break;
    case (Qt::Key_D):
        jerkX += -1;
        break;
    case (Qt::Key_Shift):
        brake = 0.99;
        break;
    case (Qt::Key_Space):
        size++;
        break;
    }
}

void Player::update() { //hard code a circle 100 radius around 250, 150
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

void Player::randomDirection() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_int_distribution<> dist(-1, 1);

    jerkX = dist(e2);
    jerkY = dist(e2);
}

void Player::target(QPointF target) {
    if(target.x() - pos.x() > 0) {
        jerkX = 1;
    }
    else if(target.x() - pos.x() < 0) {
        jerkX = -1;
    }

    if(target.y() - pos.y() > 0) {
        jerkY = 1;
    }
    else if(target.y() - pos.y() < 0) {
        jerkY = -1;
    }
}
