#include "changervitesse.h"
#include "ui_changervitesse.h"

ChangerVitesse::ChangerVitesse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangerVitesse)
{
    ui->setupUi(this);

    _modif = false;

    connect(ui->bValider, SIGNAL(clicked()), this, SLOT(valider()));
    connect(ui->bAnnuler, SIGNAL(clicked()), this, SLOT(close()));
}

ChangerVitesse::~ChangerVitesse()
{
    delete ui;
}

void ChangerVitesse::valider()
{
    getVitesse();
    setModif();
    close();
}

int ChangerVitesse::getVitesse()
{
    return ui->sNvelleVitesse->value();
}

bool ChangerVitesse::getModif()
{
    return _modif;
}

void ChangerVitesse::setModif()
{
    _modif = true;
}
