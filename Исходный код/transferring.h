#ifndef TRANSFERRING_H
#define TRANSFERRING_H

#include <QWidget>

namespace Ui {
class Transferring;
}

class Transferring : public QWidget
{
    Q_OBJECT

public:
    explicit Transferring(bool&, QWidget *parent = nullptr);
    ~Transferring();
    void closeEvent(QCloseEvent*);
private slots:
    void on_Transferring_x_valueChanged(int arg1);

    void on_transferring_y_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

signals:
    void zTransfer(double z);

    void xTransfer(double x);

    void yTransfer(double y);

private:
    Ui::Transferring *ui;
    bool& isTransfer;
};

#endif // TRANSFERRING_H
