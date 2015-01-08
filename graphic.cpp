/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/

#include "graphic.h"
#include "math.h"

Graphic::Graphic()
{
    /* ----------------------- Déclaration des pointeurs ---------------------*/
    m_scene = new QGraphicsScene;
    m_lenses = new QVector<Lentille>;
    m_rayons = new QVector<Rayon>;

    double f1 = 0.250;
    double f2 = 0.125;
    double x0 = 0.200;

    m_scene->setBackgroundBrush(Qt::black);
    /* ------------------- Ajout des lentilles "de base" ---------------------*/
    /* /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\
     Si vous modifiez ces lentilles, veillez à les rentrer TRIEES par POSITIONS
     CROISSANTES
       /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\ /!\*/
    m_lenses->push_back(Lentille(f1,x0));
    m_lenses->push_back(Lentille(f2,x0 + f1 + f2));
    m_lenses->push_back(Lentille(f2,x0 + f1 + f2 + 2*f2*(f1+f2)/(f1-f2)));
    m_lenses->push_back(Lentille(f1,x0 + f1 + f2 + 2*f2*(f1+f2)/(f1-f2) + f1+f2));


    /* ------------------- Ajout des rayons "de base" ------------------------*/

    m_rayons->push_back(Rayon(0,0.1));
    m_rayons->push_back(Rayon(0,0.2));

    /* ------------------- Affichage des axes --------------------------------*/

    this->dessinerAxes();

    /* -------------------  Affichage des lentilles  -------------------------*/
    this->dessinerLentilles();

    /* ------------------   Affichage des rayons -----------------------------*/
    this->dessinerSchema();

    this->setScene(m_scene);
    this->centerOn(0,0);
}

void Graphic::dessinerAxes()
{
    //Stylos !
    QPen vertAxe;
    vertAxe.setWidth(3);
    vertAxe.setColor(Qt::green);

    Lentille *temp = m_lenses->data();
    double longueur = 200 + 1000 * temp[m_lenses->size()-1].retournePos();
    m_scene->addLine(0,0,0,400,vertAxe);
    m_scene->addLine(0,0,longueur,0,vertAxe);
}

void Graphic::dessinerLentilles()
{
    Lentille *temp = m_lenses->data();
    int i = 0;

    //std::cout << "size = " << m_lenses->size() << "," << temp[1].retournePos() << std::endl;
    QPen pen;
    QBrush bru;
    bru.setStyle(Qt::CrossPattern);
    pen.setBrush(bru);
    pen.setColor(Qt::darkBlue);
    pen.setWidth(10);
    for(i=0;i<m_lenses->size();i++)
    {
        //std::cout << "size = " << m_lenses->size() << "," << temp[i].retournePos() << std::endl;
        m_scene->addLine(1000*temp[i].retournePos(),-200,1000*temp[i].retournePos(),+200,pen);
    }
}

void Graphic::dessinerSchema()
{
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);

    Rayon *tempR = m_rayons->data();
    Lentille *tempL = m_lenses->data();
    int a = m_rayons->size();
    int b = m_lenses->size();
    int i = 0;
    int k = 0;
    double m,p;

    Rayon r = Rayon(0,0);
    Lentille l = Lentille(1,0);

    for(i = 0; i < a; i++)
    {
        r = tempR[i];


        for(k = 0; k < b ; k++)
        {
            m = r.retourneCoef();
            p = r.retourneOrdo();
            l = tempL[k];
            if(k==0)
            {
                m_scene->addLine(0,r.retourneOrdo()*1000,l.retournePos()*1000,m*l.retournePos()*1000+p*1000, pen);
            }
            else
            {
                double pos0 = tempL[k-1].retournePos();
                double pos1 = tempL[k].retournePos();
                //std::cout << "On est ici, pos0 = "  << pos0 << " pos1 = " << pos1 << std::endl;
                m_scene->addLine(pos0*1000,m*pos0*1000 + p*1000, pos1*1000, m*pos1*1000 + p*1000, pen);
            }

            double nveauCoef = (-(m*(l.retournePos()-l.retourneFocale()) + p))/l.retourneFocale();
            //r = Rayon(nveauCoef*45, m*l.retournePos() + p - nveauCoef*l.retournePos());
	    r = Rayon(atan(nveauCoef)*180/3.1415926535897932, m*l.retournePos() + p - nveauCoef*l.retournePos());
        }
        m = r.retourneCoef();
        p = r.retourneOrdo();
        m_scene->addLine(l.retournePos()*1000, m*l.retournePos()*1000 + p*1000, l.retournePos()*1000 + 200, m*(l.retournePos()*1000+200) + p*1000, pen);
    }
}

int Graphic::nbreLentilles()
{
    return m_lenses->size();
}

int Graphic::nbreRayons()
{
    return m_rayons->size();
}

double Graphic::rtrnFocale(int indiceLentille)
{
    if(indiceLentille >= 0 && indiceLentille < m_lenses->size())
    {
        Lentille *temp = m_lenses->data();
        return temp[indiceLentille].retourneFocale();
    }
    else
    {
        return 1;
    }
}

