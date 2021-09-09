#ifndef NOMENCLATURE_H
#define NOMENCLATURE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <string>
using namespace std;

class Nomenclature
{
private:
    string titre;
    string contenu;
    string description;
    int solde;
    string type;
    string parent;

public:

    Nomenclature();
    ~Nomenclature();
};

#endif // NOMENCLATURE_H
