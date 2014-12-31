/*****************************
            OPTIQUE
              v0.6

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

public slots:
    void majInfosLentille(int indiceComboBox);
    void modLentille();
    
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
    QPushButton *m_changerLentille;
    
};

#endif // FENETRE_H
