//*********************************************************************************************
//* Programme : main.cpp
//* Date : 21/11/2023
//* Dernière mise à jour : 21/11/2023
//*
//* Programmeurs : Lopes-Pereira Damien :) / Hurtel Joris / Sénépart Mathias :)
//* Classe : BTSSN2
//*--------------------------------------------------------------------------------------------------------
//* BUT : Point d'entrée de l'application. Crée et affiche la fenêtre principale.
//* Programmes associés : QtWidgetsApplication1
//*********************************************************************************************

#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
 
    QApplication a(argc, argv);

    QtWidgetsApplication1 w;

    w.show();

    return a.exec();
}
