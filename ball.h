#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QPainter>
#include "paddle.h"

class Ball {
private:
    int m_x, m_y; // Renommé pour éviter les conflits
    int dx, dy;
    int m_size;
    QWidget* parent;

public:
    Ball(QWidget* parent) : m_x(350), m_y(250), dx(5), dy(5), m_size(20), parent(parent) {}

    void draw(QPainter* painter) {
        painter->setBrush(Qt::white);
        painter->drawEllipse(m_x, m_y, m_size, m_size);
    }

    void move() {
        m_x += dx;
        m_y += dy;

        // Rebondir sur le haut et le bas de la fenêtre
        if (m_y <= 0 || m_y + m_size >= parent->height()) {
            dy = -dy;
        }
    }

    bool isOutLeft() const {
        return m_x < 0;
    }

    bool isOutRight() const {
        return m_x + m_size > parent->width();
    }

    void checkCollision(Paddle* playerPaddle, Paddle* computerPaddle) {
        // Vérifie la collision avec la raquette du joueur
        if (m_x <= playerPaddle->x() + playerPaddle->width() &&
            m_y + m_size >= playerPaddle->y() &&
            m_y <= playerPaddle->y() + playerPaddle->height()) {
            dx = -dx;
            m_x = playerPaddle->x() + playerPaddle->width(); // Ajuster la position pour éviter la superposition
        }

        // Vérifie la collision avec la raquette de l'ordinateur
        if (m_x + m_size >= computerPaddle->x() &&
            m_y + m_size >= computerPaddle->y() &&
            m_y <= computerPaddle->y() + computerPaddle->height()) {
            dx = -dx;
            m_x = computerPaddle->x() - m_size; // Ajuster la position pour éviter la superposition
        }
    }

    void resetPosition() {
        m_x = parent->width() / 2 - m_size / 2;
        m_y = parent->height() / 2 - m_size / 2;
        dx = 5; // Réinitialiser la direction
        dy = 5;
    }

    int x() const { return m_x; }
    int y() const { return m_y; }
    int size() const { return m_size; }
};

#endif // BALL_H

