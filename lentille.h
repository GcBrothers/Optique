/*****************************
            OPTIQUE
              v0.6

    (d'après une idée de K)

******************************/

#ifndef LENTILLE_H
#define LENTILLE_H

#include <iostream>

class Lentille
{
public:
    Lentille(double focale = 0.25, double x = 1);
    void afficherInfo();
    double retournePos();
    double retourneFocale();

private:
    double *m_focale;
    double *m_x;
};

#endif // LENTILLE_H
