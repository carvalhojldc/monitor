#include "meminfo.h"

MemInfo::MemInfo() {
    memTotal = 0;
    memAvailable = 0;

    memInfoUpdate();
}

MemInfo::~MemInfo() { }

double MemInfo::truncate(double number) {
    return (int)number +(((int)((number - (int)number)*10.))/10.);
}

int MemInfo::memInfoSearch(void) {
    FILE *file;
    char str[ _POSIX2_LINE_MAX ];
    char *temp;

    if( ( file = fopen(MEM_INFO_FILE, "r") ) == NULL ) {
        return -1;
    }

    while(fgets(str, sizeof(str) , file) != NULL) {
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

    fclose(file);

    memRam = memTotal - (memFree + buffers + cached);
}

int MemInfo::memInfoUpdate(void) {
    if( memInfoSearch() < 0 ) return -1;

    return 1;
}

unsigned long MemInfo::getMemTotal(void) const { return memTotal; }
unsigned long MemInfo::getMemAvailable(void) const { return (memTotal - memRam); }
unsigned long MemInfo::getMemUsed(void) const { return memRam; }

unsigned long MemInfo::getSwapTotal(void) const { return swapTotal; }
unsigned long MemInfo::getSwapFree(void) const { return swapFree; }
unsigned long MemInfo::getSwapUsed(void) const { return (swapTotal - swapFree); }

double MemInfo::getMemUsedPerct(void) { return truncate((double)getMemUsed()/getMemTotal() * 100); }
double MemInfo::getSwapUsedPerct(void) { return truncate((double)getSwapUsed()/getSwapTotal() * 100); }
