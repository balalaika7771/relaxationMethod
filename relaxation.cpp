#include "relaxation.h"
#include "ui_relaxation.h"

relaxation::relaxation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::relaxation)
{
    ui->setupUi(this);
}

relaxation::~relaxation()
{
    delete ui;
}

void relaxation::matrixUpdate(inputMatrix *newMatrix)
{
   matrix = newMatrix->getMatrixData();
   solve();
   update();
}

void relaxation::solve()
{
    x.clear();
    for(int i = 0; i < matrix.size(); i++){
        x.push_back(QVector<double>(1,0));
    }
    while(x.first().size() < 200){
        for (int i = 0; i < x.size(); ++i) {
            double newx = 0;;
            for(int j = 0; j < matrix[i].size()-1;j++){
                if(j == i){
                    continue;
                }
                newx += -matrix[i][j] * x[i].back();
            }
            newx += -matrix[i].back();
            newx /= matrix[i][i];
            x[i].push_back(newx);
        }
        for (int i = 0; i < x.size(); ++i){
            x[i].push_back(w * x[i].back() + (1 - w) * x[i][x[i].size()-2]);
        }
        double max = -10000;
        for (int i = 0; i < x.size(); ++i){
            if(max < abs(x[i][x[i].size()-1] - x[i][x[i].size()-2])){
                max = abs(x[i][x[i].size()-1] - x[i][x[i].size()-2]);
            }
        }
        if(max < eps){
            break;
        }
    }
    update();
}

void relaxation::paintEvent(QPaintEvent *event)
{
    ui->list->clear();
    for (int i = 0; i < x.size(); ++i){
        QString str = "X" + QString::number(i+1) + ":" + QString::number(x[i].back());
        ui->list->addItem(str);
    }
    if(curRow > 0 && curRow < ui->list->count()){

    }
}

void relaxation::on_epsSpin_valueChanged(double arg1)
{

    eps = arg1;
    solve();
}


void relaxation::on_wSpin_valueChanged(double arg1)
{
    if(arg1 > 1 || arg1 <= 0){
        return;
    }
    w =  arg1;
    solve();
}


void relaxation::on_list_currentRowChanged(int currentRow)
{
    curRow = currentRow;
}

