#include "rotating.h"
#include "ui_rotating.h"

Rotating::Rotating(bool& Rotate,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rotating), isRotate(Rotate)
{
    ui->setupUi(this);
    ui->rotating_x->setRange(-180, 180);
    ui->roating_y->setRange(-180, 180);
    ui->rotating_z->setRange(-180 ,180);
}

Rotating::~Rotating()
{
    delete ui;
}

void Rotating::closeEvent(QCloseEvent *event)
{
    isRotate = false;
    QWidget::closeEvent(event);
}

void Rotating::on_rotating_x_valueChanged(int arg1)
{
    emit x_AngleChange(arg1);
}

void Rotating::on_roating_y_valueChanged(int arg1)
{
    emit y_AngleChange(arg1);
}

void Rotating::on_rotating_z_valueChanged(int arg1)
{
    emit z_AngleChange(arg1);
}
