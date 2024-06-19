#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <Qt>

class Paddle {
private:
    int m_x, m_y;
    int m_width, m_height;
    int dy;
    bool isPlayer;
    QWidget* parent;
    Qt::Key upKey;
    Qt::Key downKey;

public:
    Paddle(QWidget* parent, bool isPlayer, Qt::Key upKey = Qt::Key_S, Qt::Key downKey = Qt::Key_W)
        : m_x(isPlayer ? 30 : parent->width() - 50), m_y(parent->height() / 2 - 50),
        m_width(10), m_height(100), dy(0), isPlayer(isPlayer), parent(parent),
        upKey(upKey), downKey(downKey) {}

    void draw(QPainter* painter) {
        painter->setBrush(Qt::white);
        painter->drawRect(m_x, m_y, m_width, m_height);
    }

    void move(int ballY = 0) {
        if (isPlayer) {
            m_y += dy;
            if (m_y < 0) m_y = 0;
            if (m_y + m_height > parent->height()) m_y = parent->height() - m_height;
        } else {
            // Computer paddle movement logic
            if (ballY < m_y + m_height / 2) m_y -= 5;
            if (ballY > m_y + m_height / 2) m_y += 5;
        }
    }

    void handleKeyPress(QKeyEvent* event) {
        if (isPlayer) {
            if (event->key() == upKey) dy = -6;    // Move up
            if (event->key() == downKey) dy = 6;   // Move down
        }
    }

    void handleKeyRelease(QKeyEvent* event) {
        if (isPlayer) {
            if (event->key() == upKey || event->key() == downKey) dy = 0;
        }
    }

    int x() const { return m_x; }
    int y() const { return m_y; }
    int width() const { return m_width; }
    int height() const { return m_height; }
    void setX(int x) {
        m_x = x;
    }

    // Method to set the y-coordinate of the paddle
    void setY(int y) {
        m_y = y;
    }
};

#endif // PADDLE_H
