#include <QApplication>
#include "mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <string>
//Alexandre SOARES Alex LAMEIRAO Ahmet-Kadir ONSEKIZ  
int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainWindow m;
    m.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
       db.setHostName("127.0.0.1");
       db.setPort(3306);
       db.setDatabaseName("smart_finances");
       db.setUserName("root");
       db.setPassword("usbw");
       if (db.open())   {
          qDebug() << "Connected!";
       }
       else   {
         qDebug() << "Failed to connect.";
         return 0;
       }

    return app.exec();
}
