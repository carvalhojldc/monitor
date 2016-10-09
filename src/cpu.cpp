#include "cpu.h"

CPU::CPU() {
    numberCore = sysconf(_SC_NPROCESSORS_ONLN);

    //qDebug() << memInfo->getMemAvailable();
}

int CPU::getNumberCore() const {
    return numberCore;
}

