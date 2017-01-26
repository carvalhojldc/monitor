#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"

#include <QDebug>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "meminfo.h"
#include "cpu.h"
#include "ProcessData.h"

#include <signal.h>

#define NUMB_COL_PROCESS 5
enum columProcess {PID, PROCESS_NAME, USER, NICE, MEMORY};


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
    void processes();

    void killProcesses();
    void pauseProcesses();
    void continueProcesses();
    void sort(const QString &);
    void previousWeek(int row, int col);

private:
    Ui::MainWindow *ui;

    QTimer *timerGraph;
    QThread *threadGraph;

    QTimer *timerProcesses;
    QThread *threadProcesses;

    MemInfo *memInfo;
    CPU *cpu;

    ProcessData *processData;
    const Process *process;

    int numCores;

    double memTotal;
    double memSwapTotal;

    float timescale;

    int teste = 0;

    int qpidantigo = 0;

    bool ts = false;

    int pidClicked;

    QStringList listColumProcess = { "PID" , "Process Name" , "User" , "Prio", "Memory"};
};

#endif // MAINWINDOW_H
