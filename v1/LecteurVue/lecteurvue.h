#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();

private:
    Ui::LecteurVue *ui;

public slots:
    void lancerDiapo();
    void arreterDiapo();
    void suivant();
    void precedent();
    void changerVitesse();
    void chargerDiapo();
    void enleverDiapo();
    void aPropos();
    void quitter();
};
#endif // LECTEURVUE_H
