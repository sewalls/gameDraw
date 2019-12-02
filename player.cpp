#include "player.h"

Player::Player()
{
    pos = {250, 150};
}

void Player::draw(QPainter *painter) {
    painter->drawText(QPointF{10, 10}, "P: " + QString::number(std::round(pos.x() * 1000) / 1000) + ", " + QString::number(std::round(pos.y() * 1000) / 1000));
    painter->drawText(QPointF{10, 25}, "V: " + QString::number(std::round(velX * 1000) / 1000) + ", " + QString::number(std::round(velY * 1000) / 1000));

    painter->setBrush(QBrush(Qt::blue));

    for(unsigned int i = prevPos.size() - size; i < prevPos.size(); i++) {
        painter->drawEllipse(prevPos[i], 9, 9);
    }
    painter->drawEllipse(pos, 10, 10);
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
    }
}

void Player::update() {
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
