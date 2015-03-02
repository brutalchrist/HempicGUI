#ifndef CAMBIARFECHA_H
#define CAMBIARFECHA_H

#include <QDialog>

namespace Ui {
class CambiarFecha;
}

class CambiarFecha : public QDialog
{
    Q_OBJECT

public:
    explicit CambiarFecha(QWidget *parent = 0);
    ~CambiarFecha();

private:
    Ui::CambiarFecha *ui;
};

#endif // CAMBIARFECHA_H
