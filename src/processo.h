#ifndef PROCESSO_H
#define PROCESSO_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std;

#define MEMINFO_FILE "/proc/meminfo"
//#define MEMINFO_FILE "/proc/meminfo"
//#define MEMINFO_FILE "/proc/meminfo"

#define BUFFER 100


class Processo {
    private:
        int pid;
        int memoriaRam;
        float porcCPU;
        string usuario;
        string nomeProcesso;

    public:
        void Set_pid(int val){
            pid = val;
        };
        int Get_pid(){
            return pid;
        };
        void Set_memoriaRam(int val){
            memoriaRam = val;
        };
        int Get_memoriaRam(){
            return memoriaRam;
        };
        void Set_porcCPU(int val){
            porcCPU = val;
        };
        int Get_porcCPU(){
            return porcCPU;
        };
        void Set_usuario(string val){
            usuario = val;
        };
        string Get_usuario(){
            return usuario;
        };
        void Set_nomeProcesso(string val){
            nomeProcesso = val;
        };
        string Get_nomeProcesso(){
            return nomeProcesso;
        };

        int* leitura_PID() {

            int Contador_Processos = 0;
            DIR * dir = opendir ( "/proc");
            struct dirent * lsdir;
            while ((lsdir = readdir ( dir ))!= NULL){
                if(atof(lsdir->d_name) != 0 && lsdir->d_type == DT_DIR) {
                    Contador_Processos++;
                }
            }
            closedir ( dir );

            DIR * dirr = opendir ( "/proc");
            int i=0;
            int *V = new int[Contador_Processos];
            while ((lsdir = readdir ( dirr ))!= NULL){
                if(atof(lsdir->d_name) != 0 && lsdir->d_type == DT_DIR) {
                    int pid = atoi(lsdir->d_name);
                    V[i] = pid;
                    i++;
                }
            }
            closedir ( dir );

            return V;
        }

        int Q_PIDS(void){
            int Contador_Processos = 0;
            DIR * dir = opendir ( "/proc");
            struct dirent * lsdir;
            while ((lsdir = readdir ( dir ))!= NULL){
                if(atof(lsdir->d_name) != 0 && lsdir->d_type == DT_DIR) {
                    Contador_Processos++;
                }
            }
            return Contador_Processos;
        }

        void leitura_memoria_processo(void) {

            ifstream txtfile;
            txtfile.open("/proc/9042/mem");
            string a;
            char c;
            while(txtfile.get(c)){
                a += c;
            }

            cout << a << endl;
            //return memoria;
        }

        void leitura_nome_processo(string pid) {
            string caminho = "/proc/" + pid + "/comm";
            //caminho,pid);
            //strcat(caminho,"/comm");
            ifstream txtfile;
            txtfile.open(caminho);
            string a;
            char d;
            while(txtfile.get(d)){
                    a += d;
            }
            //cout << a << endl;

            Set_nomeProcesso(a);
            //return memoria;
        }

        void leitura_usuario(void) {

            ifstream txtfile;
            txtfile.open("/proc/9042/ns/user");
            string a;
            char d;
            while(txtfile.get(d)){
                    a += d;
            }
            cout << a << endl;
            //return memoria;
        }
};





#endif // PROCESSO_H
