#ifndef CPU_H
#define CPU_H

#include <unistd.h>

#include <vector>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define CPU_INFO_FILE "/proc/stat"
#define CPU_BUFFER 400
class CPU {
private:
    int numberCore;
    unsigned long *cpuUsedTotal_Old;
    unsigned long *cpuUsedWork_Old;
    unsigned long *cpuUsedTotal_New;
    unsigned long *cpuUsedWork_New;

    double *percCPU;

    void cpuInfoSearch(unsigned long *total, unsigned long *work);
public:
    CPU();
    ~CPU();
    void updateCPU(void);
    int getNumberCore() const;
    double getPerctCPU(int core) const;
};

#endif // CPU_H
