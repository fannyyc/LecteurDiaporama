#ifndef LECTEURVUE_H
#define LECTEURVUE_H
#include "image.h"
#include "changervitesse.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE


typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les images


class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    void avancer();             // incrémente _posImageCourante, modulo nbImages()
    void reculer();             // décrémente _posImageCourante, modulo nbImages()
    void changerDiaporama(unsigned int pNumDiaporama);    // permet de choisir un diaporama, 0 si aucun diaporama souhaité
    void afficher();            // affiche les informations sur lecteur-diaporama et image courante
    unsigned int nbImages();    // affiche la taille de _diaporama
    Image* imageCourante();     // retourne le pointeur vers l'image courante
    unsigned int numDiaporamaCourant();

private:
    Ui::LecteurVue *ui;
    unsigned _numDiaporamaCourant;   // numéro du diaporama courant, par défaut 0
    Diaporama _diaporama;            // pointeurs vers les images du diaporama
    unsigned int _posImageCourante;  /* position, dans le diaporama,
                                        de l'image courante.
                                        Indéfini quand diaporama vide.
                                        Démarre à 0 quand diaporama non vide */
    QTimer *monTimer;
    int _vitesse;
    bool _estManuel = true;                // vrai si le diapo est en manuel, faux si en mode auto

private:
    void chargerDiaporama();    // charge dans _diaporama les images du _numDiaporamaCourant
    void viderDiaporama();      // vide _diaporama de tous ses objets image et les delete
    bool compareRang(Image, Image);
    void afficherRang(Image*);
    void afficherTitre(Image*);
    void afficherCategorie(Image*);
    void afficherImage(Image*);
    void demarrerTimer();
    void arreterTimer();
    void setVitesse(int);
    void setEstManuel();
    int getVitesse();

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

#endif //LECTEURVUE_H
