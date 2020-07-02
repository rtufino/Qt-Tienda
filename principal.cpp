#include "principal.h"
#include "ui_principal.h"

#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    inicializarDatos();
    m_subtotal = 0;
}

Principal::~Principal()
{
    delete ui;
}

void Principal::mostrarPrecio(int index)
{
    // Obtener el precio del producto seleccionado
    float precio = m_productos.at(index)->precio();

    // Colacar el precio en la etiqueta correspondiente
    ui->outPrecio->setText("$ " + QString::number(precio));
}

void Principal::agregarProducto()
{
    // Obteniendo datos desde la interfaz
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);
    int cantidad = ui->inCantidad->value();

    // Calcular subtotal
    float subtotal = cantidad * p->precio();

    // Agregar datos a la tabla
    int posicion = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(posicion);
    ui->outDetalle->setItem(posicion,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(posicion,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(posicion,2,new QTableWidgetItem(QString::number(subtotal)));

    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Calcular valores y mostrar
    calcular(subtotal);

}

void Principal::inicializarDatos()
{
    // Crear y agregar productos a la lista
    m_productos.append(new Producto(1,"Leche",0.75));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.50));

    // Invocar al metodo para inicializar los widgets
    inicializarWidgets();
}

void Principal::inicializarWidgets()
{
    // Agregar nombre de los productos al combo box
    for (int i = 0; i < m_productos.length(); ++i) {
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }

    // Colocar cabecera en la tabla
    QStringList cabecera = {"Cantidad", "Producto", "Sub Total"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);

    // Eventos
    connect(ui->inProducto, SIGNAL(currentIndexChanged(int)), this, SLOT(mostrarPrecio(int)));
    connect(ui->cmdAgregar, SIGNAL(clicked(bool)), this, SLOT(agregarProducto()));

    // Mostrar el precio del primer producto
    mostrarPrecio(0);
}

void Principal::calcular(float subtotal)
{
    m_subtotal += subtotal;
    float iva = m_subtotal * 0.12;
    float total = m_subtotal + iva;

    ui->outSubtotal->setText(QString::number(m_subtotal));
    ui->outIva->setText(QString::number(iva));
    ui->outTotal->setText(QString::number(total));
}

