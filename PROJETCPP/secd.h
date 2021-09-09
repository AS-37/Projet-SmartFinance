#ifndef SECD_H
#define SECD_H

#include <QDialog>

namespace Ui {
class SecD;
}

class SecD : public QDialog
{
    Q_OBJECT

public:
    explicit SecD(QWidget *parent = nullptr);
    ~SecD();
    void rafraichir_parent();
    void rafraichir_nomemclature();
    void rafraichir_fournisseur();

private slots:
    void on_cb_type_currentIndexChanged(const QString &arg1);

    void on_b_ajouter_clicked();

    void on_b_ajouter2_clicked();

    void on_cb_affichage_type_currentIndexChanged(const QString &arg1);

    void on_b_supprimer_clicked();

    void on_b_supprimer2_clicked();

private:
    Ui::SecD *ui;
};

#endif // SECD_H
