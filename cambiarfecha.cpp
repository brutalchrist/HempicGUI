#include "cambiarfecha.h"
#include "ui_cambiarfecha.h"

CambiarFecha::CambiarFecha(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CambiarFecha)
{
    ui->setupUi(this);
}

CambiarFecha::~CambiarFecha()
{
    delete ui;
}
