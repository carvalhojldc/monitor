
/*
    File: /proc/stat
        0 cpuid: number of cpu
        1 user: normal processes executing in user mode
        2 nice: niced processes executing in user mode
        3 system: processes executing in kernel mode
        4 idle: twiddling thumbs
        5 iowait: waiting for I/O to complete
        6 irq: servicing interrupts
        7 softirq: servicing softirqs
          steal
          guest
          guest_nice
*/

#ifndef CPU_H
#define CPU_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <climits>

#define CPU_FILE "/proc/stat"

class CPU {
private:
    int numCores;
    long int *cpuDataTotalNew,
             *cpuDataTotalOld,
             *cpuDataIdleNew,
             *cpuDataIdleOld;
    float *percCPU;

    int readCPUFile(long int *total_, long int *idle_);
    float truncate(float number);

public:
    CPU();
    ~CPU();

    int updateCPU();
    int getNumberCore();
    float getPerctCPU(int core);
};

#endif // CPU_H
