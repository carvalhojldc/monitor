#include "cpu.h"

CPU::CPU() {
    numCores = sysconf(_SC_NPROCESSORS_ONLN);
    /*(numCores+1) -> N_CPUs + AverageCPUs*/
    cpuDataTNew = (long int*)malloc((numCores+1) * sizeof(long int)); /*numCores x 2*/
    cpuDataTOld = (long int*)malloc((numCores+1) * sizeof(long int));
    cpuDataINew = (long int*)malloc((numCores+1) * sizeof(long int)); /*numCores x 2*/
    cpuDataIOld = (long int*)malloc((numCores+1) * sizeof(long int));

    percCPU = (float*)malloc((numCores+1) * sizeof(float));

    readCPUFile(cpuDataTOld, cpuDataIOld);
}

CPU::~CPU() {
    free(cpuDataTNew);
    free(cpuDataTOld);
    free(cpuDataINew);
    free(cpuDataIOld);
    free(percCPU);
}

void CPU::readCPUFile(long int *total_, long int *idle_) {
    FILE* pFile = fopen(CPU_FILE, "r");

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

    char *temp;
    char str[CPU_BUFFER];

    if(pFile == NULL)
        exit(-1);

    for(int core=0; fgets(str, sizeof(str) , pFile) != NULL, core<=numCores; core++) {
        temp = strtok(str, " ");
        for(int contAux= 0; temp!= NULL, contAux<7; contAux++){
            /*
                user 0
                nice 1
                system 2
                idle 3
                iowait 4
                irq 5
                softirq 6
                steal
                guest
                guest_nice
            */
            temp = strtok(NULL, " ");
            if(temp!=NULL) {
                switch (contAux) {
                    case CPUF_USER:
                        cpuf_user = atof(temp);
                        break;
                    case CPUF_NICE:
                        cpuf_nice = atof(temp);
                        break;
                    case CPUF_SYSTEM:
                        cpuf_system = atof(temp);
                        break;
                    case CPUF_IDLE:
                        cpuf_idle = atof(temp);
                        break;
                    case CPUF_IOWAIT:
                        cpuf_iowait = atof(temp);
                        break;
                    case CPUF_IRQ:
                        cpuf_irq = atof(temp);
                        break;
                    case CPUF_SOFTIRQ:
                        cpuf_softirq = atof(temp);
                        break;
                }
            }
        }

        idle = cpuf_idle + cpuf_iowait;
        noIdle = cpuf_user + cpuf_nice + cpuf_system + cpuf_irq + cpuf_softirq;
        total = idle + noIdle;

        total_[core] = total;
        idle_[core] = idle;
    }


    fclose(pFile);
}
float CPU::truncate(float number) {
    return (int)number +(((int)((number - (int)number)*10.))/10.);
    return number;
}

void CPU::updateCPU() {

    readCPUFile(cpuDataTNew, cpuDataINew);

    float totalOld,
            idleOld ,
            totalNew ,
            idleNew ;

    for(int core=0; core<=numCores; core++) {
        totalOld = cpuDataTOld[core],
        idleOld = cpuDataIOld[core],
        totalNew = cpuDataTNew[core],
        idleNew = cpuDataINew[core];

        percCPU[core] = truncate(((totalNew - totalOld)-(idleNew-idleOld))/(totalNew - totalOld) * 100.);
    }
    readCPUFile(cpuDataTOld, cpuDataIOld);
}

int CPU::getNumberCore() {
    return numCores;
}

float CPU::getPerctCPU(int core) {
    return percCPU[core];
}



