#ifndef SCALING_H
#define SCALING_H

#include <QWidget>

namespace Ui {
class Scaling;
}

class Scaling : public QWidget
{
    Q_OBJECT

public:
    explicit Scaling(bool&, QWidget *parent = nullptr);
    ~Scaling();

private slots:

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void closeEvent(QCloseEvent *event);
signals:

    void zChange(double z);

    void xChange(double x);

    void yChange(double y);

private:
    Ui::Scaling *ui;
    bool& isScale;
};

#endif // SCALING_H
