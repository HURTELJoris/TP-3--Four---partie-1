//*********************************************************************************************
//* Programme : QtWidgetsApplication1.cpp
//* Date : 21/11/2023
//* Derni�re mise � jour : 24/11/2023
//*
//* Programmeurs : Lopes-Pereira Damien :) / Hurtel Joris / S�n�part Mathias :)
//* Classe : BTSSN2
//*--------------------------------------------------------------------------------------------------------
//* BUT : Etre capable de piloter un four via une carte de conversion AN / NA.
//* Programmes associ�s : AUCUN
//*********************************************************************************************

#include "QtWidgetsApplication1.h"
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QSlider>

// Initialiser cardId � une valeur invalide
I16 cardId;


// Constructeur de la classe principale
QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent), tensionSlider(nullptr)
{
    ui.setupUi(this);

    // Appeler la carte au d�but
    cardId = Register_Card(PCI_9111DG, 0);
    if (cardId >= 0)
    {
        qDebug() << "Ouverture carte OK";

        AI_9111_Config(cardId, TRIG_INT_PACER, P9111_TRGMOD_SOFT, 0);

        double tension;

        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0)
            ui.labelVoltage->setText("Erreur lecture");
        else
        {
            QString tensionString = QString("Tension : %1").arg(tension);
            double temperature = (tension / 10.0) * 150.0;

            QString temperatureString = QString("Temperature : %1").arg(temperature);
            ui.labelVoltage->setText(tensionString + " V" + temperatureString + " �C");
        }

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateVoltage()));
        timer->start(600); // D�marrez le timer avec une p�riode de 600 ms

        // Connectez le signal clicked du bouton Stop � la fonction onStopButtonClicked
        connect(ui.stopButton, SIGNAL(clicked()), this, SLOT(onStopButtonClicked()));
    }
}

// Fonction pour d�finir la tension en fonction du pourcentage du slider
void QtWidgetsApplication1::setTension(int percentage)
{
    // Calcul de la tension en fonction du pourcentage
    double tension = (percentage / 100.0) * 10.2;  // La plage de tension est de 0 � 10 V
    tension = qBound(0.0, tension, 10.0); // Pour que �a ne d�passe pas 10 V
    ui.transmittedTension->setText(QString::number(tension));

    // �crire la tension sur la sortie analogique
    if (cardId >= 0)
    {
        AO_VWriteChannel(cardId, 0, tension);
    }
}

// Fonction pour mettre � jour la tension et la temp�rature affich�es
void QtWidgetsApplication1::updateVoltage()
{
    if (cardId >= 0)
    {
        double tension;

        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0)
            ui.labelVoltage->setText("Erreur lecture");
        else
        {
            QString tensionString = QString("Tension : %1").arg(tension);
            double temperature = (tension / 10.0) * 150.0;

            QString temperatureString = QString("Temperature : %1").arg(temperature);
            ui.labelVoltage->setText(tensionString + " V" + temperatureString + " �C");
        }

        // Cr�ez le slider s'il n'existe pas encore
        if (!tensionSlider)
        {
            tensionSlider = new QSlider(Qt::Horizontal, this);
            connect(tensionSlider, SIGNAL(valueChanged(int)), this, SLOT(setTension(int)));
            tensionSlider->setRange(0, 100);  // Plage de 0 � 100%
        }
    }
}

// Fonction appel�e lorsqu'on clique sur le bouton Stop
void QtWidgetsApplication1::onStopButtonClicked()
{
    // R�initialisez la valeur du slider � 0
    if (tensionSlider)
        tensionSlider->setValue(tensionSlider->minimum());
    // Appelez setTension avec 0%
    setTension(0);
}

// Destructeur de la classe
QtWidgetsApplication1::~QtWidgetsApplication1()
{
    // Lib�rer la carte � la fin
    if (cardId >= 0)
    {
        Release_Card(cardId);
    }
}
