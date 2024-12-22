#include "transferring.h"
#include "ui_transferring.h"

Transferring::Transferring(bool& Trans, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Transferring), isTransfer(Trans)
{
    ui->setupUi(this);
    ui->Transferring_x->setRange(-10, 10);
    ui->transferring_y->setRange(-10, 10);
    ui->spinBox_3->setRange(-10, 10);
}

Transferring::~Transferring()
{
    delete ui;
}

void Transferring::closeEvent(QCloseEvent * e)
{
    isTransfer = false;
    QWidget::closeEvent(e);
}

void Transferring::on_Transferring_x_valueChanged(int arg1)
{
    emit xTransfer(arg1);
}

void Transferring::on_transferring_y_valueChanged(int arg1)
{
    emit yTransfer(arg1);
}

void Transferring::on_spinBox_3_valueChanged(int arg1)
{
    emit zTransfer(arg1);
}
