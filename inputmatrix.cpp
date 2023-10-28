#include "inputmatrix.h"
#include "ui_inputmatrix.h"

inputMatrix::inputMatrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputMatrix)
{
    ui->setupUi(this);
    validator = new QRegExpValidator(QRegExp("[0-9.]+"), this);
    int rowCount = ui->tableWidget->rowCount();
    int colCount = ui->tableWidget->columnCount();
    matrixData = QVector<QVector<double>> (rowCount, QVector<double>(colCount));

    matrixUpdate(this);
}

inputMatrix::~inputMatrix()
{
    delete ui;
}

QVector<QVector<double> > inputMatrix::getMatrixData()
{
    return matrixData;
}

void inputMatrix::updateMatrixSize()
{

    int rowCount = ui->tableWidget->rowCount();
    int colCount = ui->tableWidget->columnCount();
    matrixData = QVector<QVector<double>> (rowCount, QVector<double>(colCount));
    for(int i = 0; i < rowCount;i++){
        for(int j = 0; j < colCount; j++){
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if(item == nullptr){
                continue;
            }
            bool ok;
            double value = item->text().toDouble(&ok);
            if (ok) {
                matrixData[i][j] = value;
            }
        }

    }
     matrixUpdate(this);
}


void inputMatrix::on_scaleUp_pressed()
{
    int rowToInsert = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowToInsert);
    QString newRowName = "линейное уравнение " + QString::number(rowToInsert+1);
    QTableWidgetItem* headerRowItem = new QTableWidgetItem(newRowName);
    ui->tableWidget->setVerticalHeaderItem(rowToInsert, headerRowItem);

    int columnToInsert = ui->tableWidget->columnCount()-1;
    ui->tableWidget->insertColumn(columnToInsert);
    QString newcolumnName = "X " + QString::number(columnToInsert+1);
    QTableWidgetItem* headerItem = new QTableWidgetItem(newcolumnName);
    ui->tableWidget->setHorizontalHeaderItem(columnToInsert, headerItem);
    updateMatrixSize();
}


void inputMatrix::on_scaleDown_pressed()
{
    if(ui->tableWidget->rowCount()<=2){
        return;
    }
    ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    ui->tableWidget->removeColumn(ui->tableWidget->columnCount()-2);
    updateMatrixSize();
}


void inputMatrix::on_tableWidget_cellChanged(int row, int column)
{
 QTableWidgetItem* item = ui->tableWidget->item(row, column);
 bool ok;
 double value = item->text().toDouble(&ok);
 if (ok) {
     matrixData[row][column ] = value;
 }
 matrixUpdate(this);
}

