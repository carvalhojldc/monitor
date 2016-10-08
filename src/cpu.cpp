#include "cpu.h"

CPU::CPU() {
    numberCore = sysconf(_SC_NPROCESSORS_ONLN);
}


int CPU::getNumberCore() {
    return numberCore;
}
