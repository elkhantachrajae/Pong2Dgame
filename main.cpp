#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "login.h"

void initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Error", "Database connection failed.");
        exit(-1);
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE, "
               "password TEXT)");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    initializeDatabase();

    LoginWindow w;
    w.show();

    return app.exec();
}
