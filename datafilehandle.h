#ifndef DATAFILEHANDLE_H
#define DATAFILEHANDLE_H
#include "publicdata.h"
#include "data.h"
#include "datafile.h"
#include <QString>

class FILE_EXPORT HDataFileHandle
{
public:
    HDataFileHandle();

public:
    static HDataFileHandle* m_pInstance;
    static HDataFileHandle* Instance();
    static void Exinstance();

    int  getFileTypeSize(int nFileType);
    void getDataFilePath(int nPath,char* filename);
    bool getDataFileName(int nFileType,char* pBuffer);

public:
    HDataFileList dataFileList;
};

#endif // DATAFILEHANDLE_H
