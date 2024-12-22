#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "letter.h"
#include <QMessageBox>
#include <scaling.h>
#include <rotating.h>
#include <transferring.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    QString info = "Кнопки:\n";
    info += "w,a,s,d - вращение камеры\n";
    info += "u,b,l,r - движение камеры\n";
    QDialog qd(this);
    QVBoxLayout* qv = new QVBoxLayout(&qd);
    qv->addWidget(new QLabel(info, &qd));
    qd.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->widget->x_transfer = ui->widget->y_transfer = ui->widget->z_transfer = 0;
    ui->widget->x_scale = ui->widget->y_scale = ui->widget->z_scale = 1;
    ui->widget->x_angle = ui->widget->y_angle = ui->widget->z_angle = 0;

    ui->widget->updateGL();
}

void MainWindow::on_pushButton_10_clicked()
{

    ui->widget->colour=QColorDialog::getColor(Qt::black, this );;
}

/*virtual*/void MainWindow::keyPressEvent(QKeyEvent* pe)
{
    ui->widget->keyPressEvent(pe);
    ui->widget->updateGL();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    emit closing();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_pushButton_11_clicked()
{

    QMessageBox::information(this,"Control keys","To interact with letter you can use your mosuse or keyboard \n \n "
                                  "To zoom in press + \n \n"
                                                 "To zoom out press - \n \n"
                                                 "To rotate up press w \n \n"
                                                 "To rotate down press s \n \n"
                                                 "To rotate left press a \n \n"
                                                 "To rotate right press d \n \n"
                                                 "To translate down press z \n \n"
                                                 "To translate up press x \n \n");
}

void MainWindow::on_action_Oxy_triggered()
{
    ui->widget->xz_proection = ui->widget->yz_proection = false;
    ui->widget->xy_proection = true;
    ui->widget->updateGL();
}

void MainWindow::on_action_Oyz_triggered()
{
    ui->widget->xz_proection = ui->widget->xy_proection = false;
    ui->widget->yz_proection = true;
    ui->widget->updateGL();
}

void MainWindow::on_action_Oxz_triggered()
{
    ui->widget->xy_proection = ui->widget->yz_proection = false;
    ui->widget->xz_proection = true;
    ui->widget->updateGL();
}

void MainWindow::on_scaling_triggered()
{
    if(!isScale)
    {
        isScale = true;
        Scaling* scaling = new Scaling(isScale);
        connect(this, &MainWindow::closing, scaling, &Scaling::close);
        connect(scaling, &Scaling::xChange, this, &MainWindow::changing_x);
        connect(scaling, &Scaling::yChange, this, &MainWindow::changing_y);
        connect(scaling, &Scaling::zChange, this, &MainWindow::changing_z);
        scaling->resize(200, 200);
        scaling->show();
        scaling->move(150, 150);
        scaling->setWindowTitle("МАсштабирование");
    }
}

void MainWindow::on_rotating_triggered()
{
    if(!isRotate)
    {
        isRotate = true;
        Rotating* rotating = new Rotating(isRotate);
        connect(this, &MainWindow::closing, rotating, &Rotating::close);
        connect(rotating, &Rotating::x_AngleChange, this, &MainWindow::changing_x_Angle);
        connect(rotating, &Rotating::y_AngleChange, this, &MainWindow::changing_y_Angle);
        connect(rotating, &Rotating::z_AngleChange, this, &MainWindow::changing_z_Angle);
        rotating->resize(200, 200);
        rotating->move(1000, 150);
        rotating->show();
        rotating->setWindowTitle("Поворот");
    }
}

void MainWindow::on_transfering_triggered()
{
    if(!isTransfer)
    {
        isTransfer = true;
        Transferring* transferring = new Transferring(isTransfer);
        connect(this, &MainWindow::closing, transferring, &Transferring::close);
        connect(transferring, &Transferring::xTransfer, this, &MainWindow::x_Transfer);
        connect(transferring, &Transferring::yTransfer, this, &MainWindow::y_Transfer);
        connect(transferring, &Transferring::zTransfer, this, &MainWindow::z_Transfer);
        transferring->resize(200, 200);
        transferring->move(100, 100);
        transferring->show();
        transferring->setWindowTitle("Перемещение");
    }
}

void MainWindow::changing_z(double z)
{
    ui->widget->z_scale = z;
    qDebug() << "signal emitted";
    ui->widget->check=4;
    ui->widget->updateGL();
}

void MainWindow::changing_x(double x)
{
    ui->widget->x_scale = x;
    ui->widget->check=4;
    ui->widget->updateGL();
}

void MainWindow::changing_y(double y)
{
    ui->widget->y_scale = y;
    ui->widget->check=4;
    ui->widget->updateGL();
}

void MainWindow::changing_x_Angle(int x)
{
    ui->widget->x_angle = x;
    ui->widget->check = 6;
    ui->widget->updateGL();
}

void MainWindow::changing_y_Angle(int y)
{
    ui->widget->y_angle = y;
    ui->widget->check = 7;
    ui->widget->updateGL();
}

void MainWindow::changing_z_Angle(int z)
{
    ui->widget->z_angle = z;
    ui->widget->check = 8;
    ui->widget->updateGL();
}

void MainWindow::x_Transfer(int x)
{
    ui->widget->x_transfer=x;
    ui->widget->check=5;
    ui->widget->updateGL();
}

void MainWindow::y_Transfer(int y)
{
    ui->widget->y_transfer=y;
    ui->widget->check=5;
    ui->widget->updateGL();
}

void MainWindow::z_Transfer(int z)
{
    ui->widget->z_transfer=z;
    ui->widget->check=5;
    ui->widget->updateGL();
}

void MainWindow::on_No_proection_triggered()
{
    ui->widget->xz_proection = ui->widget->yz_proection = ui->widget->xy_proection = false;
    ui->widget->updateGL();
}

void MainWindow::on_Matrix_triggered()
{
    float** matrix = ui->widget->returnMatrix();
    QString info = "Матрица преобразования\n";
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            info += (QString::number(matrix[i][j]) + ' ');
        }
        if(i == 0)
        {
            info += (QString::number(ui->widget->x_transfer) + ' ');
        }
        else if(i == 1)
        {
            info += (QString::number(ui->widget->y_transfer) + ' ');
        }
        else if(i == 2)
        {
            info += (QString::number(ui->widget->z_transfer) + ' ');
        }
        info+= '\n';
    }
    for(int i = 0; i < 3; i++)
    {
        info += "0 ";
    }
    info += '1';
    QDialog qd(this);
    QVBoxLayout* qv = new QVBoxLayout(&qd);
    qv->addWidget(new QLabel(info, &qd));
    qd.exec();
}

void MainWindow::on_Info_triggered()
{
    QString info = "Кнопки:\n";
    info += "w,a,s,d - вращение камеры\n";
    info += "u,b,l,r - движение камеры\n";
    QDialog qd(this);
    QVBoxLayout* qv = new QVBoxLayout(&qd);
    qv->addWidget(new QLabel(info, &qd));
    qd.exec();
}
