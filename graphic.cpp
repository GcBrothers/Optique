/*****************************
            OPTIQUE
              v0.6

    (d'après une idée de K)

******************************/

#include "graphic.h"

Graphic::Graphic()
{
    /* ----------------------- Déclaration des pointeurs ---------------------*/
    m_scene = new QGraphicsScene;
    m_lenses = new QVector<Lentille>;
    m_rayons = new QVector<Rayon>;

    double f1 = 0.250;
    double f2 = 0.125;
    double x0 = 0.200;

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

    m_scene->addLine(0,0,0,400,vertAxe);
    m_scene->addLine(0,0,2000,0,vertAxe);
}

void Graphic::dessinerLentilles()
{
    Lentille *temp = m_lenses->data();
    int i = 0;

    //std::cout << "size = " << m_lenses->size() << "," << temp[1].retournePos() << std::endl;
    QPen pen;
    QBrush bru;
    QColor col;
    bru.setStyle(Qt::CrossPattern);
    pen.setBrush(bru);
    col.setBlue(90);
    col.setRed(5);
    col.setGreen(5);
    pen.setColor(col);
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
    pen.setWidth(4);

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
            r = Rayon(nveauCoef*45, m*l.retournePos() + p - nveauCoef*l.retournePos());
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
        return -1;
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

void Graphic::changerLentille(int ind, double foc, double pos)
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
