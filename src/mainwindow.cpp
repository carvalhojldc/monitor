#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cpu = new CPU();

    qDebug() << cpu->getNumberCore();
}

MainWindow::~MainWindow()
{
    delete ui;
}
