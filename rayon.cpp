/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#include "rayon.h"

Rayon::Rayon(double angle, double ordo)
{
    //Attention l'axe des abcisses est orienté VERS LE BAS
    m_angle = new double; //EN DEGRES
    m_ordoALOrigine = new double;

    *m_angle = angle;
    *m_ordoALOrigine = ordo;
}

double Rayon::retourneCoef() // Retourne le coefficient équivalent
{
    return *m_angle/45;
}

double Rayon::retourneOrdo()
{
    return *m_ordoALOrigine;
}
