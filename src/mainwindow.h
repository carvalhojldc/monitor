#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qcustomplot.h"

#include <QDebug>

#include "meminfo.h"
#include "cpu.h"

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
    void UI_ConfigGraphMemory();
    void UI_ConfigGraphCPU();
    void graphMemory();
    void graphCPU();
    void graphics();


private:
    Ui::MainWindow *ui;

    QTimer *timerGraph;
    QThread *threadGraph;

    MemInfo *memInfo;
    CPU *cpu;

    int numCores;

    double memTotal;
    double memSwapTotal;

    float timescale;
};

#endif // MAINWINDOW_H
