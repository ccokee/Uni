#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsObject>

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();
private:
    Ui::VentanaPrincipal *ui;
    QImage image,imagebn;
    QGraphicsScene* scene;
    QGraphicsPixmapItem item;
    QPixmap* m;

private slots:
    void leerFichero();
    void ordenarFichero();
    void clear();
    void guardarFichero();
    void leerImagen();
    void transformarImagen();
    void guardarImagen();

};

#endif // VENTANAPRINCIPAL_H
