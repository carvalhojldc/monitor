/* 
 * File:   Process.h
 * Author: carvalhojldc - carvalhojldc@gmail.com
 *
 * Created on December 28, 2016, 12:55 PM
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <limits.h>

/*
 * Data type for Process
 * 
 */
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

#endif /* PROCESS_H */

