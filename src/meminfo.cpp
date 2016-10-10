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

double MemInfo::truncate(double number) {
    return (int)number +(((int)((number - (int)number)*10.))/10.);
}

double MemInfo::KbTOGiB(unsigned long number) {
    return truncate(number/1024./1024.);
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

double MemInfo::getMemUsedPerct(void)  {
    return truncate((double)getMemUsed()/getMemTotal() * 100);
}

double MemInfo::getSwapUsedPerct(void)  {
    return truncate((double)getSwapUsed()/getSwapTotal() * 100);
}

double MemInfo::getMemTotalGiB(void) {
    return KbTOGiB(getMemTotal());
}

double MemInfo::getMemAvailableGiB(void) {
    return KbTOGiB(getMemAvailable());
}

double MemInfo::getMemUsedGiB(void) {
    return KbTOGiB(getMemUsed());
}

double MemInfo::getSwapTotalGiB(void) {
    return KbTOGiB(getSwapTotal());
}

double MemInfo::getSwapFreeGiB(void) {
    return KbTOGiB(getSwapFree());
}

double MemInfo::getSwapUsedGiB(void) {
    return KbTOGiB(getSwapUsed());
}

void MemInfo::memInfoUpdate(void) {
    memInfoSearch();
    memRamCalc();
}
