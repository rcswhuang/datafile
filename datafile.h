#ifndef _DATAFILE_H_
#define _DATAFILE_H_
#include "data.h"
//qt 中导出函数

class HDataFileList
{
public:
    HDataFileList();
    ~HDataFileList();

public:
    void freeDataFileList();

    int createDBFile(QString strFile);
    int openDBFile(QString strFile);
    void closeDBFile(int fd);// fd

    int createDataFile(int nFileType,QString szFile);
    int openDataFile(int nFileType,QString szFile);
    void closeDataFile(int nFileType);

    int loadDataFileHeader(int fd,DATAFILEHEADER* pHeader);
    int saveDataFileHeader(int fd,DATAFILEHEADER* pHeader);
    //int loadDataFileRecord(int fd, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );
    int loadDbRecord(int nFileType, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );
    int saveDbRecord(int nFileType, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );
    int loadDataFileRecord(int fd, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );
    int saveDataFileRecord(int fd, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );

protected:
    HDataFile* findDataFile(QString szFile);
    HDataFile* findDataFile(int fd);
    HDataFile* findDataFileByType(int nFileType);

private:
    QList<HDataFile*> m_pDataFileList;
};


#endif
