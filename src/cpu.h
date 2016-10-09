#ifndef CPU_H
#define CPU_H

#include <unistd.h>

#include <QDebug>


class CPU {
private:
    int numberCore;

public:
    CPU();

    int getNumberCore() const;
};

#endif // CPU_H
