#ifndef PLAYERVSPLAYERWINDOW_H
#define PLAYERVSPLAYERWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include "ball.h"
#include "paddle.h"

class PlayerVsPlayerWindow : public QWidget {
    Q_OBJECT

private:
    Ball* ball;
    Paddle* player1Paddle;
    Paddle* player2Paddle;
    QTimer* timer;
    int player1Score;
    int player2Score;
    QLabel* player1ScoreLabel;
    QLabel* player2ScoreLabel;
    QPushButton* restartButton;
    QPushButton* endButton;
    QPushButton* playerButton;
    QPushButton* player2Button;

public:
    PlayerVsPlayerWindow(QWidget* parent = nullptr) : QWidget(parent), player1Score(0), player2Score(0) {
        setFixedSize(700, 500);
        setStyleSheet("background-color: black;");
        setFocusPolicy(Qt::StrongFocus); // Ensure that the window receives keyboard events

        ball = new Ball(this);

        // Player 1 paddle using keys W and S
        player1Paddle = new Paddle(this, true, Qt::Key_S, Qt::Key_W); // Swapped keys
        player1Paddle->setX(30); // Set x-coordinate for player 1 paddle

        // Player 2 paddle using arrow keys
        player2Paddle = new Paddle(this, true, Qt::Key_Up, Qt::Key_Down);
        player2Paddle->setX(width() - 40); // Set x-coordinate for player 2 paddle

        // Initialize and position the score labels for each player
        player1ScoreLabel = new QLabel("0",this);
        player1ScoreLabel->setStyleSheet("color: white;background-color: transparent;font-size: 20px;");
        player1ScoreLabel->setGeometry(110, 10, 50, 30);

        player2ScoreLabel = new QLabel("0",this);
        player2ScoreLabel->setStyleSheet("color: white;background-color: transparent;font-size: 20px;");
        player2ScoreLabel->setGeometry(width() - 90, 10, 50, 30);

        // Initialize and position the buttons
        restartButton = new QPushButton("Restart", this);
        restartButton->setGeometry(200, height() - 50, 120, 40);
        restartButton->setStyleSheet("color:white;background-color:#803D3B; font-size:20px;");
        connect(restartButton, &QPushButton::clicked, this, &PlayerVsPlayerWindow::restartGame);

        endButton = new QPushButton("End", this);
        endButton->setGeometry(400, height() - 50, 120, 40);
        endButton->setStyleSheet("color:white;background-color:#803D3B; font-size:20px;");
        connect(endButton, &QPushButton::clicked, this, &PlayerVsPlayerWindow::endGame);

        // Initialize and position the player buttons
        playerButton = new QPushButton("Player 1", this);
        playerButton->setStyleSheet("color: #AF8260; font-size: 20px; background-color: transparent; border: none;");
        playerButton->setGeometry(20, 10, 100, 30);

        player2Button = new QPushButton("Player 2", this);
        player2Button->setStyleSheet("color: #AF8260; font-size: 20px; background-color: transparent; border: none;");
        player2Button->setGeometry(width() - 200, 10, 100, 30);

        // Initialize and start the timer for game updates
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &PlayerVsPlayerWindow::updateGame);
        timer->start(16); // Approximately 60 FPS
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        ball->draw(&painter);
        player1Paddle->draw(&painter);
        player2Paddle->draw(&painter);
    }

    void keyPressEvent(QKeyEvent* event) override {
        // Check key events for player 1 paddle
        player1Paddle->handleKeyPress(event);

        // Check key events for player 2 paddle
        player2Paddle->handleKeyPress(event);
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        // Check key release events for player 1 paddle
        player1Paddle->handleKeyRelease(event);

        // Check key release events for player 2 paddle
        player2Paddle->handleKeyRelease(event);
    }

private slots:
    void updateGame() {
        ball->move();
        ball->checkCollision(player1Paddle, player2Paddle);

        if (ball->isOutLeft()) {
            player2Score++;
            updateScoreLabels();
            ball->resetPosition();
        }

        if (ball->isOutRight()) {
            player1Score++;
            updateScoreLabels();
            ball->resetPosition();
        }

        player1Paddle->move(); // Update player 1 paddle position
        player2Paddle->move(); // Update player 2 paddle position
        update();
    }

    void restartGame() {
        player1Score = 0;
        player2Score = 0;
        updateScoreLabels();
        ball->resetPosition();
    }

    void endGame() {
        close();
    }

private:
    void updateScoreLabels() {
        player1ScoreLabel->setText(QString::number(player1Score));
        player2ScoreLabel->setText(QString::number(player2Score));
    }
signals:
    void gameEnded();
};

#endif // PLAYERVSPLAYERWINDOW_H
