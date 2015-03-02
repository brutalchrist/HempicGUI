#include "hempicgui.h"
#include "cambiarfecha.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HempicGUI w;
    w.show();

    return a.exec();
}
