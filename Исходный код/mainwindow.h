#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include "letter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     ~MainWindow();
    void closeEvent(QCloseEvent*);
private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_action_Oxy_triggered();

    void on_action_Oyz_triggered();

    void on_action_Oxz_triggered();

    void on_scaling_triggered();

    void on_rotating_triggered();

    void on_transfering_triggered();

    void changing_z(double);

    void changing_x(double);

    void changing_y(double);

    void changing_x_Angle(int);

    void changing_y_Angle(int);

    void changing_z_Angle(int);

    void x_Transfer(int);

    void y_Transfer(int);

    void z_Transfer(int);

    void on_No_proection_triggered();

    void on_Matrix_triggered();

    void on_Info_triggered();

private:
     /*virtual*/ void keyPressEvent(QKeyEvent* pe);       // методы обработки события при нажатии определенной клавиши
    Ui::MainWindow *ui;
    bool isScale = false;
    bool isRotate = false;
    bool isTransfer = false;
signals:
    void closing();
};
#endif // MAINWINDOW_H
