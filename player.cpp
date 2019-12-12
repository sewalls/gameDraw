#include "player.h"

Player::Player()
{
    pos = {250, 150};
}

void Player::draw(QPainter *painter) {
    painter->setBrush(QBrush(Qt::blue));

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
    }
}

void Player::update() {
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

void Player::reset() {
    score = 0;
    acelX = 0;
    acelY = 0;
    velX = 0;
    velY = 0;
    size = 10;
    pos = {250, 150};
}
