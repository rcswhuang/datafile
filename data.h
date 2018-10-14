#ifndef _DATA_H_
#define _DATA_H_
#include <QFile>
#include "hfileapi.h"

/*
|   |------------------|
|   |  DATAFILEHEADER  |
|   |                  |
|   |  StructXXXX      |
|   |  StructXXXX      |
*/

/*
 * 1.打开某类型文件，注意这类文件所有元素都存在此文件 比如厂站遥信遥测等文件，所有都存在对应文件内
 * 2.打开某文件，注意这类文件只是存放1个实际文件，比如操作票文件，这种文件是1个操作票对应1个文件
*/
class HDataFile
{
public:
    HDataFile();
    ~HDataFile();

protected:
    int m_nFileFD; //文件描述符
    int m_nFileType;//记录文件
    int m_nCount;//记录文件打开的次数
    quint16 m_wRec;//当前已经读取某种数据结构的个数
    QString m_szFile;//文件名称
    DATAFILEHEADER m_hHeader;//文件头
    FILE* m_pFP;
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
