#ifndef ROTATING_H
#define ROTATING_H

#include <QWidget>

namespace Ui {
class Rotating;
}

class Rotating : public QWidget
{
    Q_OBJECT

public:
    explicit Rotating(bool&, QWidget *parent = nullptr);
    ~Rotating();
    void closeEvent(QCloseEvent *event);
signals:

    void z_AngleChange(double z);

    void x_AngleChange(double x);

    void y_AngleChange(double y);

private slots:
    void on_rotating_x_valueChanged(int arg1);

    void on_roating_y_valueChanged(int arg1);

    void on_rotating_z_valueChanged(int arg1);

private:
    Ui::Rotating *ui;
    bool& isRotate;
};

#endif // ROTATING_H
