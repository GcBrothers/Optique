/*****************************
            OPTIQUE
              v0.6

    (d'après une idée de K)

******************************/

#include "lentille.h"

Lentille::Lentille(double focale, double x)
{
    m_focale = new double;
    m_x = new double;

    *m_focale = focale;
    *m_x = x;
}

void Lentille::afficherInfo()
{
    std::cout << "Position : x = " << *m_x << std::endl;
    std::cout << "Focale : f' = " << *m_focale << std::endl;
}

double Lentille::retournePos()
{
    return *m_x;
}

double Lentille::retourneFocale()
{
    return *m_focale;
}
