#include "lecteurvue.h"
#include "ui_lecteurvue.h"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Mode :");

    QCoreApplication * instapp = QCoreApplication::instance();

    QObject::connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(lancerDiapo()));
    QObject::connect(ui->bArreterDiapo, SIGNAL(clicked()), this, SLOT(arreterDiapo()));
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(suivant()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(precedent()));
    QObject::connect(ui->aChangerVitesse, SIGNAL(triggered()), this, SLOT(changerVitesse()));
    QObject::connect(ui->aChargerDiapo, SIGNAL(triggered()), this, SLOT(chargerDiapo()));
    QObject::connect(ui->aEnleverDiapo, SIGNAL(triggered()), this, SLOT(enleverDiapo()));
    QObject::connect(ui->aAPropos, SIGNAL(triggered()), this, SLOT(aPropos()));
    QObject::connect(ui->aQuitter, SIGNAL(triggered()), instapp, SLOT(quit()));
}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::lancerDiapo()
{
    qDebug() << "Lancer diapo" << Qt::endl;
}

void LecteurVue::arreterDiapo()
{
    qDebug() << "Arreter diapo" << Qt::endl;
}

void LecteurVue::suivant()
{
    qDebug() << "Image suivante" << Qt::endl;
}

void LecteurVue::precedent()
{
    qDebug() << "Image précédente" << Qt::endl;
}

void LecteurVue::changerVitesse()
{
    qDebug() << "Changement de vitesse" << Qt::endl;
}

void LecteurVue::chargerDiapo()
{
    qDebug() << "Charger diapo" << Qt::endl;
}

void LecteurVue::enleverDiapo()
{
    qDebug() << "Enlever diapo" << Qt::endl;
}

void LecteurVue::aPropos()
{
    qDebug() << "A propos" << Qt::endl;
}

void LecteurVue::quitter()
{
    qDebug() << "Quitter" << Qt::endl;
}
