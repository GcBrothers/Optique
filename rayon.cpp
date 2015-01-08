/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#include "rayon.h"
#include "math.h"

Rayon::Rayon(double angle, double ordo)
{
    //Attention l'axe des abcisses est orienté VERS LE BAS
    m_angle = new double; //EN DEGRES
    m_ordoALOrigine = new double;
    pi = 3.14159265358979323;

    *m_angle = angle;
    *m_ordoALOrigine = ordo;
}

double Rayon::retourneCoef() // Retourne le coefficient équivalent
{
    //std::cout << "La valeur du coef est : " << tan(*m_angle * pi / 180) << std::endl;
    //return *m_angle/45;
    return tan(*m_angle * pi / 180);
}

double Rayon::retourneOrdo()
{
    return *m_ordoALOrigine;
}
