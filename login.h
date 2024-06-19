#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include<QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include<QFrame>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "window.h"
#include "signupwindow.h"

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(700, 500);
        setStyleSheet("background-color: black;");
        setWindowTitle("Gumii&Rajae's Pong2D");

        title = new QLabel("Welcome to Gumii&Rajae's Pong2D", this);
        title->move(120, 60);
        QFont font("Arial", 20, QFont::Bold);
        title->setFont(font);
        title->setStyleSheet("color:#AF8260;background-color: transparent;");

        info = new QLabel("Enter your username and password or sign up if you don't have an account", this);
        info->move(110, 110);
        info->setStyleSheet("color:white;background-color: transparent; font-size:15px;");


        frame = new QFrame(this);
        frame->setGeometry(190, 150, 300, 220); // Adjust the size and position as needed
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(2);
        frame->setStyleSheet("border: 2px solid #AF8260;");

        usernameEdit = new QLineEdit(this);
        usernameEdit->setPlaceholderText("Username");
        usernameEdit->setStyleSheet("color: black; font-size: 20px; background-color: white; border: none;");
        usernameEdit->setGeometry(240, 190, 200, 30);

        passwordEdit = new QLineEdit(this);
        passwordEdit->setPlaceholderText("Password");
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setStyleSheet("color: black; font-size: 20px; background-color: white; border: none;");
        passwordEdit->setGeometry(240, 250, 200, 30);

        loginButton = new QPushButton("Login", this);
        loginButton->setStyleSheet("color: #AF8260; font-size: 20px; background-color: black;");
        loginButton->setGeometry(250, 300, 80, 30);
        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::login);

        signUpButton = new QPushButton("Sign Up", this);
        signUpButton->setStyleSheet("color: #AF8260; font-size: 20px; background-color: black; ");
        signUpButton->setGeometry(340, 300, 80, 30);


        connect(signUpButton, &QPushButton::clicked, this, &LoginWindow::showSignUp);
    }

private slots:
    void login() {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();

        if (validateCredentials(username, password)) {
            //QMessageBox::information(this, "Success", "Login successful.");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Success");
            msgBox.setText("Login successful");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: black; color: white; }"
                "QLabel { color: white; }"
                "QPushButton { color: white; background-color: #803D3B; }"
                );
            msgBox.exec();
            Window *mainWindow = new Window();
            mainWindow->show();
            this->close();
        } else {
            //QMessageBox::warning(this, "Error", "Invalid username or password.");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Invalid username or password.");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: black; color: white; }"
                "QLabel { color: white; }"
                "QPushButton { color: white; background-color: #803D3B; }"
                );
            msgBox.exec();
        }
    }

    void showSignUp() {
        SignUpWindow *signUpWindow = new SignUpWindow();
        connect(signUpWindow, &SignUpWindow::signUpSuccess, this, &LoginWindow::onSignUpSuccess);
        signUpWindow->show();
    }

    void onSignUpSuccess() {
       //QMessageBox::information(this, "Success", "Account created successfully. Please login.");
        QMessageBox msgBox;
        msgBox.setWindowTitle("Success");
        msgBox.setText("Account created successfully. Please login.");
        msgBox.setStyleSheet(
            "QMessageBox { background-color: black; color: white; }"
            "QLabel { color: white; }"
            "QPushButton { color: white; background-color: #803D3B; }"
            );
        msgBox.exec();
    }

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *signUpButton;
    QLabel *title;
    QLabel *info;
    QFrame *frame;

    bool validateCredentials(const QString &username, const QString &password) {
        // Connexion à la base de données (à remplacer par vos propres paramètres de connexion)
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("database.db");

        if (!db.open()) {
            QMessageBox::critical(this, "Error", "Database connection failed.");
            return false;
        }

        // Vérification des informations de connexion
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        query.exec();

        return query.next(); // Renvoie true si les informations sont correctes
    }
};

#endif // LOGINWINDOW_H
