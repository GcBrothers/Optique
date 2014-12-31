/*****************************
            OPTIQUE
              v0.6

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
    //~Graphic();
    void changerLentille(int ind, double foc, double pos);
    
signals:
    
public slots:

private:
    QGraphicsScene *m_scene;
    QVector<Lentille> *m_lenses;
    QVector<Rayon> *m_rayons;
    
};

#endif // GRAPHIC_H
