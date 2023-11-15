#ifndef RELAXATION_H
#define RELAXATION_H

#include <QWidget>
#include "inputmatrix.h"
#include <QSharedPointer>
namespace Ui {
class relaxation;
}

class relaxation : public QWidget
{
    Q_OBJECT

public:
    explicit relaxation(QWidget *parent = nullptr);
    ~relaxation();
public slots:
     void matrixUpdate(inputMatrix* newMatrix);
private:
    QVector<QVector<double>> matrix;
    Ui::relaxation *ui;
    QVector<QVector<double>> x;
    double w = 0.75;
    double eps = 0.001;
    int curRow = -1;
protected:
    void solve();
    void paintEvent(QPaintEvent *event);
private slots:
    void on_epsSpin_valueChanged(double arg1);
    void on_wSpin_valueChanged(double arg1);
    void on_list_currentRowChanged(int currentRow);
};

#endif // RELAXATION_H
