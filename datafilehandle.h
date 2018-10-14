#ifndef DATAFILEHANDLE_H
#define DATAFILEHANDLE_H
#include "data.h"
#include "datafile.h"
#include <QString>

class HDataFileHandle
{
public:
    HDataFileHandle();
public:
    void initDataFilePath();
    int  getFileTypeSize(int nFileType);
    void getDataFilePath(int nPath,QString& path);
    bool getDataFileName(int nFileType,QString& file);

public:
    HDataFileList dataFileList;
};

#endif // DATAFILEHANDLE_H
