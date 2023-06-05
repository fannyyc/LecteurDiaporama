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

    _numDiaporamaCourant = 0;   // =  le lecteur est vide

    // afficher image de tapis
    QPixmap pix(CHEMIN_TAPIS);
    ui->lImage->setPixmap(pix);

    Database *db = new Database();
    db->openDataBase();

    // désactiver les boutons avant de charger un diapo
    ui->bArreterDiapo->setEnabled(false);
    ui->bLancerDiapo->setEnabled(false);
    ui->bSuivant->setEnabled(false);
    ui->bPrecedent->setEnabled(false);
    ui->aChangerVitesse->setEnabled(false);
    ui->aEnleverDiapo->setEnabled(false);

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

    monTimer=new QTimer();
    QObject::connect(monTimer, SIGNAL(timeout()), this, SLOT(suivant()));

    demarrerTimer();
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this,SLOT(arreterDiapo()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this,SLOT(arreterDiapo()));

    // réajuster les boutons
    ui->bArreterDiapo->setEnabled(true);
    ui->bLancerDiapo->setEnabled(false);
    ui->aEnleverDiapo->setEnabled(false);
    ui->aChangerVitesse->setEnabled(true);

    setEstManuel();
    ui->statusbar->showMessage("Mode : Automatique");

}

void LecteurVue::demarrerTimer()
{
    monTimer->start(_vitesse);
    ui->lRepVitesse->setNum(getVitesse() / 1000);
}

void LecteurVue::arreterDiapo()
{
    if (!_estManuel) {
        arreterTimer();
        setEstManuel();
        ui->statusbar->showMessage("Mode : Manuel");

        // réajuster les boutons
        ui->aEnleverDiapo->setEnabled(true);
        ui->bArreterDiapo->setEnabled(false);
        ui->bLancerDiapo->setEnabled(true);
        ui->aChangerVitesse->setEnabled(false);
    }
}

void LecteurVue::arreterTimer()
{
    monTimer->stop();
    ui->lRepVitesse->clear();
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

int LecteurVue::getVitesse()
{
    return _vitesse;
}

void LecteurVue::setVitesse(int vitesse)
{
    _vitesse = vitesse;
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
    if (!_estManuel)
    {
        qDebug() << "Changement de vitesse" << Qt::endl;
        arreterTimer();
        ChangerVitesse *maDlg = new ChangerVitesse(this);
        maDlg->exec();
        if (maDlg->getModif())
        {
            setVitesse (maDlg->getVitesse()*1000);
        }
        demarrerTimer();
    }

}

void LecteurVue::chargerDiapo()
{
    chargerDiaporama();
}

void LecteurVue::enleverDiapo()
{
    viderDiaporama();
    // désactiver les boutons
    ui->bArreterDiapo->setEnabled(false);
    ui->bLancerDiapo->setEnabled(false);
    ui->bSuivant->setEnabled(false);
    ui->bPrecedent->setEnabled(false);
    ui->aChangerVitesse->setEnabled(false);
    ui->aEnleverDiapo->setEnabled(false);
}

void LecteurVue::aPropos()
{

    QMessageBox *msgBoxAPropos = new QMessageBox();
    msgBoxAPropos->setStandardButtons(QMessageBox::Ok);
    msgBoxAPropos->setText("Auteurs : BEGUINEL Kévin, BERTRAND Lou & CONSTANS Fanny\nVersion v5");
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

    QSqlQuery  query;
    query.exec(" SELECT * FROM Diapos JOIN Familles ON Diapos.idFam = Familles.idFamille JOIN DiaposDansDiaporama ON Diapos.idphoto = DiaposDansDiaporama.idDiapo JOIN Diaporamas ON DiaposDansDiaporama.idDiaporama = Diaporamas.idDiaporama WHERE Diaporamas.`titre Diaporama` = 'diaporama Thierry' ");
    query.next();

    _numDiaporamaCourant = query.value(7).toInt();
    // afficher le nom du diapo
    QString nomDiapo = query.value(10).toString();
    afficherNomDiapo(nomDiapo);

    // enregistrer la vitesse de défilement du diapo choisie en seconde
    setVitesse(query.value(11).toInt()*1000);


    query.previous();

    for (int i =0; query.next(); i++)
    {
        Image* imageACharger;
        // conversion des paramètres avec le bon type
        imageACharger = new Image(query.value(8).toUInt(), query.value(5).toString().toStdString(), query.value(1).toString().toStdString(), query.value(3).toString().toStdString());
        _diaporama.push_back(imageACharger);
    }


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
    // afficher la première image
     _posImageCourante = 0;
     afficher();

     // activer les boutons sauf celui pour arreter le mode auto
     ui->bLancerDiapo->setEnabled(true);
     ui->bSuivant->setEnabled(true);
     ui->bPrecedent->setEnabled(true);
     ui->aEnleverDiapo->setEnabled(true);

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
     QPixmap pix(CHEMIN_TAPIS);
     ui->lImage->setPixmap(pix);
     ui->lImage->show();

     // on cache les labels de résultats
     ui->lRangRep->clear();
     ui->lCategorieRep->clear();
     ui->lTitreRep->clear();
     ui->lNomDiapo->clear();
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
    QString chemin = CHEMIN_PERSO + QString::fromStdString(imageCourante->getChemin());
    QImage cheminImage (chemin);
    ui->lImage->setPixmap(QPixmap::fromImage(cheminImage));
    ui->lImage->show();

}

void LecteurVue::afficherNomDiapo(QString nomDiapo)
{
    ui->lNomDiapo->setText (nomDiapo);
}
