#include "ventanaprincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
    w.setWindowTitle("Banco de Pruebas Jorge Curbera");
    w.show();

    return a.exec();
}
