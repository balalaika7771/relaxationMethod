#ifndef INPUTMATRIX_H
#define INPUTMATRIX_H
#include <QRegExpValidator>
#include <QWidget>
#include <QLineEdit>
namespace Ui {
class inputMatrix;
}

class inputMatrix : public QWidget
{
    Q_OBJECT

public:
    explicit inputMatrix(QWidget *parent = nullptr);
    ~inputMatrix();
    QVector<QVector<double>> getMatrixData();
public slots:

signals:
    void matrixUpdate(inputMatrix* me);
private slots:
    void updateMatrixSize();

    void on_scaleUp_pressed();

    void on_scaleDown_pressed();

    void on_tableWidget_cellChanged(int row, int column);

private:
    QRegExpValidator* validator;
    Ui::inputMatrix *ui;
    QVector<QVector<double>> matrixData;
};

#endif // INPUTMATRIX_H
