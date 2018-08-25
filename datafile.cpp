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

HDataFile* HDataFileList::findDataFile(int nFileType)
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

HDataFile* HDataFileList::findDataFile(QString szFile)
{
    HDataFile *pFile = NULL;
    for(int i = 0; i < m_pDataFileList.count();i++)
    {
        pFile = (HDataFile*)m_pDataFileList[i];
        if(pFile->getFileName() == szFile)
            return pFile;
    }
    return NULL;
}

int HDataFileList::createDataFile(int nFileType,QString szFile)
{
    HDataFile *pFile = findDataFile(szFile);
    if(pFile != NULL)
    {
        pFile->closeDataFile();
        pFile->deleteDataFile(szFile);//first del exist file
        //return false;
    }
    pFile = new HDataFile(szFile);
    if(NULL == pFile)
        return (int)-1;
    pFile->setFileName(szFile);
    pFile->setFileType(nFileType);
    int fd = pFile->createDataFile(szFile);
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
    return true;
}

//
bool HDataFileList::openDataFile(int nFileType,QString szFile)
{
    HDataFile *pFile = findDataFile(szFile);
    if(pFile != NULL)
    {
        return true;
    }

    pFile = new HDataFile(szFile);
    if(NULL == pFile)
        return false;

    pFile->setFileName(szFile);
    pFile->setFileType(nFileType);
    bool bOk = pFile->openDataFile(szFile);
    if(!bOk)
    {
        delete pFile;
        return false;
    }

    m_pDataFileList.append(pFile);//需要测试
    return true;
}

void HDataFileList::closeDataFile(int nFileType)
{
    HDataFile *pFile = findDataFile(nFileType);
    if(pFile == NULL)
    {
        return;
    }
    pFile->closeDataFile();

}

bool HDataFileList::loadDataFileHeader(QString szFile,DATAFILEHEADER* pHeader)
{
    HDataFile* pFile = NULL;
    pFile = findDataFile(szFile);
    if(!pFile)
        return false;
    pFile->getDataFileHeader(pHeader);
    return true;
}

bool HDataFileList::saveDataFileHeader(QString szFile,DATAFILEHEADER* pHeader)
{
    HDataFile* pFile = NULL;
    pFile = findDataFile(szFile);
    if(!pFile)
        return false;
    pFile->setDataFileHeader(pHeader);
    return true;
}

bool HDataFileList::loadDataFileRecord(QString szFile, quint16 wRec, char * pBuffer, quint32 uLength )
{
    HDataFile *pFile = NULL;
    pFile = findDataFile(szFile);
    if(!pFile)
        return false;
    pFile->loadRecord(wRec,pBuffer,uLength);
    return true;
}

bool HDataFileList::saveDataFileRecord(QString szFile, quint16 wRec, char * pBuffer, quint32 uLength )
{
    HDataFile *pFile = NULL;
    pFile = findDataFile(szFile);
    if(!pFile)
        return false;
    pFile->saveRecord(wRec,pBuffer,uLength);
    return true;
}




	
	
	
	
	
	
	
	
	
	
	
	
	
