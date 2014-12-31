/*****************************
            OPTIQUE
              v1.0

    (d'après une idée de K)

******************************/


#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include "fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Fenetre fenetre;
    fenetre.show();
    return app.exec();
}

