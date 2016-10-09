#include "cpu.h"
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
        int numberCore = 4;

        if(pFile == NULL)
            exit(-1);

        for(int core=0; fgets(str, sizeof(str) , pFile) != NULL, core<numCores; core++) {
            //printf("\n# %s ", str);
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
            //printf("\ncore %d", core);
            // cpu[core][0] = total;
            total_[core] = total;
            idle_[core] = idle;
            //cpu[core][1] = idle;
            //printf("%d %d\n",total, cpu[i][0] );
        }


        fclose(pFile);
    }
    float CPU::truncate(float number) {
        return (int)number +(((int)((number - (int)number)*10.))/10.);
    }
    CPU::CPU() {
        numCores = 4;
        cpuDataTNew = (long int*)malloc(numCores * sizeof(long int)); /*numCores x 2*/
        cpuDataTOld = (long int*)malloc(numCores * sizeof(long int));
        cpuDataINew = (long int*)malloc(numCores * sizeof(long int)); /*numCores x 2*/
        cpuDataIOld = (long int*)malloc(numCores * sizeof(long int));

        percCPU = (float*)malloc(numCores * sizeof(float));

        //for(int colum=0; colum<2; colum++) { /*for total e idle*/
            //cpuDataNew[colum] = (long int*)malloc(2 * sizeof(long int));
            //cpuDataOld[colum] = (long int*)malloc(2 * sizeof(long int));
        //}
        readCPUFile(cpuDataTOld, cpuDataIOld);
    }
    CPU::~CPU() {
        free(cpuDataTNew);
        free(cpuDataTOld);
        free(cpuDataINew);
        free(cpuDataIOld);
        free(percCPU);
    }
    void CPU::updateCPU() {

        //sleep(1);
        readCPUFile(cpuDataTNew, cpuDataINew);
        int totalOld,
                idleOld ,
                totalNew ,
                idleNew ;

/*
        printf("\nt %d\n", ((totalNew - totalOld)-(idleNew-idleOld)));
        printf("\nt1 %d\n", (idleNew-idleOld));
        printf("\nt2 %d\n", (totalNew - totalOld));
        printf("\nresultado %f", (float)((totalNew - totalOld)-(idleNew-idleOld))/(totalNew - totalOld) * 100.);
*/
        for(int core=0; core<numCores; core++) {
            totalOld = cpuDataTOld[core],
            idleOld = cpuDataIOld[core],
            totalNew = cpuDataTNew[core],
            idleNew = cpuDataINew[core];
            //printf("\ncore%d %f", core, (float)((totalNew - totalOld)-(idleNew-idleOld))/(totalNew - totalOld) * 100.);
            percCPU[core] = truncate((float)((totalNew - totalOld)-(idleNew-idleOld))/(float)(totalNew - totalOld) * 100.);
        }
        readCPUFile(cpuDataTOld, cpuDataIOld);
    }

    int CPU::getNumberCore() {
        return numCores;
    }

    float CPU::getPerctCPU(int core) {
        return percCPU[core];
    }



