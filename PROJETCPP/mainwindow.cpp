#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include "ui_scdialog.h"
#include "secd.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_B_login_clicked()
{
    QString username = ui->lineEdit_username->text();
        QString password = ui->lineEdit_password->text();
        QSqlQuery query;
           query.prepare("SELECT pseudo, MDP FROM administrateur WHERE pseudo = :username AND MDP = :password ");
           query.bindValue(":username",username);
           query.bindValue(":password",password);
           query.exec();
            if(query.next()){

                   QMessageBox::information(this,"Connexion","Vous êtes connecté");
                   hide();
                   SecD secdialog;
                   secdialog.setModal(true);
                   secdialog.exec();
               }

               else{
                   QMessageBox::information(this,"Erreur","Votre login ou mot de passe est incorrect");
               }

}

void MainWindow::on_B_inscription_clicked()
{
    QString username = ui->lineEdit_username_2->text();
    QString password = ui->lineEdit_password_2->text();
    QString confirmation_pass = ui->lineEdit_confirmpass->text();
    QSqlQuery query;
    QSqlQuery query2;
    query.prepare("SELECT pseudo FROM administrateur WHERE pseudo = :username ");
    query.bindValue(":username",username);
    query.exec();
    if(query.next()){

        QMessageBox::information(this,"Erreur","Le pseudo existe déjà");
    }

    else if (confirmation_pass != password){
         QMessageBox::information(this,"Erreur","Les mot de passes sont différents");
    }
    else {

    query2.prepare("INSERT INTO administrateur (Pseudo, MDP) VALUES ( :username , :password )");
               query2.bindValue(":username",username);
               query2.bindValue(":password",password);
               query2.exec();
                   QMessageBox::information(this,"Inscription","Félicitations ! Vous êtes inscrit !");
               }
}
