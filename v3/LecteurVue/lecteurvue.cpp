#include "lecteurvue.h"
#include "ui_lecteurvue.h"
#include <QMessageBox>
#include <algorithm>
#include <QTimer>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Mode : Manuel");

    QPixmap pix("F:/S2/S201/v3/cartesDisney/Disney_tapis.png");
    ui->lImage->setPixmap(pix);
    ui->lImage->show();
    _numDiaporamaCourant = 0;   // =  le lecteur est vide


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

    _vitesse = 3000;
}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::lancerDiapo()
{

    monTimer=new QTimer();
    QObject::connect(monTimer, SIGNAL(timeout()), this, SLOT(suivant()));

    demarrerTimer();
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this,SLOT(arreterDiapo()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this,SLOT(arreterDiapo()));

    setEstManuel();
    ui->statusbar->showMessage("Mode : Automatique");

}

void LecteurVue::demarrerTimer()
{
    monTimer->start(_vitesse);
}

void LecteurVue::arreterDiapo()
{
    if (!_estManuel) {
        arreterTimer();
        setEstManuel();
        ui->statusbar->showMessage("Mode : Manuel");
    }
}

void LecteurVue::arreterTimer()
{
    monTimer->stop();
}

void LecteurVue::setEstManuel()
{
    if (_estManuel) {
        _estManuel = false;
    }
    else {
        _estManuel = true;
    }
}

void LecteurVue::suivant()
{
    avancer();
}

void LecteurVue::precedent()
{
    reculer();
}

void LecteurVue::changerVitesse()
{
    qDebug() << "Changement de vitesse" << Qt::endl;
}

void LecteurVue::chargerDiapo()
{
    chargerDiaporama();
}

void LecteurVue::enleverDiapo()
{
    viderDiaporama();
}

void LecteurVue::aPropos()
{

    QMessageBox *msgBoxAPropos = new QMessageBox();
    msgBoxAPropos->setStandardButtons(QMessageBox::Ok);
    msgBoxAPropos->setText("Auteurs : BEGUINEL Kévin, BERTRAND Lou & CONSTANS Fanny\nVersion v2");
    msgBoxAPropos->setWindowTitle("A propos de...");
    msgBoxAPropos->exec();        // on ne prend pas en compte la valeur retournée
}

void LecteurVue::quitter()
{
    qDebug() << "Quitter" << Qt::endl;
}

void LecteurVue::avancer()
{
    if ((*this)._posImageCourante >= nbImages()-1)
    {
        (*this)._posImageCourante=0;
    }
    else
    {
        (*this)._posImageCourante+=1;
    }
    this->afficher();
}

void LecteurVue::reculer()
{
    if ((*this)._posImageCourante<=0)
    {
        (*this)._posImageCourante=nbImages()-1;
    }
    else
    {
        (*this)._posImageCourante--;
    }
    this->afficher();
}

void LecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void LecteurVue::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    if (_numDiaporamaCourant != 0)
    {
        viderDiaporama();
    }

    _numDiaporamaCourant = 1;
    Image* imageACharger;
    imageACharger = new Image(3, "Animal", "Le dalmatien", "F:/S2/S201/v3/cartesDisney/Disney_1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "Personne", "Alice au Pays des Merveilles", "F:/S2/S201/v3/cartesDisney/Disney_2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "Animal", "Bambi", "F:/S2/S201/v3/cartesDisney/Disney_3.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "Personne", "Blanche-Neige", "F:/S2/S201/v3/cartesDisney/Disney_4.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(5, "Animal", "Daisy", "F:/S2/S201/v3/cartesDisney/Disney_5.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(6, "Animal", "La Belle et le Clochard", "F:/S2/S201/v3/cartesDisney/Disney_6.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(7, "Personne", "Jasmine", "F:/S2/S201/v3/cartesDisney/Disney_7.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(8, "Animal", "Donald", "F:/S2/S201/v3/cartesDisney/Disney_8.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(9, "Animal", "Donald", "F:/S2/S201/v3/cartesDisney/Disney_9.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(10, "Animal", "Mushu", "F:/S2/S201/v3/cartesDisney/Disney_10.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(11, "Animal", "Dumbo", "F:/S2/S201/v3/cartesDisney/Disney_11.gif");
    _diaporama.push_back(imageACharger);

     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
     // A FAIRE
    for (int i = nbImages() - 1; i >= 0; i--) {
             for (int j = 0; j < i; j++) {
                 if (_diaporama[j]->getRang() > _diaporama[j + 1]->getRang()) {
                     Image * permut = _diaporama[j];
                     _diaporama[j] = _diaporama[j + 1];
                     _diaporama[j + 1] = permut;
                 }
             }
         }

     _posImageCourante = 0;
     afficher();

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void LecteurVue::viderDiaporama()
{
    if (nbImages() > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;

     _numDiaporamaCourant=0;
     // on affice l'image tapis
     QPixmap pix("F:/S2/S201/v2/cartesDisney/Disney_tapis.png");
     ui->lImage->setPixmap(pix);
     ui->lImage->show();

     // on cache les labels de résultats
     ui->lRangRep->clear();
     ui->lCategorieRep->clear();
     ui->lTitreRep->clear();
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;
}

void LecteurVue::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if ((*this)._numDiaporamaCourant!=0)
    {
        cout << "Numero du diaporama : " << (*this)._numDiaporamaCourant << endl;
        if (nbImages()==0)
        {
            cout << "diaporama vide";
        }
        else
        {
            Image* imageCourante = this->imageCourante();
            this->afficherRang(imageCourante);
            this->afficherCategorie(imageCourante);
            this->afficherTitre(imageCourante);
            this->afficherImage(imageCourante);
        }
    }
    else
    {
        cout << "lecteur vide" << endl;
    }
}

unsigned int LecteurVue::nbImages()
{
    return _diaporama.size();
}

Image *LecteurVue::imageCourante()
{

    return _diaporama[_posImageCourante];
    // return _diaporama_posImageCourante
}

unsigned int LecteurVue::numDiaporamaCourant()
{
    return (*this)._numDiaporamaCourant;
}

void LecteurVue::afficherRang(Image* imageCourante)
{
    int rang = imageCourante->getRang();
    ui->lRangRep->setNum(rang);
}

void LecteurVue::afficherTitre(Image* imageCourante)
{
    QString titre = QString::fromStdString(imageCourante->getTitre());
    ui->lTitreRep->setText(titre);
}

void LecteurVue::afficherCategorie(Image* imageCourante)
{
    QString categorie = QString::fromStdString(imageCourante->getCategorie());
    ui->lCategorieRep->setText(categorie);
}

void LecteurVue::afficherImage(Image* imageCourante)
{
    QString chemin = QString::fromStdString(imageCourante->getChemin());
    QImage cheminImage (chemin);
    ui->lImage->setPixmap(QPixmap::fromImage(cheminImage));
    ui->lImage->show();

}
