#include <iostream>
#include "cpu.h"

int main(void)
{
    CPU *cpu = new CPU();

    for(int j=0; j<10; j++) {
        cpu->updateCPU();

        for(int i=0; i<=cpu->getNumberCore(); i++) {
            if(i==0)
                std::cout << "CPU = " << cpu->getPerctCPU(i) << " % " << std::endl;
            else
                std::cout << "CPU" << i << " = " << cpu->getPerctCPU(i) << " % " << std::endl;
        }
        std::cout << std::endl;
        sleep(1);
    }

    return 0;
}
