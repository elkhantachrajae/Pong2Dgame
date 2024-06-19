#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include "ball.h"
#include "paddle.h"


class GameWindow : public QWidget {
    Q_OBJECT

private:
    Ball* ball;
    Paddle* playerPaddle;
    Paddle* computerPaddle;
    QTimer* timer;
    int playerScore;
    int computerScore;
    QLabel* playerScoreLabel;
    QLabel* computerScoreLabel;
    QPushButton* playerButton;
    QPushButton* computerButton;
    QPushButton* restartButton;
    QPushButton* endButton;
    QTimer* startTimer;
    QLabel* startLabel;
public:
    GameWindow(QWidget* parent = nullptr) : QWidget(parent), playerScore(0), computerScore(0) {
        setFixedSize(700, 500);
        setStyleSheet("background-color: black;");
        setFocusPolicy(Qt::StrongFocus); // Assure que la fenêtre reçoit les événements clavier
        setWindowTitle("Gumii&Rajae's Pong2D");

        ball = new Ball(this);
        playerPaddle = new Paddle(this, true);
        computerPaddle = new Paddle(this, false);

        // Initialize and position the buttons for player and computer
        playerButton = new QPushButton("Player", this);
        playerButton->setStyleSheet("color: #AF8260; font-size: 20px; background-color: transparent; border: none;");
        playerButton->setGeometry(20, 10, 100, 30);

        computerButton = new QPushButton("Computer", this);
        computerButton->setStyleSheet("color: #AF8260; font-size: 20px; background-color:transparent; border: none;");
        computerButton->setGeometry(width() - 200, 10, 100, 30);

        // Initialize and position the score labels
        playerScoreLabel = new QLabel("0", this);
        playerScoreLabel->setStyleSheet("color: white;background-color: transparent;font-size: 20px;");
        playerScoreLabel->setGeometry(110, 10, 50, 30);

        computerScoreLabel = new QLabel("0", this);
        computerScoreLabel->setStyleSheet("color: white;background-color: transparent;font-size: 20px;");
        computerScoreLabel->setGeometry(width() - 90, 10, 50, 30);

        // Initialize and position the buttons
        restartButton = new QPushButton("Restart", this);
        restartButton->setGeometry(200, height() - 50, 120, 40);
        restartButton->setStyleSheet("color:white;background-color:#803D3B; font-size:20px;");
        connect(restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);

        endButton = new QPushButton("End", this);
        endButton->setGeometry(400, height() - 50, 120, 40);
        endButton->setStyleSheet("color:white;background-color:#803D3B; font-size:20px;");
        connect(endButton, &QPushButton::clicked, this, &GameWindow::endGame);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameWindow::updateGame);
        timer->start(16); // Environ 60 FPS
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        ball->draw(&painter);
        playerPaddle->draw(&painter);
        computerPaddle->draw(&painter);
    }

    void keyPressEvent(QKeyEvent* event) override {
        playerPaddle->handleKeyPress(event);
    }

    void keyReleaseEvent(QKeyEvent* event) override {
        playerPaddle->handleKeyRelease(event);
    }

private slots:
    void updateGame() {
        ball->move();
        ball->checkCollision(playerPaddle, computerPaddle);

        if (ball->isOutLeft()) {
            computerScore++;
            updateScoreLabels();
            ball->resetPosition();
        }

        if (ball->isOutRight()) {
            playerScore++;
            updateScoreLabels();
            ball->resetPosition();
        }

        playerPaddle->move(); // Met à jour la position de la raquette du joueur
        computerPaddle->move(ball->y());
        update();
    }

    void restartGame() {
        playerScore = 0;
        computerScore = 0;
        updateScoreLabels();
        ball->resetPosition();
    }

    void endGame() {
        close();
        emit gameEnded();
    }

private:
    void updateScoreLabels() {
        playerScoreLabel->setText(QString::number(playerScore));
        computerScoreLabel->setText(QString::number(computerScore));
    }

signals:
    void gameEnded();
};

#endif // GAMEWINDOW_H
