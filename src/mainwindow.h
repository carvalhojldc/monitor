#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <list>

#include "qcustomplot.h"
#include "Linux/meminfo.h"
#include "Linux/cpu.h"
#include "Linux/Processes.h"

#define NUMB_COL_PROCESS 5
enum columProcess {PROCESS_PID, PROCESS_NAME, PROCESS_USER, PROCESS_NICE, PROCESS_MEMORY};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void UI_ConfigProcesses();
    void UI_ConfigGraphMemory();
    void UI_ConfigGraphCPU();

    void graphMemory();
    void graphCPU();
    void graphics();
    void processesTable();

    void killProcesses();
    void pauseProcesses();
    void continueProcesses();
    void previousWeek(int row, int col);

private:
    Ui::MainWindow *ui;

    QTimer *timerGraph;
    QThread *threadGraph;

    QTimer *timerProcesses;
    QThread *threadProcesses;

    Processes *processes;
    MemInfo *memInfo;
    CPU *cpu;

    std::list<Process> listProcess, listProcess_Old;

    int numCores;
    double memTotal;
    double memSwapTotal;

    float timescale;
    int pidClicked;

    QStringList listColumProcess = { "PID" , "Process Name" , "User" , "Prio", "Memory"};
};

#endif // MAINWINDOW_H
