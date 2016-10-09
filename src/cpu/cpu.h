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
    long double *cpuUsedTotal_Old;
    long double *cpuUsedWork_Old;
    long double *cpuUsedTotal_New;
    long double *cpuUsedWork_New;

    double *percCPU;

    void cpuInfoSearch(long double *total, long double *work);
public:
    CPU();
    ~CPU();
    void updateCPU(void);
    int getNumberCore() const;
    double getPerctCPU(int core) const;
};

#endif // CPU_H
