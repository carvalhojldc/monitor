#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    memInfo = new MemInfo();
    cpu = new CPU();

    // Thread e Timer
    timerGraph = new QTimer(0);
    threadGraph = new QThread(this);
    timerGraph->start(100);
    threadGraph->start();
    timerGraph->moveToThread(threadGraph);

    timerProcesses = new QTimer(0);
    threadProcesses = new QThread(this);
    timerProcesses->start(1000);
    threadProcesses->start();
    timerProcesses->moveToThread(threadProcesses);

    //
    connect(timerGraph, SIGNAL(timeout()), this, SLOT(graphics()));
    connect(timerProcesses, SIGNAL(timeout()), this, SLOT(processes()));


    //
    numCores = cpu->getNumberCore();
    memInfo->memInfoUpdate();
    memTotal = memInfo->getMemTotal();
    memSwapTotal = memInfo->getSwapTotal();
    timescale = 0;

    QLabel *cell[numCores+1];
    for(int i=0;i<numCores+1;i++) {
       // cell[i] = new QLabel();
        //ui->gridCPU->addWidget(cell[i],0,i,Qt::AlignCenter);
        //ui.cell[i]->setText("aa");
    }
    // UI
    UI_ConfigProcesses();
    UI_ConfigGraphMemory();
    UI_ConfigGraphCPU();

   // this->show();
}

MainWindow::~MainWindow()
{
    threadGraph->terminate();
    threadProcesses->terminate();
    delete ui;
}

void MainWindow::UI_ConfigProcesses() {
    ui->tableWidget->setColumnCount(6);

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(listColumProcess);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

    ui->graphMemory->xAxis->setLabel("Seconds");
    ui->graphMemory->yAxis->setLabel("% Memory");
    ui->graphMemory->yAxis->setRange(0,100);
    //ui->graphMemory->yAxis->setNumberPrecision(5);
    //ui->graphMemory->xAxis->setSubTickCount(10);

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

    for(int i=0; i<=numCores; i++) {
        ui->graphCPU->addGraph();
        if(i == 0)
            ui->graphCPU->graph(i)->setName("Average");
        else
            ui->graphCPU->graph(i)->setName("CPU" + QString::number(i));
        ui->graphCPU->graph(i)->setPen(QPen(QColor(rand()%200+10,rand()%200+10,rand()%200+10,255)));
        ui->graphCPU->graph(i)->setAntialiasedFill(false);
    }

    ui->graphCPU->xAxis->setLabel("Seconds");
    ui->graphCPU->yAxis->setLabel("% CPU");

    //ui->graphCPU->xAxis->setSubTickCount(10);
    ui->graphCPU->yAxis->setRange(0,100);
    ui->graphCPU->yAxis->setTickLengthIn(5);
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

    QString strCPU;

    cpu->updateCPU();

    if(teste == 5) {
        strCPU.clear();
        for(int i=0; i<=numCores; i++) {
            if(i == 0)
            strCPU  =  "  Average " + QString::number(cpu->getPerctCPU(i)) + "% ";
            else
            strCPU  +=  "  CPU" + QString::number(i) + " " + QString::number(cpu->getPerctCPU(i)) + "% ";

            ui->graphCPU->graph(i)->addData(timescale,cpu->getPerctCPU(i));
        }

        ui->labelCPU->setText(strCPU);
        teste = 0;
    }
    teste += 1;

    for(int i=0; i<=numCores; i++)


    ui->graphCPU->xAxis->setRange(timescale, 60, Qt::AlignRight);
    ui->graphCPU->replot();
}

void MainWindow::graphics() {
    graphMemory();
    graphCPU();

    timescale += 0.1;
}

void MainWindow::processes() {

    int i = 0;
    if(ui->tableWidget->rowCount() <1)
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(i,PID,new QTableWidgetItem("991"));
    ui->tableWidget->setItem(i,PROCESS_NAME,new QTableWidgetItem("firefox"));
    ui->tableWidget->setItem(i,PROCESS_NAME,new QTableWidgetItem("firefox"));
    ui->tableWidget->setItem(i,USER,new QTableWidgetItem("gg"));
    ui->tableWidget->setItem(i,NICE,new QTableWidgetItem("0"));
    ui->tableWidget->setItem(i,PCPU,new QTableWidgetItem("3"));
    ui->tableWidget->setItem(i,MEMORY,new QTableWidgetItem("23.1"));



}
