#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    memInfo = new MemInfo();
    cpu = new CPU();
    processo = new Processo();

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

    connect(ui->pb_kill, SIGNAL(clicked(bool)), this, SLOT(killProcesses()));
    connect(ui->pb_pause, SIGNAL(clicked(bool)), this, SLOT(pauseProcesses()));
    connect(ui->pb_continue, SIGNAL(clicked(bool)), this, SLOT(continueProcesses()));

    connect(ui->search, SIGNAL(textChanged(const QString &)), this, SLOT(sort(const QString &)));

    connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(previousWeek(int, int)));

    //
    numCores = cpu->getNumberCore();
    memInfo->memInfoUpdate();
    memTotal = memInfo->getMemTotal();
    memSwapTotal = memInfo->getSwapTotal();
    timescale = 0;


    // UI
    UI_ConfigProcesses();
    UI_ConfigGraphMemory();
    UI_ConfigGraphCPU();

}

MainWindow::~MainWindow()
{
    threadGraph->terminate();
    threadProcesses->terminate();
    delete ui;
}

void MainWindow::UI_ConfigProcesses() {
    ui->tableWidget->setColumnCount(NUMB_COL_PROCESS);
    //ui->tableWidget->columnSpan(    )

    ui->tableWidget->setColumnWidth(PID, 100);
    ui->tableWidget->setColumnWidth(PROCESS_NAME, 230);
    ui->tableWidget->setColumnWidth(USER, 100);
    ui->tableWidget->setColumnWidth(NICE, 100);
    ui->tableWidget->setColumnWidth(MEMORY, 100);

    //ui->tableWidget->setSortingEnabled(true);
    //ui->tableWidget->sortByColumn(PID,Qt::AscendingOrder);
    //ui->tableWidget->sortByColumn(PROCESS_NAME,Qt::AscendingOrder);

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
            ui->graphCPU->graph(i)->setName("CPU");
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
            strCPU  =  "  CPU " + QString::number(cpu->getPerctCPU(i)) + "% ";
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

void MainWindow::killProcesses() {
    if(pidClicked != getpid())
    kill(pidClicked, SIGKILL);
}

void MainWindow::pauseProcesses() {
    if(pidClicked != getpid())
    kill(pidClicked, SIGSTOP);
}

void MainWindow::continueProcesses() {
    if(pidClicked != getpid())
    kill(pidClicked, SIGCONT);
}


void MainWindow::previousWeek(int row, int col) {
    pidClicked = ui->tableWidget->item(row,0)->text().toInt();
}

void MainWindow::sort(const QString &filter)
{
// http://stackoverflow.com/questions/6785481/how-to-set-filter-option-in-qtablewidget// http://stackoverflow.com/questions/20585795/how-to-connect-the-signal-valuechanged-from-qlineedit-to-a-custom-slot-in-qt
    for( int i = 0; i < ui->tableWidget->rowCount(); ++i )
    {
        bool match = false;
        for( int j = 0; j < 3; ++j )
        {
            QTableWidgetItem *item = ui->tableWidget->item( i, j );
            if( item->text().contains(filter) )
            {
                match = true;
                break;
            }
        }
        ui->tableWidget->setRowHidden( i, !match );
    }

}

void MainWindow::processes() {

    int i = 0;
    int *vec;
    int qPID;


    qPID = processo->Q_PIDS();
    vec = processo->leitura_PID();


    if(qPID<qpidantigo)
    for(int linha = 0; linha<(qpidantigo-qPID); linha++) {
        ui->tableWidget->removeRow(qpidantigo-linha);
    }
    else if(qpidantigo<qPID)
    for(int linha = 0; linha<(qPID-qpidantigo); linha++) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }
    qpidantigo = qPID;


    for(int ppid = 0; ppid<qPID; ppid++) {

        std::string s;
        std::stringstream out;
        out << vec[ppid];
        s = out.str();
        processo->leitura_nome_processo(s);
        //processo->leitura_memoria_processo(s);
        //processo->leitura_prioridade(s);
        //processo->Get_nomeProcesso();
        QString nameP = processo->Get_nomeProcesso().c_str();
        //QString memR = QString::number(processo->Get_memoriaRam());
        //QString prio = QString::number(processo->Get_prioridade());

        ui->tableWidget->setItem(ppid,PID,new QTableWidgetItem(QString::number(vec[ppid])));

        ui->tableWidget->setItem(ppid,PROCESS_NAME,
                                 new QTableWidgetItem(nameP));
        ui->tableWidget->setItem(ppid,USER,new QTableWidgetItem(".."));
        ui->tableWidget->setItem(ppid,NICE,new QTableWidgetItem(".."));
        ui->tableWidget->setItem(ppid,MEMORY,new QTableWidgetItem(".."));

    }


}
