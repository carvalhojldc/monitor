#include "cpu.h"

CPU::CPU() {
    numberCore = sysconf(_SC_NPROCESSORS_ONLN);

    cpuUsedTotal_Old = (long double*)malloc(numberCore*sizeof(long double));
    cpuUsedWork_Old = (long double*)malloc(3*sizeof(long int));

    cpuUsedTotal_New = (long double*)malloc(numberCore*sizeof(long double));
    cpuUsedWork_New = (long double*)malloc(3*sizeof(long double));

    percCPU = (double*)malloc(numberCore*sizeof(double));

    for(int i=0; i<numberCore; i++) cpuUsedTotal_New[i] = 0;
    for(int i=0; i<3; i++) cpuUsedWork_New[i] = 0;

    for(int i=0; i<numberCore; i++) cpuUsedTotal_New[i] = 0;
    for(int i=0; i<3; i++) cpuUsedWork_New[i] = 0;
    //cpuUsed.reserve(numberCore); //= new std::vector<double>(numberCore);
    //cpuUsed[numberCore] = new vector<float>();
    //qDebug() << memInfo->getMemAvailable();
    updateCPU();
}

CPU::~CPU() {
    free(cpuUsedTotal_Old);
    free(cpuUsedWork_Old);
    free(cpuUsedTotal_New);
    free(cpuUsedWork_New);
    free(percCPU);
}

void CPU::updateCPU(void) {
    cpuInfoSearch(cpuUsedTotal_Old, cpuUsedWork_Old);
    sleep(1);
    cpuInfoSearch(cpuUsedTotal_New, cpuUsedWork_New);
    for(int i=0; i<numberCore; i++) {
        percCPU[i] = (double)(cpuUsedWork_New[i] - cpuUsedWork_Old[i]) /
        (cpuUsedTotal_New[i] - cpuUsedTotal_Old[i]) * 100;
    }
}

int CPU::getNumberCore() const {
    return numberCore;
}

double CPU::getPerctCPU(int core) const {
    //(core < numberCore && core > 0) ? return percCPU[core] : return -1;
    return percCPU[core];
}


void CPU::cpuInfoSearch(long double *total, long double *work) {
    FILE *pfile = fopen(CPU_INFO_FILE, "r");
    char str[CPU_BUFFER];
    char *temp;
    int cAux = 0;

    for(int i=0; fgets(str, sizeof(str) , pfile) != NULL, i<numberCore; i++) {
        //printf("%s\n", str);
        temp = strtok(str, " ");
         while(temp != NULL) {
            temp = strtok(NULL, " ");
            if(temp != NULL) total[i] += atof(temp);
            if(cAux == 2 ) work[i] = total[i];
            cAux += 1; /* cpuUsedWork_Old[i] recebe ate a 3a amostra */
        }
        //if(i == 0) printf("core 0 %u %u\n", total[i], work[i]);
        cAux = 0;
    }

    fclose(pfile);

}
