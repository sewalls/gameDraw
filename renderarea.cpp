
#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)/*, food({200, 220})*/

{
    setAutoFillBackground(true);
    pen.setColor(Qt::black);
    brush.setColor(Qt::black);
    brush.setStyle(Qt::BrushStyle::NoBrush);
    timer.start(10, this);
    food.move();
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(pen);
    player.draw(&painter);
    testPlayer.draw(&painter);
    testPlayerTwo.draw(&painter);
    food.draw(&painter);
    painter.setBrush(brush);
    //enemyTest.draw(&painter);
}

void RenderArea::timerEvent(QTimerEvent *event) {
    update();
    player.update();
    testPlayer.target(player);
    testPlayer.update();
    testPlayerTwo.randomDirection();
    testPlayerTwo.update();
    food.update();
    playerEat();
    //enemyTest.targetize(player.pos);
    //enemyTest.update();
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case (Qt::Key_E):

        break;
    }
    player.keyPressEvent(event);
    update();
}

void RenderArea::keyReleaseEvent(QKeyEvent *event) {
    player.keyReleaseEvent(event);
    update();
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    update();
}

void RenderArea::playerEat() {
    if((player.pos - food.pos).manhattanLength() < 20) {
        player.grow(1);
        food.move();
    }
}

void RenderArea::collision() {

}
