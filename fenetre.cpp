/*****************************
            OPTIQUE
              v0.6

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
    m_changerLentille = new QPushButton;

    /* ----------------------- Initialisation des Labels ---------------------*/

    m_labFoc->setText("Focale = ");
    m_labPos->setText("Position = ");

    /* -------------------- Initialisation de la ComboBox --------------------*/
    int i = 0;
    for(i=0;i<m_graph->nbreLentilles();i++)
    {
        m_lensList->addItem("Lentille " + QString::number(i+1));
    }

    /* ---------------------- Initialisation des LineEdit --------------------*/

    m_focale->setText(QString::number(m_graph->rtrnFocale(0)));
    m_position->setText(QString::number(m_graph->rtrnPosition(0)));

    /* ---------------------- Initialisation des LineEdit --------------------*/

    m_changerLentille->setText("Changer !");

    /* ----------------------- Mise au point des Layouts ---------------------*/
    m_lensCtrl->addWidget(m_lensList);
    m_lensCtrl->addWidget(m_labFoc);
    m_lensCtrl->addWidget(m_focale);
    m_lensCtrl->addWidget(m_labPos);
    m_lensCtrl->addWidget(m_position);
    m_lensCtrl->addWidget(m_changerLentille);

    m_hBox->addWidget(m_graph);
    m_hBox->addLayout(m_lensCtrl);

    this->setLayout(m_hBox);

    QObject::connect(m_lensList, SIGNAL(currentIndexChanged(int)), this, SLOT(majInfosLentille(int)));
    QObject::connect(m_changerLentille, SIGNAL(clicked()), this, SLOT(modLentille()));
}

void Fenetre::majInfosLentille(int indiceComboBox)
{
    m_focale->setText(QString::number(m_graph->rtrnFocale(indiceComboBox)));
    m_position->setText(QString::number(m_graph->rtrnPosition(indiceComboBox)));
}

void Fenetre::modLentille()
{
    m_graph->changerLentille(m_lensList->currentIndex(), m_focale->text().toDouble(),m_position->text().toDouble());
}
