#include "Processes.h"

Processes::Processes() {
    processData = new ProcessData();
}

Processes::~Processes() {
    delete processData;
}

bool Processes::_searchProcess() {
    DIR * dir;
    struct dirent * lsdir;

    processes.clear();

    if( (dir = opendir ( "/proc") ) == NULL ) {
        return false;
    }

    while ( (lsdir = readdir ( dir ))!= NULL ) {
        if( atof(lsdir->d_name) != 0 && lsdir->d_type == DT_DIR ) {
            processes.push_back( \
                processData->getData( atoi(lsdir->d_name) ) );
        }
    }

    closedir(dir);

    return true;
}

const std::list<Process> Processes::getProcesses() {

    _searchProcess();

    return processes;
}
