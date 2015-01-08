/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#include "fenetre.h"

Fenetre::Fenetre()
{
    /* ----------------------- Déclaration des pointeurs ---------------------*/
    m_graph = new Graphic;
    m_hBox = new QHBoxLayout;

    m_lensCtrl = new QVBoxLayout;
    m_lensList = new QComboBox;
    m_labFoc = new QLabel;
    m_labPos = new QLabel;
    m_focale = new QLineEdit;
    m_position = new QLineEdit;
    m_btnsLentille = new QHBoxLayout;
    m_ajouterLentille = new QPushButton;
    m_changerLentille = new QPushButton;
    m_supprimerLentille = new QPushButton;

    m_rayonsCtrl = new QVBoxLayout;
    m_rayonsList = new QComboBox;
    m_labAngle = new QLabel;
    m_labOrdo = new QLabel;
    m_angle = new QLineEdit;
    m_ordo = new QLineEdit;
    m_btnsRayons = new QHBoxLayout;
    m_ajouterRayon = new QPushButton;
    m_changerRayon = new QPushButton;
    m_supprimerRayon = new QPushButton;

    /* ----------------------- Initialisation des Labels --------------------- */

    m_labFoc->setText("Focale = ");
    m_labPos->setText("Position = ");
    m_labAngle->setText("Angle = ");
    m_labOrdo->setText("Ordonnée à l'origine = ");

    /* -------------------- Initialisation de la ComboBox -------------------- */
    int i = 0;
    for(i=0;i<m_graph->nbreLentilles();i++)
    {
        m_lensList->addItem("Lentille " + QString::number(i+1));
    }
    i = 0;
    for(i=0;i<m_graph->nbreRayons();i++)
    {
        m_rayonsList->addItem("Rayon " + QString::number(i+1));
    }

    /* ---------------------- Initialisation des LineEdit -------------------- */

    m_focale->setText(QString::number(m_graph->rtrnFocale(0)));
    m_position->setText(QString::number(m_graph->rtrnPosition(0)));
    m_angle->setText(QString::number(m_graph->rtrnAngle(0)));
    m_ordo->setText(QString::number(m_graph->rtrnOrdo(0)));

    /* ----------------------- Initialisation des Boutons -------------------- */

    m_ajouterLentille->setText("Ajouter !");
    m_changerLentille->setText("Changer !");
    m_supprimerLentille->setText("Supprimer !");
    m_ajouterRayon->setText("Ajouter !");
    m_changerRayon->setText("Changer !");
    m_supprimerRayon->setText("Supprimer !");

    /* ----------------------- Mise au point des Layouts --------------------- */
    m_lensCtrl->addStretch(1);
    m_lensCtrl->addWidget(m_lensList);
    m_lensCtrl->addWidget(m_labFoc);
    m_lensCtrl->addWidget(m_focale);
    m_lensCtrl->addWidget(m_labPos);
    m_lensCtrl->addWidget(m_position);

    m_btnsLentille->addWidget(m_ajouterLentille);
    m_btnsLentille->addWidget(m_changerLentille);
    m_btnsLentille->addWidget(m_supprimerLentille);
    m_lensCtrl->addLayout(m_btnsLentille);
    m_lensCtrl->addStretch(1);

    m_rayonsCtrl->addStretch(1);
    m_rayonsCtrl->addWidget(m_rayonsList);
    m_rayonsCtrl->addWidget(m_labAngle);
    m_rayonsCtrl->addWidget(m_angle);
    m_rayonsCtrl->addWidget(m_labOrdo);
    m_rayonsCtrl->addWidget(m_ordo);

    m_btnsRayons->addWidget(m_ajouterRayon);
    m_btnsRayons->addWidget(m_changerRayon);
    m_btnsRayons->addWidget(m_supprimerRayon);
    m_rayonsCtrl->addLayout(m_btnsRayons);
    m_rayonsCtrl->addStretch(1);

    m_hBox->addWidget(m_graph);
    m_hBox->addLayout(m_lensCtrl);
    m_hBox->addLayout(m_rayonsCtrl);

    this->setLayout(m_hBox);

    /* ------ Connection des différents boutons à leur comportment ----------- */

    QObject::connect(m_lensList, SIGNAL(currentIndexChanged(int)), this, SLOT(majInfosLentille(int)));
    QObject::connect(m_ajouterLentille, SIGNAL(clicked()), this, SLOT(ajLentille()));
    QObject::connect(m_changerLentille, SIGNAL(clicked()), this, SLOT(modLentille()));
    QObject::connect(m_supprimerLentille, SIGNAL(clicked()), this, SLOT(suppLentille()));
    QObject::connect(m_rayonsList, SIGNAL(currentIndexChanged(int)), this, SLOT(majInfosRayon(int)));
    QObject::connect(m_ajouterRayon, SIGNAL(clicked()), this, SLOT(ajRayon()));
    QObject::connect(m_changerRayon, SIGNAL(clicked()), this, SLOT(modRayon()));
    QObject::connect(m_supprimerRayon, SIGNAL(clicked()), this, SLOT(suppRayon()));
}

void Fenetre::majLentilles()
{
    m_lensList->clear();
    int i = 0;
    for(i=0;i<m_graph->nbreLentilles();i++)
    {
        m_lensList->addItem("Lentille " + QString::number(i+1));
    }

}
void Fenetre::majRayons()
{
    m_rayonsList->clear();
    int i = 0;
    for(i=0;i<m_graph->nbreRayons();i++)
    {
        m_rayonsList->addItem("Rayon " + QString::number(i+1));
    }

}

void Fenetre::majInfosLentille(int indiceComboBox)
{
    m_focale->setText(QString::number(m_graph->rtrnFocale(indiceComboBox)));
    m_position->setText(QString::number(m_graph->rtrnPosition(indiceComboBox)));
}

void Fenetre::ajLentille()
{
    m_graph->ajouterLentille(m_focale->text().toDouble(),m_position->text().toDouble());
    this->majLentilles();
}

void Fenetre::modLentille()
{
    m_graph->changerLentille(m_lensList->currentIndex(), m_focale->text().toDouble(),m_position->text().toDouble());
}

void Fenetre::suppLentille()
{
    m_graph->supprimerLentille(m_lensList->currentIndex());
    this->majLentilles();
}

void Fenetre::majInfosRayon(int indiceComboBox)
{
    m_angle->setText(QString::number(m_graph->rtrnAngle(indiceComboBox)));
    m_ordo->setText(QString::number(m_graph->rtrnOrdo(indiceComboBox)));
}

void Fenetre::ajRayon()
{
    m_graph->ajouterRayon(m_angle->text().toDouble(), m_ordo->text().toDouble());
    this->majRayons();
}
void Fenetre::modRayon()
{
    m_graph->changerRayon(m_rayonsList->currentIndex(), m_angle->text().toDouble(), m_ordo->text().toDouble());
    this->majRayons();
}
void Fenetre::suppRayon()
{
    m_graph->supprimerRayon(m_rayonsList->currentIndex());
    this->majRayons();
}
