#include "data.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
/*
初始化DataFile的相关参数
*/

HDataFile::HDataFile()
{  
    m_nCount = 0;//记录文件打开的次数
    m_wRec = 1;//偏移？？
    m_szFile = "";//文件名称
    m_nFileType = 0;
    m_nFileFD = (int)-1;
    m_hHeader.btMagic[0] = 'H';//文件头
    m_hHeader.btMagic[1] = 'W';
    m_hHeader.btVersion[0] = 0x01;
    m_hHeader.btVersion[1] = 0x00;
    m_hHeader.btType = 0;
    m_hHeader.wTotal = 0;
    m_hHeader.wTypeLen = 0;
    m_hHeader.wReserved = 0;
    m_hHeader.wReserved1 = 0;

}

HDataFile::HDataFile(QString szFile)
{
    m_nCount = 0;//记录文件打开的次数
    m_wRec = 1;//偏移？？
    m_szFile = "";//文件名称
    m_nFileType = 0;

    m_hHeader.btMagic[0] = 'H';//文件头
    m_hHeader.btMagic[1] = 'W';
    m_hHeader.btVersion[0] = 0x01;
    m_hHeader.btVersion[1] = 0x00;
    m_hHeader.btType = 0;
    m_hHeader.wTotal = 0;
    m_hHeader.wTypeLen = 0;
    m_hHeader.wReserved = 0;
    m_hHeader.wReserved1 = 0;
    m_szFile = szFile;
}

HDataFile::HDataFile(const HDataFile& df)
{
    m_nFileType = df.m_nFileType;
    m_nCount = df.m_nCount;
    m_wRec = df.m_wRec;
    m_szFile = df.m_szFile;
    memcpy(&m_hHeader,&df.m_hHeader,HEADER_SIZE);
}

HDataFile::~HDataFile()
{
    closeDataFile();
}

const HDataFile& HDataFile::operator =(const HDataFile& df)
{
    m_nFileType = df.m_nFileType;
    m_nCount = df.m_nCount;
    m_wRec = df.m_wRec;
    m_szFile = df.m_szFile;
    memcpy(&m_hHeader,&df.m_hHeader,HEADER_SIZE);

    return *this;
}

bool HDataFile::operator ==(const HDataFile& other )const
{
    bool bResult = true;
    if(m_nFileType != other.m_nFileType || m_nCount != other.m_nCount ||  m_wRec != other.m_wRec || m_szFile != other.m_szFile)
        bResult = false;
    if(m_hHeader.btMagic[0] != other.m_hHeader.btMagic[0] || m_hHeader.btMagic[1] != other.m_hHeader.btMagic[1] ||
    m_hHeader.btVersion[0] != other.m_hHeader.btVersion[0] || m_hHeader.btVersion[1] != other.m_hHeader.btVersion[0] ||
    m_hHeader.btType != other.m_hHeader.btType || m_hHeader.wTotal != other.m_hHeader.wTotal || m_hHeader.wTypeLen != other.m_hHeader.wTypeLen)
        bResult = false;
    return bResult;
}

void HDataFile::getDataFileHeader(DATAFILEHEADER *pHeader)
{
    memcpy(pHeader,&m_hHeader,HEADER_SIZE);
}

void HDataFile::setDataFileHeader(DATAFILEHEADER *pHeader)
{
    memcpy(&m_hHeader,pHeader,HEADER_SIZE);
    /*if(!file.isOpen())
    {
        file.open(QIODevice::ReadWrite);
    }*/
    bool b = file.isOpen();
    file.reset();
    file.seek(0);
    file.write((char*)&m_hHeader,HEADER_SIZE);
    file.flush();
}

int HDataFile::createDataFile(QString strName)
{
    if(strName.isEmpty())
        return false;
    m_szFile = strName;
    /*file.setFileName(m_szFile);
    if(QFile::exists(m_szFile)) //如果文件存在 就不管了
        return true;
    if(!file.open(QIODevice::ReadWrite)) //否则创建文件
        return false;
    file.read((char*)&m_hHeader,HEADER_SIZE);
    if('H' != m_hHeader.btMagic[0] || 'W' != m_hHeader.btMagic[1])
    {
        return false;
    }*/
    char szFile[256];
    qstrcpy(szFile,strName.toLocal8Bit().data());
    m_pFP = fopen(szFile,"wb+");
    if(m_pFP == NULL)
        return (int)-1;
    m_nFileFD = fileno(m_pFP);
    if(fwrite(&m_hHeader,HEADER_SIZE,1,m_pFP) != 1)
        return (int)-1;
    return m_nFileFD;
}

int HDataFile::openDataFile(QString strName)
{
    if(strName.isEmpty())
        return false;
    m_szFile = strName;
    /*file.setFileName(m_szFile);
    if(!QFile::exists(m_szFile)) //打开文件，如果文件不存在，就false
        return false;
    if(!file.open(QIODevice::ReadWrite))//否则打开文件，获取header
        return false;
    file.read((char*)&m_hHeader,HEADER_SIZE);
    if('H' != m_hHeader.btMagic[0] || 'W' != m_hHeader.btMagic[1])
    {
        return false;
    }
    return true;*/
    char szFile[256];
    qstrcpy(szFile,strName.toLocal8Bit().data());
    m_pFP = fopen(szFile,"wb+");
    if(m_pFP == NULL)
        return (int)-1;
    m_nFileFD = fileno(m_pFP);
    fread(&m_hHeader,HEADER_SIZE,1,m_pFP);
    if('H' != m_hHeader.btMagic[0] || 'W' != m_hHeader.btMagic[1])
    {
        return (int)-1;
    }
    return m_nFileFD;
}

bool HDataFile::deleteDataFile(QString szFile)
{
    bool bRemove = false;
    if(QFile::exists(szFile))
    {
        bRemove = QFile::remove(szFile);
    }
    return bRemove;
}

void HDataFile::closeDataFile()
{
    if((int)-1 != m_nFileFD)
    {
        fclose(m_pFP);
    }
    m_nFileFD = (int)-1;
    m_szFile = "";
}


#define  min(a,b) (((a) < (b)) ? (a) : (b))
int HDataFile::loadRecord(int wRec,char* pBuffer,int uLength)
{
    if((int)-1 == uLength)
        uLength = m_hHeader.wTypeLen;

    int wRecTemp = (0 == wRec)? m_wRec:wRec;//m_wRec就在这个地方有用
    if(wRecTemp > m_hHeader.wTotal)
        return;
    if(0 == wRec)
        wRec = m_wRec++;
    else
        m_wRec = wRec+1;
    wRec--;
    int length = HEADER_SIZE + wRec * m_hHeader.wTypeLen;
    if(fseek(m_pFP,length,0) != 0)
        return (int)-1;

    fread(pBuffer,min(uLength,m_hHeader.wTypeLen),1,m_pFP);
    return 0;
}

int HDataFile::saveRecord(int wRec,char* pBuffer,int uLength)
{
    if((int)-1 == uLength)
        uLength = m_hHeader.wTypeLen;


    if(0 == wRec)
        wRec = m_wRec++;
    else
        m_wRec = wRec+1;

    //这样做的目的是上层传过来的是从1开始的，保存是从0开始的
    wRec--;
    int length = HEADER_SIZE + wRec * m_hHeader.wTypeLen;
    if(fseek(m_pFP,length,0) != 0)
        return (int)-1;

    fwrite(pBuffer,min(uLength,m_hHeader.wTypeLen),1,m_pFP);
    return 0;
}


