#ifndef GRELEMENT_H
#define GRELEMENT_H

#include <QPainter>
#include <QKeyEvent>

class Grelement
{
public:
    Grelement();
    virtual ~Grelement() = 0;

    virtual void draw(QPainter *painter) = 0;
    virtual void update() = 0;

    virtual void keyPressEvent(QKeyEvent *event) = 0;
    virtual void keyReleaseEvent(QKeyEvent *event) = 0;

    QPointF pos;
};

#endif // GRELEMENT_H