double Graphic::rtrnPosition(int indiceLentille)
{
    if(indiceLentille >= 0 && indiceLentille < m_lenses->size())
    {
        Lentille *temp = m_lenses->data();
        return temp[indiceLentille].retournePos();
    }
    else
    {
        return -1;
    }
}

double Graphic::rtrnAngle(int indiceRayon)
{
    if(indiceRayon >= 0 && indiceRayon < m_rayons->size())
    {
        Rayon *temp = m_rayons->data();
        //return temp[indiceRayon].retourneCoef()*45;
	return atan(temp[indiceRayon].retourneCoef())*180/3.14159265358979323;
    }
    else
    {
        return 0;
    }
}

double Graphic::rtrnOrdo(int indiceRayon)
{
    if(indiceRayon >= 0 && indiceRayon < m_rayons->size())
    {
        Rayon *temp = m_rayons->data();
        return temp[indiceRayon].retourneOrdo();
    }
    else
    {
        return 0;
    }
}

void Graphic::ajouterLentille(double focale, double position)
{
    Lentille *temp = m_lenses->data();
    int i = 0;
    while (position > temp[i].retournePos() && i < m_lenses->size()) //Ajouter la lentille au bon endroit pour que ça soit trié
    {
        i++;
    }
    m_lenses->insert(i, Lentille(focale, position));

    //on efface...
    m_scene->clear();
    //... et on redessine tout !
    this->dessinerAxes();
    this->dessinerLentilles();
    this->dessinerSchema();
}

void Graphic::changerLentille(int ind, double foc, double pos)
{
    if(ind >= 0 && ind < m_lenses->size())
    {
        m_lenses->remove(ind);
        Lentille *temp = m_lenses->data();
        int i = 0;
        while (pos > temp[i].retournePos() && i < m_lenses->size())
        {
            i++;
        }
        m_lenses->insert(i, Lentille(foc, pos));

        //on efface...
        m_scene->clear();
        //... et on redessine tout !
        this->dessinerAxes();
        this->dessinerLentilles();
        this->dessinerSchema();
    }
}

void Graphic::supprimerLentille(int ind)
{
    if(ind >= 0 && ind < m_lenses->size())
    {
        m_lenses->remove(ind);
        //on efface...
        m_scene->clear();
        //... et on redessine tout !
        this->dessinerAxes();
        this->dessinerLentilles();
        this->dessinerSchema();
    }
}

void Graphic::ajouterRayon(double angle, double ord)
{
    m_rayons->push_front(Rayon(angle, ord));
    //... et on redessine tout !
    this->dessinerSchema();
}

void Graphic::changerRayon(int ind, double ang, double ord)
{
    Rayon *temp = m_rayons->data();
    temp[ind] = Rayon(ang,ord);
    //on efface...
    m_scene->clear();
    //... et on redessine tout !
    this->dessinerAxes();
    this->dessinerLentilles();
    this->dessinerSchema();
}

void Graphic::supprimerRayon(int ind)
{
    m_rayons->remove(ind);
    //on efface...
    m_scene->clear();
    //... et on redessine tout !
    this->dessinerAxes();
    this->dessinerLentilles();
    this->dessinerSchema();
}

/* Première fonction, à refaire */
/*void Graphic::dessinerSchema(int densB, int densA, int ecartB, int ecartA, qreal a0)
{
    int a = -(ecartA*densA);
    int b = -(ecartB*densB);

    long double a1 = a/1000;
    long double b1 = b/1000;
    long double b2,a2;
    Lentille last;
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(255,0,0));

    Lentille *l = m_lenses->data();
    for(a= -(ecartA*densA); a<(densA+1)*ecartA; a += ecartA)
    {
        for(b=-(ecartB*densB); b<(densB+1)*ecartB;b += ecartB)
        {
            std::cout << "b = " << b << std::endl;
            last = Lentille(1,0);
            a1 = a/1e3;
            b1 = b/1e3;

            int i = 0;
            for(i=0;i<m_lenses->size();i++)
            {
                std::cout << i << std::endl;
                b2 = a1 * (l[i].retournePos() - last.retournePos()) + b1;
                a2 = a1-(b2/l[i].retourneFocale());

                std::cout << "Coordonnées : " << 1000*last.retournePos() << ", " << a0 - 1000*b1 << ", " << 1000*l[i].retournePos() << "," << a0-1000*b2 << std::endl;
                //std::cout << "1/1000 = " << b1 << std::endl;

                m_scene->addLine(1000*last.retournePos(),a0 - 1000*b1,1000*l[i].retournePos(),a0-1000*b2, pen);
                //m_scene->addLine(1000*last.retournePos(),a0 - 1000*b1,10,10);
                last = l[i];
                a1 = a2;
                b1 = b2;
            }
            b2 = a1*(0.1)+ b1;
            //double a2 = a1- b2/l[m_lenses->size() - 1].retourneFocale();
            std::cout << last.retournePos() + 0.1 << std::endl;
            m_scene->addLine(1000*last.retournePos(),a0 - 1000*b1,1000*(last.retournePos()+0.1),a0-1000*b2, pen);
        }
    }
    //std::cout << "Ici" << std::endl;
}
*/
