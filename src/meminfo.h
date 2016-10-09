/*
 * File: meminfo.h
 *
 * Author: João Leite carvalhojdlc@gmail.com
 *
 * Date: 08-Octuber-2016
 */

/*
File /proc/meminfo
    MemTotal:        2935392 kB   **
    MemFree:          507920 kB   **
    MemAvailable:    1621084 kB
    Buffers:           70748 kB   **
    Cached:          1261428 kB   **
    SwapCached:          260 kB
    Active:          1298444 kB
    Inactive:         812464 kB
    Active(anon):     725668 kB
    Inactive(anon):   241944 kB
    Active(file):     572776 kB
    Inactive(file):   570520 kB
    Unevictable:           0 kB
    Mlocked:               0 kB
    SwapTotal:       5858300 kB   **
    SwapFree:        5837692 kB   **
    Dirty:                40 kB
    Writeback:             0 kB
    AnonPages:        778516 kB
    Mapped:           232012 kB
    Shmem:            188872 kB
    Slab:             259216 kB
    SReclaimable:     223272 kB
    SUnreclaim:        35944 kB
    KernelStack:        6176 kB
    PageTables:        22152 kB
    NFS_Unstable:          0 kB
    Bounce:                0 kB
    WritebackTmp:          0 kB
    CommitLimit:     7325996 kB
    Committed_AS:    3482236 kB
    VmallocTotal:   34359738367 kB
    VmallocUsed:      348456 kB
    VmallocChunk:   34359382704 kB
    HardwareCorrupted:     0 kB
    AnonHugePages:         0 kB
    HugePages_Total:       0
    HugePages_Free:        0
    HugePages_Rsvd:        0
    HugePages_Surp:        0
    Hugepagesize:       2048 kB
    DirectMap4k:       51136 kB
    DirectMap2M:     3006464 kB
*/

#ifndef MEMINFO_H
#define MEMINFO_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <QDebug>

#define MEM_INFO_FILE "/proc/meminfo"
#define MEM_BUFFER 50

class MemInfo {
private:
	unsigned long memRam;

    unsigned long memTotal;
    unsigned long memAvailable;
    unsigned long memFree;
    unsigned long buffers;
    unsigned long cached;
	unsigned long swapTotal;
	unsigned long swapFree;

    void memInfoSearch(void);
    void memRamCalc(void);

    double truncate(double number);
    double KbTOGiB(unsigned long number);
	
public:
    MemInfo();
	~MemInfo();

    unsigned long getMemTotal(void) const;
    unsigned long getMemAvailable(void) const;
    unsigned long getMemUsed(void) const;

	unsigned long getSwapTotal(void) const;
	unsigned long getSwapFree(void) const;
	unsigned long getSwapUsed(void) const;

    double getMemUsedPerct(void) ;
    double getSwapUsedPerct(void) ;

    double getMemTotalGiB(void);
    double getMemAvailableGiB(void);
    double getMemUsedGiB(void);

    double getSwapTotalGiB(void);
    double getSwapFreeGiB(void);
    double getSwapUsedGiB(void);


    void memInfoUpdate(void);



};

#endif /* MEMINFO_H */
