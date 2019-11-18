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
    painter->drawText(QPointF{10, 60}, "P: " + QString::number(std::round(pos.x() * 1000) / 1000) + ", " + QString::number(std::round(pos.y() * 1000) / 1000));
}

void Food::update() {

}

void Food::move() {
    std::mt19937 e2(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<> distX(0, 1190);
    std::uniform_real_distribution<> distY(0, 790);

    pos.setX(distX(e2));
    pos.setY(distY(e2));
}

void Food::keyPressEvent(QKeyEvent *event) {

}

void Food::keyReleaseEvent(QKeyEvent *event) {

}
