#include "cpu.h"

CPU::CPU() {
    numberCore = sysconf(_SC_NPROCESSORS_ONLN);

    cpuUsedTotal_Old = (unsigned long*)malloc(numberCore*sizeof(unsigned long));
    cpuUsedWork_Old = (unsigned long*)malloc(numberCore*sizeof(unsigned long));

    cpuUsedTotal_New = (unsigned long*)malloc(numberCore*sizeof(unsigned long));
    cpuUsedWork_New = (unsigned long*)malloc(numberCore*sizeof(unsigned long));

    percCPU = (double*)malloc(numberCore*sizeof(double));

    for(int i=0; i<numberCore; i++) {
        cpuUsedTotal_New[i] = 0;
        cpuUsedWork_New[i] = 0;
        cpuUsedTotal_New[i] = 0;
        cpuUsedWork_New[i] = 0;
        percCPU[i]  = 0;
    }

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
    for(int i=0; i<numberCore; i++) {
        cpuUsedTotal_New[i] = 0;
        cpuUsedWork_New[i] = 0;
        cpuUsedTotal_New[i] = 0;
        cpuUsedWork_New[i] = 0;
        percCPU[i]  = 0;
    }
    std::cout <<"old" <<std::endl;
    cpuInfoSearch(cpuUsedTotal_Old, cpuUsedWork_Old);
    sleep(1);
    std::cout <<"new" <<std::endl;
    cpuInfoSearch(cpuUsedTotal_New, cpuUsedWork_New);

    for(int i=0; i<numberCore; i++) {

        percCPU[i] = (cpuUsedWork_New[i] - cpuUsedWork_Old[i]) /
                (cpuUsedTotal_New[i] - cpuUsedTotal_Old[i]) * 100;

        std::cout << ((long double)cpuUsedWork_New[i] - (long double)cpuUsedWork_Old[i]) << "| " << (long double)cpuUsedWork_New[i] << " - " << (long double)cpuUsedWork_Old[i] << std::endl;
        std::cout << ((long double)cpuUsedTotal_New[i] - (long double)cpuUsedTotal_Old[i]) << "| " << (long double)cpuUsedTotal_New[i] << " - " << (long double)cpuUsedTotal_Old[i] << std::endl;
        std::cout << ((long double)cpuUsedWork_New[i] - (long double)cpuUsedWork_Old[i])/((long double)cpuUsedTotal_New[i] - (long double)cpuUsedTotal_Old[i])  << std::endl;


    }
}

int CPU::getNumberCore() const {
    return numberCore;
}

double CPU::getPerctCPU(int core) const {
    //(core < numberCore && core > 0) ? return percCPU[core] : return -1;
    return percCPU[core];
}


void CPU::cpuInfoSearch(unsigned long *total, unsigned long *work) {
    FILE *pfile = fopen(CPU_INFO_FILE, "r");
    char str[CPU_BUFFER];
    char *temp;
    int cAux = 0;

    for(int i=0; fgets(str, sizeof(str) , pfile) != NULL, i<numberCore; i++) {
        if(i == 0) printf("%s\n", str);
        temp = strtok(str, " ");

         while(temp != NULL) {

            temp = strtok(NULL, " ");
            //total[i] += atof(temp);
            if(temp != NULL) total[i] += atof(temp);
            if(i == 0) printf("%s\n", temp);

            if(cAux == 2 ) work[i] = total[i];
            if(cAux == 3) break;
            cAux += 1; /* cpuUsedWork_Old[i] recebe ate a 3a amostra */

        }
        //std::cout << i << " core " <<  work[i] << "--" <<total[i] << std::endl;
        cAux = 0;
    }

    fclose(pfile);

}
