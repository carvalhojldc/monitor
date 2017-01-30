#include <iostream>
#include <unistd.h>
#include "meminfo.h"

int main(void)
{
    MemInfo *mem = new MemInfo();

    for(int i=0; i<10; i++) {
        mem->memInfoUpdate();

        std::cout << "Mem used = " << mem->getMemUsedPerct() << " % ( " \
                  << mem->getMemUsed()/1024. << " MB )" << std::endl;
        std::cout << "Swap used = " << mem->getSwapUsedPerct() << " %" << std::endl;

        std::cout << std::endl;

        sleep(1);
    }

    return 0;
}
