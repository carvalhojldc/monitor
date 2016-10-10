#ifndef CPU_H
#define CPU_H


/*
http://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
        read in cpu information from file
        The meanings of the columns are as follows, from left to right:
            0cpuid: number of cpu
            1user: normal processes executing in user mode
            2nice: niced processes executing in user mode
            3system: processes executing in kernel mode
            4idle: twiddling thumbs
            5iowait: waiting for I/O to complete
            6irq: servicing interrupts
            7softirq: servicing softirqs

        #the formulas from htop
             user    nice   system  idle      iowait irq   softirq  steal  guest  guest_nice
        cpu  74608   2520   24433   1117073   6176   4054  0        0      0      0
*/

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>

#define CPU_FILE "/proc/stat"
#define CPU_BUFFER 200

enum CPUF_ { CPUF_USER, CPUF_NICE, CPUF_SYSTEM, CPUF_IDLE, CPUF_IOWAIT, CPUF_IRQ, CPUF_SOFTIRQ };

class CPU {
private:
    int numCores;
    long int *cpuDataTNew,
            *cpuDataTOld,
            *cpuDataINew,
            *cpuDataIOld;
    float *percCPU;

    void readCPUFile(long int *total_, long int *idle_);

public:
    CPU();
    ~CPU();
    void updateCPU();
    int getNumberCore();
    float truncate(float number);
    float getPerctCPU(int core);
};

#endif // CPU_H
