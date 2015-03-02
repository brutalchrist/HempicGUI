#ifndef CAMBIARFECHA_H
#define CAMBIARFECHA_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class CambiarFecha;
}

class CambiarFecha : public QDialog
{
    Q_OBJECT

public:
    explicit CambiarFecha(QWidget *parent = 0);
    ~CambiarFecha();
    QDateTime fecha;

public slots:
    QDateTime getFecha();
    void setFecha(QDateTime fechaCambiar);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CambiarFecha *ui;
};

#endif // CAMBIARFECHA_H
