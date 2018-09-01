#include "publicdata.h"
#include "datafilehandle.h"
#include "data.h"
#include "datafile.h"
#include <QCoreApplication>
extern int getFileTypeSize(int nFileType);
class HDataFile;
//////////////////////////////////////HDataFileList/////////////////////////////////////////////
HDataFileList::HDataFileList()
{
}

HDataFileList::~HDataFileList()
{
    freeDataFileList();
}

void HDataFileList::freeDataFileList()
{
    while(!m_pDataFileList.isEmpty())
        delete (HDataFile*)m_pDataFileList.takeFirst();
}

HDataFile* HDataFileList::findDataFile(int fd)
{
    HDataFile *pFile = NULL;
    for(int i = 0; i < m_pDataFileList.count();i++)
    {
        pFile = (HDataFile*)m_pDataFileList[i];
        if(pFile->getFileFD() == fd)
            return pFile;
    }
    return NULL;
}

HDataFile* HDataFileList::findDataFile(QString strFile)
{
    HDataFile *pFile = NULL;
    for(int i = 0; i < m_pDataFileList.count();i++)
    {
        pFile = (HDataFile*)m_pDataFileList[i];
        if(pFile->getFileName() == strFile)
            return pFile;
    }
    return NULL;
}


HDataFile* HDataFileList::findDataFileByType(int nFileType)
{
    HDataFile *pFile = NULL;
    for(int i = 0; i < m_pDataFileList.count();i++)
    {
        pFile = (HDataFile*)m_pDataFileList[i];
        if(pFile->getFileType() == nFileType)
            return pFile;
    }
    return NULL;
}

int HDataFileList::createDBFile(QString strFile)
{
    HDataFile *pFile = findDataFile(strFile);
    if(pFile != NULL)
    {
        pFile->closeDataFile();
        pFile->deleteDataFile(strFile);//first del exist file
    }
    pFile = new HDataFile;
    if(NULL == pFile)
        return (int)-1;
    pFile->setFileName(strFile);
    int fd = pFile->createDataFile(strFile);
    if(fd == (int)-1)
    {
        delete pFile;
        return (int)-1;
    }
    m_pDataFileList.append(pFile);//需要测试
    return fd;
}

int HDataFileList::openDBFile(QString strFile)
{
    HDataFile *pFile = findDataFile(strFile);
    if(pFile != NULL)
    {
        return pFile->getFileFD();
    }

    pFile = new HDataFile;
    if(NULL == pFile)
        return (int)-1;
    pFile->setFileName(strFile);
    int fd = pFile->openDataFile(strFile);
    if(fd == (int)-1)
    {
        delete pFile;
        return (int)-1;
    }
    m_pDataFileList.append(pFile);//需要测试
    return fd;
}

void HDataFileList::closeDBFile(int fd)
{
    HDataFile *pFile = findDataFile(fd);
    if(pFile == NULL)
    {
        return;
    }
    pFile->closeDataFile();
    m_pDataFileList.removeOne(pFile);
}

int HDataFileList::createDataFile(int nFileType,QString strFile)
{
    HDataFile *pFile = findDataFile(strFile);
    if(pFile != NULL)
    {
        pFile->closeDataFile();
        pFile->deleteDataFile(strFile);//first del exist file
    }
    pFile = new HDataFile;
    if(NULL == pFile)
        return (int)-1;
    pFile->setFileName(strFile);
    pFile->setFileType(nFileType);
    int fd = pFile->createDataFile(strFile);
    if(fd == -1)
    {
        delete pFile;
        return (int)-1;
    }
    DATAFILEHEADER header;
    pFile->getDataFileHeader(&header);
    int nSize = getFileTypeSize(nFileType);
    if(header.wTotal == 0 || header.btType != nFileType || header.wTypeLen != nSize)
    {
        header.wTotal = 0;
        header.btType = nFileType;
        header.wTypeLen = nSize;
    }
    pFile->setDataFileHeader(&header);
    m_pDataFileList.append(pFile);//需要测试
    return fd;
}

//
int HDataFileList::openDataFile(int nFileType,QString szFile)
{
    HDataFile *pFile = findDataFile(szFile);
    if(pFile != NULL)
    {
        return pFile->getFileFD();
    }

    pFile = new HDataFile;
    if(NULL == pFile)
        return (int)-1;

    pFile->setFileName(szFile);
    pFile->setFileType(nFileType);
    int fd = pFile->openDataFile(szFile);
    if(fd == (int)-1)
    {
        delete pFile;
        return (int)-1;
    }
    m_pDataFileList.append(pFile);//需要测试
    return fd;
}

void HDataFileList::closeDataFile(int nFileType)
{
    HDataFile *pFile = findDataFileByType(nFileType);
    if(pFile == NULL)
    {
        return;
    }
    pFile->closeDataFile();
    m_pDataFileList.removeOne(pFile);

}

int HDataFileList::loadDataFileHeader(int fd,DATAFILEHEADER* pHeader)
{
    HDataFile* pFile = NULL;
    pFile = findDataFile(fd);
    if(!pFile)
        return (int)-1;
    pFile->getDataFileHeader(pHeader);
    return 0;
}

int HDataFileList::saveDataFileHeader(int fd,DATAFILEHEADER* pHeader)
{
    HDataFile* pFile = NULL;
    pFile = findDataFile(fd);
    if(!pFile)
        return (int)-1;
    pFile->setDataFileHeader(pHeader);
    return 0;
}

int HDataFileList::loadDataFileRecord(int fd, quint16 wRec, char * pBuffer, quint32 uLength )
{
    HDataFile *pFile = NULL;
    pFile = findDataFile(fd);
    if(!pFile)
        return (int)-1;
    DATAFILEHEADER dbHeader;
    pFile->getDataFileHeader(&dbHeader);
    return pFile->loadRecord(wRec,pBuffer,uLength);
}

int HDataFileList::saveDataFileRecord(int fd, quint16 wRec, char * pBuffer, quint32 uLength )
{
    HDataFile *pFile = NULL;
    pFile = findDataFile(fd);
    if(!pFile)
        return (int)-1;
    return pFile->saveRecord(wRec,pBuffer,uLength);
}
