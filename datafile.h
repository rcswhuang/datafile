#ifndef _DATAFILE_H_
#define _DATAFILE_H_
#include "publicdata.h"
#include "data.h"
//#include "publicfun.h"
//qt 中导出函数

class FILE_EXPORT HDataFileList
{
public:
    HDataFileList();
    ~HDataFileList();

public:
    void freeDataFileList();

    bool createDataFile(int nFileType,QString szFile);
    bool openDataFile(int nFileType,QString szFile);
    void closeDataFile(int nFileType);

    bool loadDataFileHeader(QString szFile,DATAFILEHEADER* pHeader);
    bool saveDataFileHeader(QString szFile,DATAFILEHEADER* pHeader);
    bool loadDataFileRecord(QString szFile, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );
    bool saveDataFileRecord(QString szFile, quint16 wRec, char* pBuffer, quint32 uLength = (quint32)-1 );

protected:
    HDataFile* findDataFile(QString szFile);
    HDataFile* findDataFile(int nFileType);

private:
    QList<HDataFile*> m_pDataFileList;
};

/*
#ifdef __cplusplus
extern "C"
{
#endif

    //文件数据库 对外接口
    bool FILE_EXPORT setDataFilePath();
    const char*   getDataFilePath( int nPath );
    bool FILE_EXPORT getDataFileName(int nFileType,char* pBuffer);

    bool FILE_EXPORT createDB( int uFileType );
    bool FILE_EXPORT openDB( int uFileType );
    void FILE_EXPORT closeDB( int uFileType );

    bool FILE_EXPORT createDataFile(int nFileType,const char* lpszFile );
    bool FILE_EXPORT openDataFile(int nFileType, const char* lpszFile );
    void FILE_EXPORT closeDataFile( int nFileType );

    bool FILE_EXPORT loadDataFileHeader( int nFileType, DATAFILEHEADER* pHeader );
    bool FILE_EXPORT saveDataFileHeader( int nFileType, DATAFILEHEADER* pHeader );
    bool FILE_EXPORT loadDataFileRecord( int nFileType, int wRec, void* pBuffer, int uLength = -1);
    bool FILE_EXPORT saveDataFileRecord( int nFileType, int wRec, void* pBuffer, int uLength = -1 );

    bool FILE_EXPORT loadDBRecord( int uFileType, int wRec, void* pRecord );
    bool FILE_EXPORT saveDBRecord( int uFileType, int wRec, void* pRecord );

	/////////////////////
	//事件
//	BOOL WriteEventToFile(EventData* pEventData);// 将事件写入文件
//	BOOL GetEventDataFile( int nYear,int nMonth,char* szEventFile); //得到事件文件的名称

//	BOOL GetEventTicketDataFile(time_t tEventTime,char* szEventTicketFile); //得到操作票事件文件的名称
//	BOOL WriteEventTicketToFile(time_t tEventTime,EventTicketData* pEventTicketData);// 将操作票事件写入文件
#ifdef __cplusplus
}
#endif*/

#endif
