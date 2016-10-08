#ifndef CPU_H
#define CPU_H

#include <unistd.h>

class CPU {
private:
    int numberCore;

public:
    CPU();

    int getNumberCore();
};

#endif // CPU_H
