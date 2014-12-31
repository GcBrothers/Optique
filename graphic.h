/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QVector>
#include <QLineF>
#include "lentille.h"
#include "rayon.h"

class Graphic : public QGraphicsView
{
    Q_OBJECT
public:
    Graphic();
    void dessinerAxes();
    void dessinerLentilles();
    void dessinerSchema();

    int nbreLentilles();
    int nbreRayons();

    double rtrnFocale(int indiceLentille);
    double rtrnPosition(int indiceLentille);
    double rtrnAngle(int indiceRayon);
    double rtrnOrdo(int indiceRayon);
    //~Graphic();
    void ajouterLentille(double focale, double position);
    void changerLentille(int ind, double foc, double pos);
    void supprimerLentille(int ind);

    void ajouterRayon(double angle, double ord);
    void changerRayon(int ind, double ang, double ord);
    void supprimerRayon(int ind);
    
signals:
    
public slots:

private:
    QGraphicsScene *m_scene;
    QVector<Lentille> *m_lenses;
    QVector<Rayon> *m_rayons;
    
};

#endif // GRAPHIC_H
