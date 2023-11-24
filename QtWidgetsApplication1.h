//*********************************************************************************************
//* Programme : QtWidgetsApplication1.h
//* Date : 21/11/2023
//* Dernière mise à jour : 24/11/2023
//*
//* Programmeurs : Lopes-Pereira Damien :) / Hurtel Joris / Sénépart Mathias :)
//* Classe : BTSSN2
//*--------------------------------------------------------------------------------------------------------
//* BUT : Déclaration de la classe QtWidgetsApplication1 pour piloter un four via une carte de conversion AN / NA.
//* Programmes associés : AUCUN
//*********************************************************************************************

#pragma once

#include <Windows.h>
#include <Dask64.h>
#include <QtWidgets/QMainWindow>
#include <QTimer> // Ajout de l'inclusion pour QTimer
#include <QSlider> // Ajout de l'inclusion pour QSlider
#include "ui_QtWidgetsApplication1.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = nullptr);
    ~QtWidgetsApplication1();

private:
    Ui::QtWidgetsApplication1Class ui;
    QTimer* timer;
    QSlider* tensionSlider; // Ajout d'un QSlider pour la gestion du pourcentage de tension
    I16 cardId;

private slots:
    void updateVoltage();
    void setTension(int percentage);
    void onStopButtonClicked();
};
