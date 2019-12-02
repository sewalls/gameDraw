
#include "renderarea.h"

#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
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
    switch(state) {
    case(GameState::Playing): {
        for(auto& e : elements) {
            painter.save();
            e->draw(&painter);
            painter.restore();
        }
        break;
    }
    case(GameState::Dead): {
        painter.drawText(550, 350, "DEAD");
        break;
    }
    case(GameState::Menu): {
        painter.drawText(500, 350, "SPACE TO PLAY");
        break;
    }
    }
}

void RenderArea::timerEvent(QTimerEvent *event) {
    switch(state) {
    case (GameState::Playing): {
        checkEat();
        checkCollision(player, enemyPlayer);
        checkCollision(player, enemyFood);
        checkCollision(player, enemyRandom);
        enemyPlayer.targetize(player.pos);
        enemyFood.targetize(food.pos);
        enemyRandom.randomDirection();
        for(auto& e : elements) {
            e->update();
        }
        update();
        break;
    }
    case (GameState::Dead): {
        break;
    }
    case (GameState::Menu): {
        break;
    }
    }
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case (Qt::Key_E): {
        break;
    }
    case (Qt::Key_Space): {
        state = GameState::Playing;
    }
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

void RenderArea::checkCollision(Player p1, Enemy e1) { //implement this
    for(unsigned int i = e1.prevPos.size() - e1.size; i < e1.prevPos.size(); i++) {
        if(QLineF(p1.pos, e1.prevPos[i]).length() <= 20) {
            state = GameState::Dead;
        }
    }
}
