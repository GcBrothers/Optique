/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#ifndef FENETRE_H
#define FENETRE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "graphic.h"

class Fenetre : public QWidget
{
    Q_OBJECT
public:
    Fenetre();
    void majLentilles();
    void majRayons();

public slots:
    void majInfosLentille(int indiceComboBox);
    void ajLentille();
    void modLentille();
    void suppLentille();

    void majInfosRayon(int indiceComboBox);
    void ajRayon();
    void modRayon();
    void suppRayon();
    
private:
    Graphic *m_graph;
    QHBoxLayout *m_hBox;

    //Partie Gestion des Lentilles
    QVBoxLayout *m_lensCtrl;
    QComboBox *m_lensList;
    QLabel *m_labFoc;
    QLabel *m_labPos;
    QLineEdit *m_focale;
    QLineEdit *m_position;
    QHBoxLayout *m_btnsLentille;
    QPushButton *m_ajouterLentille;
    QPushButton *m_changerLentille;
    QPushButton *m_supprimerLentille;

    //Partie Gestion des rayons
    QVBoxLayout *m_rayonsCtrl;
    QComboBox *m_rayonsList;
    QLabel *m_labAngle;
    QLabel *m_labOrdo;
    QLineEdit *m_angle;
    QLineEdit *m_ordo;
    QHBoxLayout *m_btnsRayons;
    QPushButton *m_ajouterRayon;
    QPushButton *m_changerRayon;
    QPushButton *m_supprimerRayon;
    
};

#endif // FENETRE_H
