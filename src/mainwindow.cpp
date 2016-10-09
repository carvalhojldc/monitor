#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    memInfo = new MemInfo();
    cpu = new CPU();

    timerGraph = new QTimer(0);
    threadGraph = new QThread(this);
    timerGraph->start(100);
    threadGraph->start();
    timerGraph->moveToThread(threadGraph);
    connect(timerGraph, SIGNAL(timeout()), this, SLOT(graphics()));

    numCores = cpu->getNumberCore();
    memInfo->memInfoUpdate();

    memTotal = memInfo->getMemTotal();
    memSwapTotal = memInfo->getSwapTotal();

    timescale = 0;

    UI_ConfigGraphMemory();
    UI_ConfigGraphCPU();


    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "PID" << "Process Name" << "User" << "Nice" << "%CPU" << "Memory");
}

MainWindow::~MainWindow()
{
    threadGraph->terminate();
    delete ui;
}

void MainWindow::UI_ConfigGraphMemory() {
    ui->graphMemory->legend->setVisible(true);
    //ui->graphMemory->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->graphMemory->plotLayout()->addElement(0, 1, subLayout);
    subLayout->addElement(0, 0, new QCPLayoutElement);
    subLayout->addElement(1, 0, ui->graphMemory->legend);
    subLayout->addElement(2, 0, new QCPLayoutElement);
    ui->graphMemory->plotLayout()->setColumnStretchFactor(1, 0.001);

    // sinal enviado
    ui->graphMemory->addGraph(); // blue line
    ui->graphMemory->graph(0)->setPen(QPen(Qt::blue));
    ui->graphMemory->graph(0)->setAntialiasedFill(false);
    ui->graphMemory->graph(0)->setName("RAM");

    // sinal calculado
    ui->graphMemory->addGraph(); // red line
    ui->graphMemory->graph(1)->setPen(QPen(Qt::red));
    ui->graphMemory->graph(1)->setAntialiasedFill(false);
    ui->graphMemory->graph(1)->setName("Swap");

    ui->graphMemory->xAxis->setLabel("Time (s)");
    ui->graphMemory->yAxis->setRange(0,100);
    ui->graphMemory->yAxis->setNumberPrecision(5);
    ui->graphMemory->yAxis->setLabel("% Memory");
    ui->graphMemory->xAxis->setSubTickCount(10);

    ui->graphMemory->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphMemory->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphMemory->axisRect(0)->setRangeZoom(Qt::Vertical);
}

void MainWindow::UI_ConfigGraphCPU() {
    ui->graphCPU->legend->setVisible(true);
    //ui->graphCPU->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignLeft|Qt::AlignBottom);

    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    ui->graphCPU->plotLayout()->addElement(0, 1, subLayout);
    subLayout->addElement(0, 0, new QCPLayoutElement);
    subLayout->addElement(1, 0, ui->graphCPU->legend);
    subLayout->addElement(2, 0, new QCPLayoutElement);
    ui->graphCPU->plotLayout()->setColumnStretchFactor(1, 0.001);

    for(int i=0; i<numCores; i++) {
        ui->graphCPU->addGraph();
        ui->graphCPU->graph(i)->setName("core" + QString::number(i));
        ui->graphCPU->graph(i)->setPen(QPen(QColor(rand()%200+10,rand()%200+10,rand()%200+10,255)));
        ui->graphCPU->graph(i)->setAntialiasedFill(false);
    }

    ui->graphCPU->xAxis->setLabel("Time (s)");
    ui->graphCPU->yAxis->setLabel("% CPU");

    //ui->graphCPU->xAxis->setSubTickCount(10);
    ui->graphCPU->yAxis->setRange(0,100);
    //ui->graphCPU->yAxis->setNumberPrecision(5);

    ui->graphCPU->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    ui->graphCPU->axisRect(0)->setRangeDrag(Qt::Vertical);
    ui->graphCPU->axisRect(0)->setRangeZoom(Qt::Vertical);

}

void MainWindow::graphMemory() {
    memInfo->memInfoUpdate();

    ui->lb_m_ram->setText("RAM " + QString::number(memInfo->getMemUsedGiB()) +
                          "GiB (" + QString::number(memInfo->getMemUsedPerct()) + "%) de " +
                          QString::number(memInfo->getMemTotalGiB()) + " GiB");

    ui->lb_m_swap->setText("Swap " + QString::number(memInfo->getSwapUsedGiB()) +
                          "GiB (" + QString::number(memInfo->getSwapUsedPerct()) + "%) de " +
                          QString::number(memInfo->getSwapTotalGiB()) + " GiB");

    ui->graphMemory->graph(0)->addData(timescale,memInfo->getMemUsedPerct());
    ui->graphMemory->graph(1)->addData(timescale,memInfo->getSwapUsedPerct());

    ui->graphMemory->xAxis->setRange(timescale, 60, Qt::AlignRight);
    ui->graphMemory->replot();
}

void MainWindow::graphCPU() {

    for(int i=0; i<numCores; i++) {
        ui->graphCPU->graph(i)->addData(timescale,12+i+(5*i));
    }


    ui->graphCPU->xAxis->setRange(timescale, 60, Qt::AlignRight);
    ui->graphCPU->replot();
}

void MainWindow::graphics() {
    graphMemory();
    graphCPU();

    timescale += 0.1;
}
