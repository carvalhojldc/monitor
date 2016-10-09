#include <iostream>
#include "cpu.h"
using std::cout;
using std::cin;
using std::endl;

int main() {

	CPU *cpu = new CPU();

	cpu->updateCPU();
	cout << cpu->getNumberCore() << endl;

	while(1) {
		cpu->updateCPU();
		cout << cpu->getPerctCPU(0) << endl;
		cout << cpu->getPerctCPU(1) << endl;
		cout << cpu->getPerctCPU(2) << endl;
		cout << cpu->getPerctCPU(3) << endl;
	}


	return 0;
}
