#ifndef CHANGERVITESSE_H
#define CHANGERVITESSE_H

#include <QDialog>

namespace Ui {
class ChangerVitesse;
}

class ChangerVitesse : public QDialog
{
    Q_OBJECT

public:
    explicit ChangerVitesse(QWidget *parent = nullptr);
    ~ChangerVitesse();
    int getVitesse();
    bool getModif();
    void setModif();

private:
    Ui::ChangerVitesse *ui;
    bool _modif;
    // devient vrai si l'utilisateur modifie la vitesse et valide la modif. Faux par défaut

private slots:
    void valider();
};

#endif // CHANGERVITESSE_H
