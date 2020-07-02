#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

#include "producto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

public slots:
    void mostrarPrecio(int);
    void agregarProducto();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;

    void inicializarDatos();
    void inicializarWidgets();
    float m_subtotal;

    void calcular(float subtotal);

};
#endif // PRINCIPAL_H
