//*********************************************************************************************
//* Programme : main.cpp
//* Date : 21/11/2023
//* Derni�re mise � jour : 21/11/2023
//*
//* Programmeurs : Lopes-Pereira Damien :) / Hurtel Joris / S�n�part Mathias :)
//* Classe : BTSSN2
//*--------------------------------------------------------------------------------------------------------
//* BUT : Point d'entr�e de l'application. Cr�e et affiche la fen�tre principale.
//* Programmes associ�s : QtWidgetsApplication1
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
