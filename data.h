#ifndef _DATA_H_
#define _DATA_H_
#include <QFile>
#include "publicdata.h"
//#include "publicfun.h"

/*
|   |------------------|
|   |  DATAFILEHEADER  |
|   |                  |
|   |  StructXXXX      |
|   |  StructXXXX      |
*/

//文件的头结构
//每一种类型的(遥信表、遥测表、其他数据)都有一个datafile对应
//header应该保存这个数据文件的数据个数，及文件需要存储的数据结构长度，这样可以定位或者获取到任何一个数据)
class FILE_EXPORT HDataFile
{
public:
    HDataFile();
    HDataFile(QString szFile);
    HDataFile(const HDataFile& datafile);
    ~HDataFile();

protected:
    int m_nFileFD; //文件描述符
    int m_nFileType;//记录文件
    int m_nCount;//记录文件打开的次数
    quint16 m_wRec;//当前已经读取某种数据结构的个数
    QString m_szFile;//文件名称
    DATAFILEHEADER m_hHeader;//文件头
    QFile file;
    FILE* m_pFP;
public:
   const HDataFile& operator =(const HDataFile&);
   bool operator ==(const HDataFile& other )const;
public:
   int getFileFD(){return m_nFileFD;}
   void setFileType(int nType){m_nFileType = nType;}
   int getFileType(){return m_nFileType;}
   void setFileName(QString strFile){ m_szFile = strFile;}
   QString getFileName(){return m_szFile;}

   void getDataFileHeader(DATAFILEHEADER* pHeader);
   void setDataFileHeader(DATAFILEHEADER* pHeader);

   int createDataFile(QString strFile);//创建文件
   int openDataFile(QString strFile);
   void closeDataFile();
   bool deleteDataFile(QString szFile);

   int loadRecord(int wRec, char* pBuffer, int wLength = (int)-1); //取一个结构
   int saveRecord(int wRec, char* pBuffer, int wLength = (int)-1);
};

#endif
