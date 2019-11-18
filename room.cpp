#include "room.h"

Room::Room(std::vector<Wall*> walls, QString name, QPointF p1, QPointF p2)
{
    this->walls = walls;
    this->name = name;
    this->p1 = p1;
    this->p2 = p2;
}

Room::Room(std::vector<Wall*> walls) {
    this->walls = walls;
    QPointF smallest = {100000, 100000};
    QPointF largest = {-100000, -100000};
    for(auto& w : walls) {
        if(w->getP1().x() < smallest.x()) {
            smallest.setX(w->getP1().x());
        }
        if(w->getP2().x() < smallest.x()) {
            smallest.setX(w->getP2().x());
        }
        if(w->getP1().y() < smallest.y()) {
            smallest.setY(w->getP1().y());
        }
        if(w->getP2().y() < smallest.y()) {
            smallest.setY(w->getP2().y());
        }

        if(w->getP1().x() > largest.x()) {
            largest.setX(w->getP1().x());
        }
        if(w->getP2().x() > largest.x()) {
            largest.setX(w->getP2().x());
        }
        if(w->getP1().y() > largest.y()) {
            largest.setY(w->getP1().y());
        }
        if(w->getP2().y() > largest.y()) {
            largest.setY(w->getP2().y());
        }
    }
    p1 = smallest;
    p2 = largest;
}

void Room::draw(QPainter& painter) {
    QRectF rect(p1, p2);
    if(clicked) {
        painter.setPen(Qt::green);
    }
    for(unsigned int i = 0; i < walls.size(); i++) {
        painter.drawText(walls[i]->midpt(), QString::number(i)); // point, string
    }
    painter.drawRect(rect);
    painter.setPen(Qt::black);
}

bool Room::containsPoint(QPointF event) {
    return (event.x() > p1.x() && event.x() < p2.x()) && (event.y() > p1.y() && event.y() < p2.y());
}

bool Room::containsWall(Wall* wall) {
    for(auto& w : walls) {
        if(w == wall) {
            return true;
        }
    }
    return false;
}

void Room::replaceWall(Wall* wall, Wall* w1, Wall* w2) {
    walls.erase(std::find(walls.begin(), walls.end(), wall));
    walls.push_back(w1);
    walls.push_back(w2);
}
