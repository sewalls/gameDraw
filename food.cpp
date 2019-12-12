#include "food.h"

Food::Food()
{

}

void Food::draw(QPainter *painter) {
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    painter->setPen(Qt::green);
    painter->setBrush(brush);
    painter->drawEllipse(pos, 5, 5);
}

void Food::update() {

}

void Food::move() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<> distX(150, 1450);
    std::uniform_real_distribution<> distY(150, 750);

    pos.setX(distX(e2));
    pos.setY(distY(e2));
}

void Food::keyPressEvent(QKeyEvent *event) {

}

void Food::keyReleaseEvent(QKeyEvent *event) {

}
