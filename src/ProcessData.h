/*
 * File:   ProcessData.h
 * Author: carvalhojldc - carvalhojldc@gmail.com
 *
 * Created on December 26, 2016, 9:43 AM
 */

#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

typedef struct {
    char name[_POSIX2_BC_STRING_MAX];
    char state;
    unsigned int pid;
    unsigned int ppid;
    unsigned int rss;
    unsigned int vsz;
    unsigned int priority;
    unsigned int nice;
    unsigned int numThreads;
} Process;

class ProcessData {

private:

    /*
     * type for data of process
     */
    Process* process;

    unsigned int pageSize;


    /*
     * @brief For read data in /proc/[PID]/stat file
     *
     * ***   The stat file  ****
     * contains details information about the process itself.
     * Its fields are explained in Table 1-4.
     *
     *   Table 1-4: Contents of the stat files (as of 2.6.30-rc7)
     *   ..............................................................................
     *       Field          Content
     *     01 pid           process id
     *     02 tcomm         filename of the executable
     *     03 state         state (R is running, S is sleeping, D is sleeping in an
     *                   uninterruptible wait, Z is zombie, T is traced or stopped)
     *     04 ppid          process id of the parent process
     *     05 pgrp          pgrp of the process
     *     06 sid           session id
     *     07 tty_nr        tty the process uses
     *     08 tty_pgrp      pgrp of the tty
     *     09 flags         task flags
     *     10 min_flt       number of minor faults
     *     11 cmin_flt      number of minor faults with child's
     *     12 maj_flt       number of major faults
     *     13 cmaj_flt      number of major faults with child's
     *     14 utime         user mode jiffies
     *     15 stime         kernel mode jiffies
     *     16 cutime        user mode jiffies with child's
     *     17 cstime        kernel mode jiffies with child's
     *     18 priority      priority level
     *     19 nice          nice level
     *     20 num_threads   number of threads
     *     21 it_real_value	(obsolete, always 0)
     *     22 start_time    time the process started after system boot
     *     23 vsize         virtual memory size
     *     24 rss           resident set memory size
     *     25 rsslim        current limit in bytes on the rss
     *     26 start_code    address above which program text can run
     *     27 end_code      address below which program text can run
     *     28 start_stack   address of the start of the main process stack
     *     29 esp           current value of ESP
     *     30 eip           current value of EIP
     *     31 pending       bitmap of pending signals
     *     32 blocked       bitmap of blocked signals
     *     33 sigign        bitmap of ignored signals
     *     34 sigcatch      bitmap of caught signals
     *     35 0		(place holder, used to be the wchan address, use /proc/PID/wchan instead)
     *     36 0             (place holder)
     *     37 0             (place holder)
     *     38 exit_signal   signal to send to parent thread on exit
     *     39 task_cpu      which CPU the task is scheduled on
     *     40 rt_priority   realtime priority
     *     41 policy        scheduling policy (man sched_setscheduler)
     *     42 blkio_ticks   time spent waiting for block IO
     *     43 gtime         guest time of the task in jiffies
     *     44 cgtime        guest time of the task children in jiffies
     *     45 start_data    address above which program data+bss is placed
     *     46 end_data      address below which program data+bss is placed
     *     47 start_brk     address above which program heap can be expanded with brk()
     *     48 arg_start     address above which program command line is placed
     *     49 arg_end       address below which program command line is placed
     *     50 env_start     address above which program environment is placed
     *     51 env_end       address below which program environment is placed
     *     52 exit_code     the thread's exit_code in the form reported by the waitpid system call
     *
     *  Source: THE /proc FILESYSTEM, The Linux Documentation
     *   ..............................................................................
     *
     * @paran pid PID of process
     *
     * @return Success or failure
     *
     */
    bool _readDetails(unsigned int pid);


    /*
     * @brief Control all data searches
     *
     * @paran pid PID of process
     *
     * @return Success or failure
     *
     */
    bool _searchData(unsigned int pid);


public:

    ProcessData();

    ~ProcessData();

    /*
     * @brief return Process type
     *
     * @paran pid PID of process
     *
     * @return Process* data read
     *
     */
    const Process* getStatData(unsigned int pid);

};

#endif /* PROCESS_DATA_H */
