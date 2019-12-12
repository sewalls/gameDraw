
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
    enemyPlayer.setColor(Qt::darkMagenta);
    enemyFood.setColor(Qt::darkRed);
    enemyRandom.setColor(Qt::darkYellow);
    elements.push_back(&player);
    elements.push_back(&food);
    elements.push_back(&enemyPlayer);
    elements.push_back(&enemyFood);
    elements.push_back(&enemyRandom);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(40);
    painter.setFont(font);
    switch(state) {
    case(GameState::Playing): {
        for(auto& e : elements) {
            painter.save();
            e->draw(&painter);
            painter.restore();
        }
        painter.save();                     //this draws those border rectangles
        painter.setBrush(Qt::black);
        painter.setOpacity(0.5);
        painter.drawRect(0, 0, 1600, 100);
        painter.drawRect(0, 0, 100, 900);
        painter.drawRect(1500, 0, 100, 900);
        painter.drawRect(0, 800, 1600, 100);
        painter.restore();
        break;
    }
    case(GameState::Dead): {
        painter.drawText(QPointF{700, 450}, "DEAD");
        painter.drawText(QPointF{650, 500}, "Score: " + QString::fromStdString(std::to_string(player.getScore())));
        break;
    }
    case(GameState::Menu): {
        painter.drawText(650, 450, "SPACE TO PLAY");
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
    case (Qt::Key_R): {
        player.reset();
        enemyPlayer.reset();
        enemyFood.reset();
        enemyRandom.reset();
        state = GameState::Playing;
        break;
    }
    case (Qt::Key_Space): {
        state = GameState::Playing;
        break;
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
        player.bumpScore();
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

void RenderArea::checkCollision(Player& p1, Enemy& e1) {
    if(e1.getWait() < 0) {
        for(unsigned int i = e1.prevPos.size() - e1.getSize(); i < e1.prevPos.size(); i++) { //enemy kills you
            if(QLineF(p1.pos, e1.prevPos[i]).length() <= 20) {
                state = GameState::Dead;
            }
        }

        for(unsigned int i = p1.getPrevPos().size() - p1.getSize(); i < p1.getPrevPos().size(); i++) { //you kill enemy
            if(QLineF(e1.pos, p1.getPrevPos()[i]).length() <= 20) {
                e1.reset();
                p1.bumpScore();
            }
        }
    }
}
