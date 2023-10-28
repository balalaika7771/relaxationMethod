#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->input,&inputMatrix::matrixUpdate,ui->method,&relaxation::matrixUpdate);
}

MainWindow::~MainWindow()
{
    delete ui;
}


