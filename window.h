#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QMovie>
#include "gamewindow.h"
#include "PlayerVsPlayerWindow.h"


class Window : public QWidget {
    Q_OBJECT

private:
    QLabel* title;
    QPushButton* button_player;
    QPushButton* button_pc;
    QLabel* gifLabel;
    QMovie* gifMovie;
    QLabel* title1;

public:
    Window(QWidget* parent = nullptr) : QWidget(parent) {
        setFixedSize(700, 500);
         setWindowTitle("Gumii&Rajae's Pong2D");
        // Title
        title = new QLabel("Welcome to Gumii&Rajae's Pong2D", this);
        title->move(120, 60);
        QFont font("Arial", 20, QFont::Bold);
        title->setFont(font);
        title->setStyleSheet("color:#AF8260;");
        setStyleSheet("background-color: black;");

        // Buttons
        button_player = new QPushButton("Player VS Player", this);
        button_player->move(200, 300);
        button_player->setStyleSheet("color:white;background-color:#803D3B;font-size:20px;");
        button_player->setFixedSize(300, 40);

        button_pc = new QPushButton("Player VS Computer", this);
        button_pc->move(200, 360);
        button_pc->setStyleSheet("color:white;background-color:#803D3B; font-size:20px;");
        button_pc->setFixedSize(300, 40);

        // Gif
        gifLabel = new QLabel(this);
        gifLabel->setGeometry(200, 120, 300, 150);
        gifMovie = new QMovie("C:\\Users\\ThinkPad\\Desktop\\pictures\\gif.gif");
        gifLabel->setScaledContents(true);
        gifLabel->setMovie(gifMovie);
        gifMovie->start();

        // Goodluck
        title1 = new QLabel("Good Luck !", this);
        title1->move(400, 450);
        title1->setFont(font);
        title1->setStyleSheet("color:#AF8260;");

        QObject::connect(button_pc, &QPushButton::clicked, this, &Window::startGame);
        QObject::connect(button_player, &QPushButton::clicked, this, &Window::startPlayerVsPlayer);

    }

public slots:
    void startGame() {
        GameWindow* gameWindow = new GameWindow();
        connect(gameWindow, &GameWindow::gameEnded, this, &Window::show);
        this->hide();
        gameWindow->show();
    }

    void startPlayerVsPlayer() {
        PlayerVsPlayerWindow* playerVsPlayerWindow = new PlayerVsPlayerWindow();
        playerVsPlayerWindow->show();
    }

};

#endif // WINDOW_H
