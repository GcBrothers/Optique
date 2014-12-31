/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#ifndef RAYON_H
#define RAYON_H

class Rayon
{
public:
    Rayon(double angle = 0 , double ordo = 0);
    double retourneCoef();
    double retourneOrdo();
private:
    //Attention l'axe des abcisses est orienté VERS LE BAS
    double *m_angle; //EN DEGRES
    double *m_ordoALOrigine;
};

#endif // RAYON_H
