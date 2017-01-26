/*
 * File:   ProcessData.cpp
 * Author: carvalhojldc - carvalhojldc@gmail.com
 *
 * Created on December 26, 2016, 9:43 AM
 */

#include "ProcessData.h"

ProcessData::ProcessData() {
    process = (Process*)malloc(sizeof(Process));

    /*
     *
     */
    pageSize = sysconf(_SC_PAGESIZE);
}

ProcessData::~ProcessData() {
    free(process);
}

bool ProcessData::_readDetails(unsigned int pid) {
    FILE* pfile = NULL;
    char path[_POSIX_PATH_MAX];

    unsigned int temp;

    snprintf(path, sizeof(path), "/proc/%u/stat", pid);

    if( (pfile = fopen(path, "r")) == NULL ) {
        return false;
    }

                /* 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52*/
    fscanf(pfile, "%u %s %c %d %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u %u", \
            &process->pid, /* 01 pid */
            process->name, /* 02 tcomm */
            &process->state, /* 03 state */
            &process->ppid, /* 04 ppid */
            &temp, /* 05 pgrp */
            &temp, /* 06 sid */
            &temp, /* 07 tty_nr */
            &temp, /* 08 tty_pgrp */
            &temp, /* 09 flags */
            &temp, /* 10 min_flt */
            &temp, /* 11 cmin_flt */
            &temp, /* 12 maj_flt */
            &temp, /* 13 cmaj_flt */
            &temp, /* 14 utime  */
            &temp, /* 15 stime  */
            &temp, /* 16 cutime  */
            &temp, /* 17 cstime  */
            &process->priority, /* 18 priority */
            &process->nice, /* 19 nice */
            &process->numThreads, /* 20 num_threads */
            &temp, /* 21 it_real_value */
            &temp, /* 22 start_time */
            &process->vsz, /* 23 vsize */
            &process->rss, /* 24 rss */
            &temp, /* 25 rsslim */
            &temp, /* 26 start_code */
            &temp, /* 27 end_code */
            &temp, /* 28 start_stack */
            &temp, /* 29 esp */
            &temp, /* 30 eip */
            &temp, /* 31 pending */
            &temp, /* 32 blocked */
            &temp, /* 33 sigign */
            &temp, /* 34 sigcatch */
            &temp, /* 35 0 */
            &temp, /* 36 0 */
            &temp, /* 37 0 */
            &temp, /* 38 exit_signal */
            &temp, /* 39 task_cpu */
            &temp, /* 40 rt_priority */
            &temp, /* 41 policy*/
            &temp, /* 42 blkio_ticks */
            &temp, /* 43 gtime */
            &temp, /* 44 cgtime*/
            &temp, /* 45 start_data */
            &temp, /* 46 end_data */
            &temp, /* 47 start_brk */
            &temp, /* 48 arg_start */
            &temp, /* 49 arg_end */
            &temp, /* 50 env_start*/
            &temp, /* 51 env_end */
            &temp /* 52 exit_code */        );

    fclose(pfile);

    return true;
}

bool ProcessData::_searchData(unsigned int pid) {

    if( !_readDetails(pid) ) {
        return false;
    }

    strcpy(process->name, strtok(process->name, "()"));

    process->rss *= this->pageSize;

    return true;
}

const Process* ProcessData::getStatData(unsigned int pid) {

    _searchData(pid);

    return process;
}
