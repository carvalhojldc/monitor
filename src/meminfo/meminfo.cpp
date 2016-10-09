#include "meminfo.h"

MemInfo::MemInfo() {
    memTotal = 0;
    memAvailable = 0;

    memInfoUpdate();
    memRamCalc();
}

MemInfo::~MemInfo() {

}

void MemInfo::memInfoSearch(void) {
    FILE *pfile = fopen(MEM_INFO_FILE, "r");
    char str[MEM_BUFFER];
    char *temp;

    while(fgets(str, sizeof(str) , pfile) != NULL) {
        temp = strtok(str, ": ");

        if(strcmp(temp, "MemTotal") == 0)
            memTotal = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "MemAvailable") == 0)
            memAvailable = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "MemFree") == 0)
            memFree = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "Buffers") == 0)
            buffers = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "Cached") == 0)
            cached = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "SwapTotal") == 0)
            swapTotal = (unsigned long)atof(strtok (NULL, ": "));
        else if(strcmp(temp, "SwapFree") == 0)
            swapFree = (unsigned long)atof(strtok (NULL, ": "));
    }

    fclose(pfile);
}

void MemInfo::memRamCalc(void) {
    memRam = memTotal - (memFree + buffers + cached);
}

unsigned long MemInfo::getMemTotal(void) const {
    return memTotal;
}

unsigned long MemInfo::getMemAvailable(void) const {
    return memTotal - memRam;
}

unsigned long MemInfo::getMemUsed(void) const {
    return memRam;
}

unsigned long MemInfo::getSwapTotal(void) const {
    return swapTotal;
}

unsigned long MemInfo::getSwapFree(void) const {
    return swapFree;
}

unsigned long MemInfo::getSwapUsed(void) const {
    return swapTotal - swapFree;
}

void MemInfo::memInfoUpdate(void) {
    memInfoSearch();
    memRamCalc();
}
