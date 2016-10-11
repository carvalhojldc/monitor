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
#include <string>

using namespace std;

#define MEMINFO_FILE "/proc/meminfo"
//#define MEMINFO_FILE "/proc/meminfo"
//#define MEMINFO_FILE "/proc/meminfo"

#define BUFFER 100


class Processo {
    private:
        int pid;
        float memoriaRam;
        int prioridade;
        string usuario;
        string nomeProcesso;

    public:
        void Set_pid(int val){
            pid = val;
        };
        int Get_pid(){
            return pid;
        };
        void Set_memoriaRam(float val){
            memoriaRam = val;
        };
        float Get_memoriaRam(){
            return memoriaRam;
        };
        void Set_prioridade(int val){
            prioridade = val;
        };
        int Get_prioridade(){
            return prioridade;
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
            closedir(dir);
        }

        void leitura_memoria_processo(string pid) {
        /*    string caminho = "/proc/" + pid + "/stat";
            ifstream txtfile;
            txtfile.open(caminho);
            string M_virtual;
            string M_rss;
            char d;
            int i=0;
            while(txtfile.get(d)){
                if(i==22 && d!=' '){
                    M_virtual += d;    
                }
                if(i==23 && d!=' '){
                    M_rss += d;    
                } 
                if(d == ' '){
                    i++;
                }               
            }
            int M_v; //Memoria virtual
            int M_r; //memoria residente
            int MEMORIA;
            stringstream ss(M_virtual);
            ss >> M_v;
            stringstream sss(M_rss);
            sss >> M_r;*/
            /*
				CAUCULAR MEMORIA USADA ATRAVEZ DA MEMORIA VIRTUAL E RESIDENTE, E ARMAZENAR EM 'MEMORIA'
            */
            //Set_memoriaRam(M_r);
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
            Set_nomeProcesso(a);
            txtfile.close();

        }

        void leitura_usuario(void) {

            ifstream txtfile;
            txtfile.open("/proc/9042/ns/user");
            string a;
            char d;
            while(txtfile.get(d)){
                    a += d;
            }
            txtfile.close();
        }

        void leitura_prioridade(string pid) {
            string caminho = "/proc/" + pid + "/stat";
            ifstream txtfile;
            txtfile.open(caminho);
            string a;
            char d;
            int i=0;
            while(txtfile.get(d)){
                if(i==17 && d!=' '){
                    a += d;    
                } 
                if(d == ' '){
                    i++;
                }               
            }
            int prioridade;
            stringstream ss(a);
            ss >> prioridade;
            Set_prioridade(prioridade);
            txtfile.close();
        }
};





#endif // PROCESSO_H
