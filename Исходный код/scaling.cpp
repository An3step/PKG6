#include "scaling.h"
#include "ui_scaling.h"

Scaling::Scaling(bool& Scale, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scaling), isScale(Scale)
{
    ui->setupUi(this);
    ui->doubleSpinBox->setRange(0.01, 4);
    ui->doubleSpinBox_2->setRange(0.01, 4);
    ui->doubleSpinBox_3->setRange(0.01, 4);
    ui->doubleSpinBox->setValue(1);
    ui->doubleSpinBox_2->setValue(1);
    ui->doubleSpinBox_3->setValue(1);
    ui->doubleSpinBox->setSingleStep(0.1);
    ui->doubleSpinBox_2->setSingleStep(0.1);
    ui->doubleSpinBox_3->setSingleStep(0.1);
}

Scaling::~Scaling()
{
    delete ui;
}

void Scaling::on_doubleSpinBox_valueChanged(double arg1)
{
    emit xChange(arg1);
}

void Scaling::on_doubleSpinBox_2_valueChanged(double arg1)
{
    emit yChange(arg1);
}

void Scaling::on_doubleSpinBox_3_valueChanged(double arg1)
{
    emit zChange(arg1);
}

void Scaling::closeEvent(QCloseEvent *event)
{
    isScale = false;
    QWidget::closeEvent(event);
}
