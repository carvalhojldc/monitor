#include <iostream>
#include <unistd.h>
#include "meminfo.h"

using std::cout;
using std::cin;
using std::endl;

double trunca(double value) {
	return (int)value +(((int)((value - (int)value)*10.))/10.);
}

int main() {



	//MemInfo memInfo;
	//cout << memInfo.getMemAvailable() ;
	MemInfo *memInfo = new MemInfo();
	double ram = memInfo->getMemAvailable();
	double tamanho = memInfo->getMemTotal();
	double usaod = memInfo->getMemUsed();

	double su = memInfo->getSwapUsed();

	cout <<  "Tamanho da RAM = " << tamanho/1024./1024. << "GiB" << endl;

	while(1) {
		memInfo->memInfoUpdate();
		usaod = memInfo->getMemUsed();
		ram = memInfo->getMemAvailable();
		su = memInfo->getSwapUsed();
		cout << "Ram disponivel = " << trunca(ram /1024.) << endl;
		cout << "Ram usada = " << trunca(usaod /1024.) << endl;
		cout << "Swap usada = " << trunca(su/1024.) << endl;
		sleep(1);
	}

	return 0;
}
