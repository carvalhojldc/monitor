#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cpu.h"

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CPU *cpu;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
