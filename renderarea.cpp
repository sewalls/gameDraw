
#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent) //clean up this WHOLE thing, all of it
    : QWidget(parent)

{
    setAutoFillBackground(true);
    pen.setColor(Qt::black);
    brush.setColor(Qt::black);
    brush.setStyle(Qt::BrushStyle::NoBrush);
    timer.start(10, this);
    food.move();
    elements.push_back(&player);
    elements.push_back(&food);
    elements.push_back(&enemyPlayer);
    elements.push_back(&enemyFood);
    elements.push_back(&enemyRandom);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    for(auto& e : elements) {
        painter.save();
        e->draw(&painter);
        painter.restore();
    }
}

void RenderArea::timerEvent(QTimerEvent *event) {
    checkEat();
    checkCollision();
    enemyPlayer.targetize(player.pos);
    enemyFood.targetize(food.pos);
    enemyRandom.randomDirection();
    for(auto& e : elements) {
        e->update();
    }
    update();
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

void RenderArea::checkEat() {
    if((player.pos - food.pos).manhattanLength() < 20) {
        player.grow(1);
        food.move();
    }
    if((enemyPlayer.pos - food.pos).manhattanLength() < 20) {
        enemyPlayer.grow(2);
        food.move();
    }
    if((enemyFood.pos - food.pos).manhattanLength() < 20) {
        enemyFood.grow(2);
        food.move();
    }
    if((enemyRandom.pos - food.pos).manhattanLength() < 20) {
        enemyRandom.grow(2);
        food.move();
    }
}

void RenderArea::checkCollision() { //implement this

}
