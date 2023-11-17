#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FOUR.h"

class FOUR : public QMainWindow
{
    Q_OBJECT

public:
    FOUR(QWidget *parent = nullptr);
    ~FOUR();

private:
    Ui::FOURClass ui;
};
