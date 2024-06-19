#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QLabel>
#include<QFrame>

class SignUpWindow : public QWidget {
    Q_OBJECT

public:
    SignUpWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setFixedSize(700, 500);
        setStyleSheet("background-color: black;");
        setWindowTitle("Gumii&Rajae's Pong2D");

        title = new QLabel("Welcome to Gumii&Rajae's Pong2D", this);
        title->move(120, 60);
        QFont font("Arial", 20, QFont::Bold);
        title->setFont(font);
        title->setStyleSheet("color:#803D3B;background-color: transparent;");

        frame = new QFrame(this);
        frame->setGeometry(190, 150, 300, 220); // Adjust the size and position as needed
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(2);
        frame->setStyleSheet("border: 2px solid #803D3B;");


        usernameEdit = new QLineEdit(this);
        usernameEdit->setPlaceholderText("Username");
        usernameEdit->setStyleSheet("color: black; font-size: 20px; background-color: white; border: none;");
        usernameEdit->setGeometry(240, 190, 200, 30);

        passwordEdit = new QLineEdit(this);
        passwordEdit->setPlaceholderText("Password");
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setStyleSheet("color: black; font-size: 20px; background-color: white; border: none;");
        passwordEdit->setGeometry(240, 250, 200, 30);


        signUpButton = new QPushButton("Sign Up", this);
        signUpButton->setStyleSheet("color: #803D3B; font-size: 20px; background-color: black; ");
        signUpButton->setGeometry(250, 300, 80, 30);

        connect(signUpButton, &QPushButton::clicked, this, &SignUpWindow::signUp);
    }

signals:
    void signUpSuccess();

private slots:
    void signUp() {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();

        if (username.isEmpty() || password.isEmpty()) {
            //QMessageBox::warning(this, "Error", "Please fill all fields.");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Please fill all fields.");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: black; color: white; }"
                "QLabel { color: white; }"
                "QPushButton { color: white; background-color: #803D3B; }"
                );
            msgBox.exec();
            return;
        }

        if (createAccount(username, password)) {
           // QMessageBox::information(this, "Success", "Account created successfully.");
            emit signUpSuccess();
            this->close();
        } else {
            //QMessageBox::warning(this, "Error", "Username already exists.");
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setText("Username already exists.");
            msgBox.setStyleSheet(
                "QMessageBox { background-color: black; color: white; }"
                "QLabel { color: white; }"
                "QPushButton { color: white; background-color: #803D3B; }"
                );
            msgBox.exec();
        }
    }

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *signUpButton;
    QLabel *title;
    QFrame *frame;

    bool createAccount(const QString &username, const QString &password) {
        QSqlDatabase db = QSqlDatabase::database();

        QSqlQuery query;
        query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        return query.exec();
    }
};

#endif // SIGNUPWINDOW_H
