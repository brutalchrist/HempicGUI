#include "cambiarfecha.h"
#include "ui_cambiarfecha.h"

CambiarFecha::CambiarFecha(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CambiarFecha)
{
    ui->setupUi(this);

    /* Ventana sin resize */
    //this->statusBar()->setSizeGripEnabled(false);
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
}

CambiarFecha::~CambiarFecha()
{
    delete ui;
}

void CambiarFecha::on_buttonBox_accepted()
{
    this->fecha.setDate(ui->calendarioWidget->selectedDate());
}

void CambiarFecha::setFecha(QDateTime fechaCambiar)
{
    this->fecha = fechaCambiar;
    ui->calendarioWidget->setSelectedDate(fechaCambiar.date());
}

QDateTime CambiarFecha::getFecha()
{
    return this->fecha;
}
