#include "secd.h"
#include "ui_secd.h"
#include "QComboBox"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
SecD::SecD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecD)
{


    ui->setupUi(this);
    QString type = ui->cb_type->currentText();
    if(type == "chapitre"){
    ui->cb_parent->hide();
    }

    else {
        ui->cb_parent->show();
    }

   rafraichir_parent();
   rafraichir_nomemclature();
   rafraichir_fournisseur();


    }



SecD::~SecD()
{
    delete ui;
}

void SecD::rafraichir_parent(){
ui->cb_parent->clear();
QSqlQuery query;
QString type = ui->cb_type->currentText();
if(type=="chapitre") ui->cb_parent->clear();
else if(type=="souschapitre") query.prepare("SELECT Titre FROM chapitre ");
else if(type=="article") query.prepare("SELECT Titre FROM souschapitre ");
else if(type=="programme") query.prepare("SELECT Titre FROM programme");
query.exec();

    while(query.next()){
        int i = 0;
        QStringList liste_parent;
        liste_parent.append(query.value(i).toString());
    ui->cb_parent->addItems(liste_parent);
        i = i+1;
      }
}

void SecD::on_cb_type_currentIndexChanged(const QString &arg1){

    rafraichir_parent();
    QString type = ui->cb_type->currentText();
    qDebug() << type;
    if(type == "chapitre"){
    ui->cb_parent->hide();
    }

    else {
        ui->cb_parent->show();
    }


}

void SecD::rafraichir_nomemclature(){
 QSqlQuery query;
 QString type_affichage;
 type_affichage = ui->cb_affichage_type->currentText();
 query.prepare("SELECT * FROM "+type_affichage);
 query.exec();
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery(query);
 ui->table_nomenclature->setModel(model);

}

void SecD::rafraichir_fournisseur(){
 QSqlQuery query;
 query.prepare("SELECT * FROM fournisseur");
 query.exec();
 QSqlQueryModel *model = new QSqlQueryModel();
 model->setQuery(query);
 ui->table_fournisseur->setModel(model);
}

void SecD::on_b_ajouter_clicked()
{
    QString titre = ui->f_titre->text();
    QString contenu = ui->f_contenu->text();
    QString description = ui->f_description->text();
    QString solde = ui->f_solde->text();
    QString type = ui->cb_type->currentText();
    QString parent_req = ui->cb_parent->currentText();
    QSqlQuery query2;
    QSqlQuery query;
    if(type=="chapitre") query2.prepare("INSERT INTO "+type+" (titre, contenu, description, solde) VALUES ('"+titre+"', '"+contenu+"', '"+description+"', '"+solde+"')");
    if(type=="souschapitre") query2.prepare("SELECT IDChap FROM chapitre WHERE Titre = ? ");
    else if(type=="article") query2.prepare("SELECT IDSC FROM souschapitre WHERE Titre = ? ");
    else if(type=="programme") query2.prepare("SELECT IDArticle FROM article WHERE Titre = ? ");
    query2.addBindValue(parent_req);
    query2.exec();
    if(query2.next()){
        QString id = query2.value(0).toString();


        if(type=="souschapitre") query.prepare("INSERT INTO "+type+" (titre, contenu, description, solde, IDChap) VALUES ('"+titre+"', '"+contenu+"', '"+description+"', '"+solde+"', '"+id+"')");
        else if(type=="article") query.prepare("INSERT INTO "+type+" (titre, contenu, description, solde, IDSC) VALUES ('"+titre+"', '"+contenu+"', '"+description+"', '"+solde+"', '"+id+"')");
        else if(type=="programme") query.prepare("INSERT INTO "+type+" (titre, contenu, description, solde, IDArticle) VALUES ('"+titre+"', '"+contenu+"', '"+description+"', '"+solde+"', '"+id+"')");

query.exec();
}
rafraichir_parent();
rafraichir_nomemclature();
}

void SecD::on_b_ajouter2_clicked()
{
    QString gerant = ui->f_gerant->text();
    QString rs = ui->f_rs->text();
    QString description = ui->t_description->toPlainText();
    QString popularite = ui->f_popu->text();
    QString ville = ui->f_ville->text();
    QString domaine = ui->f_domaine->text();
    QString creation = ui->f_creation->text();
    QSqlQuery query;
    query.prepare("INSERT INTO fournisseur (Gerant, RaisonSocial, Description, Domaine, Creation, Popularite, Ville) VALUES ('"+gerant+"', '"+rs+"', '"+description+"', '"+domaine+"', '"+creation+"', '"+popularite+"', '"+ville+"')");
    query.exec();
    rafraichir_fournisseur();
}

void SecD::on_cb_affichage_type_currentIndexChanged(const QString &arg1)
{
    rafraichir_nomemclature();
}

void SecD::on_b_supprimer_clicked()
{
    QModelIndex index = ui->table_nomenclature->currentIndex();

    int selectedR = index.row();

    int id = index.sibling(selectedR, 0).data().toInt();

   QString type = ui->cb_affichage_type->currentText();

   QString idHeader = ui->table_nomenclature->model()->headerData(0, Qt::Horizontal).toString();
   QSqlQuery query;

   query.prepare("DELETE FROM "+ type +" WHERE "+ idHeader +" = :id");
   query.bindValue(":id",id);
   query.exec();
rafraichir_nomemclature();
}

void SecD::on_b_supprimer2_clicked()
{
    QModelIndex index = ui->table_fournisseur->currentIndex();

    int selectedR = index.row();

    int id = index.sibling(selectedR, 0).data().toInt();

   QString idHeader = ui->table_fournisseur->model()->headerData(0, Qt::Horizontal).toString();
   QSqlQuery query;

   query.prepare("DELETE FROM fournisseur WHERE "+ idHeader +" = :id");
   query.bindValue(":id",id);
   query.exec();
rafraichir_fournisseur();
}
