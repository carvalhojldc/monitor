#ifndef PROCESSES_H
#define PROCESSES_H

#include <list>
#include <dirent.h>

#include "ProcessData.h"

class Processes {

private:
    ProcessData *processData;

    std::list<Process> processes;

    bool _searchProcess();

public:
    Processes();
    ~Processes();

    const std::list<Process> getProcesses();
};

#endif // PROCESSES_H
