#include "cpu.h"

CPU::CPU() {
    numCores = sysconf(_SC_NPROCESSORS_ONLN);

    /*(numCores+1) -> N_CPUs + AverageCPUs*/
    cpuDataTotalNew = (long int*)malloc((numCores+1) * sizeof(long int));
    cpuDataTotalOld = (long int*)malloc((numCores+1) * sizeof(long int));
    cpuDataIdleNew = (long int*)malloc((numCores+1) * sizeof(long int));
    cpuDataIdleOld = (long int*)malloc((numCores+1) * sizeof(long int));

    percCPU = (float*)malloc((numCores+1) * sizeof(float));

    readCPUFile(cpuDataTotalOld, cpuDataIdleOld);
}

CPU::~CPU() {
    free(cpuDataTotalNew);
    free(cpuDataTotalOld);
    free(cpuDataIdleNew);
    free(cpuDataIdleOld);
    free(percCPU);
}

int CPU::readCPUFile(long int *total_, long int *idle_) {
    FILE* file;

    if( (file = fopen(CPU_FILE, "r") ) == NULL) {
        return -1;
    }

    long int cpuf_user;
    long int cpuf_nice;
    long int cpuf_system;
    long int cpuf_idle;
    long int cpuf_iowait;
    long int cpuf_irq;
    long int cpuf_softirq;

    long int idle;
    long int noIdle;
    long int total;

    char str[ _POSIX2_LINE_MAX ];

    for(int core=0; core<=numCores; core++) {

        fgets(str, sizeof(str) , file);

        /* cpu_file
         *  0 cpu
         *  1 user
         *  2 nice
         *  3 system
         *  4 idle
         *  5 iowait
         *  6 irq
         *  7 softirq
         *  steal
         *  guest
         *  guest_nice
        */

        strtok(str, " ");
        cpuf_user    = atof( strtok(NULL, " ") );
        cpuf_nice    = atof( strtok(NULL, " ") );
        cpuf_system  = atof( strtok(NULL, " ") );
        cpuf_idle    = atof( strtok(NULL, " ") );
        cpuf_iowait  = atof( strtok(NULL, " ") );
        cpuf_irq     = atof( strtok(NULL, " ") );
        cpuf_softirq = atof( strtok(NULL, " ") );

        idle   = cpuf_idle + cpuf_iowait;
        noIdle = cpuf_user + cpuf_nice + cpuf_system + cpuf_irq + cpuf_softirq;
        total  = idle + noIdle;

        total_[core] = total;
        idle_[core]  = idle;
    }

    fclose(file);
}

float CPU::truncate(float number) {
    return (int)number +(((int)((number - (int)number)*10.))/10.);
}

int CPU::updateCPU() {

    if( readCPUFile(cpuDataTotalNew, cpuDataIdleNew) < 0 ) {
        return -1;
    }

    float totalOld,
          idleOld,
          totalNew,
          idleNew;

    for(int core=0; core<(numCores+1); core++) {
        totalOld = cpuDataTotalOld[core],
        idleOld  = cpuDataIdleOld[core],
        totalNew = cpuDataTotalNew[core],
        idleNew  = cpuDataIdleNew[core];

        percCPU[core] = truncate( ( (totalNew - totalOld) - \
                (idleNew-idleOld) ) / (totalNew - totalOld) * 100. );

        if( percCPU[core] < 0 ) { percCPU[core] = 0; }
    }

    if( readCPUFile(cpuDataTotalOld, cpuDataIdleOld) < 0) {
        return -1;
    }

    return 1;
}

int CPU::getNumberCore() {
    return numCores;
}

float CPU::getPerctCPU(int core) {
    return truncate( percCPU[core] );
}



