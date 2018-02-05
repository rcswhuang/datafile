#include "datafilehandle.h"
#include "publicdata.h"
#include <QCoreApplication>
#include <QDir>

QString strDataFilePath[DFPATH_LAST + 1];
QString szExecutePath;
QString szSystemPath;
#define MAX_PATH 1024
//ini文件中存放路径位置的KEY
QString strSettingPath[DFPATH_LAST + 1] =
{
    "DATAFILEPATH" ,
    "GRAPHPATH",
    "SYMBOLPATH",
    "BITMAPPATH"
    "MACROPATH"
    "MEDIAPATH",
    "OPERATETICKETPATH",
    "WORKNOTEPATH",
    "EVENTPATH",
    "REPORTPATH",
    "SIGNPADPATH",
    "FILPATH",
    "INIPATH",  //ini文件
};

//如果ini中没有对应的Key则取默认
QString strDefaultPath[DFPATH_LAST + 1] =
{
    "DATA",
    "GRAPH",
    "SYMBOL",
    "BITMAP",
    "MACRO",
    "MEDIA",
    "OPNOTE",
    "WORKNOTE",
    "EVENT",
    "REPORT",
    "SIGNPAD",
    "FIL",
    "INI",
    "PLUGIN"
};

int nFiles[ FILE_TYPE_LAST + 1 ];

int getFileTypeSize(int nFileType)
{
    int nSize = (int)-1;
    if(nFileType == FILE_TYPE_STATION)
        nSize = sizeof(STATION);
    else if(nFileType == FILE_TYPE_DIGITAL)
    {
        nSize = sizeof(DIGITAL);
    }
    else if(nFileType == FILE_TYPE_ANALOGUE)
    {
        nSize = sizeof(ANALOGUE);
    }
    else if(nFileType == FILE_TYPE_EQUIPMENTGROUP)
    {
        nSize = sizeof(EQUIPMENTGROUP);
    }
    else if(nFileType == FILE_TYPE_EQUIPMENT)
    {

    }
    else if(nFileType == FILE_TYPE_POWERGRADE)
    {
        nSize = sizeof(POWERGRADE);
    }
    else if(nFileType == FILE_TYPE_POINTTERM)
    {
        nSize = sizeof(POINTTERM);
    }
    else if(nFileType == FILE_TYPE_LOCKTYPE)
    {
        nSize = sizeof(WFLOCKTYPE);
    }
    else if(nFileType == FILE_TYPE_GLOSSARY)
    {
        nSize = sizeof(GLOSSARY);
    }
    else if(nFileType == FILE_TYPE_GLOSSARYGROUP)
    {
        nSize = sizeof(GLOSSARYGROUP);
    }
    else if(nFileType == FILE_TYPE_DIGITALLOCKNO)
    {
        nSize = sizeof(DIGITALLOCKNO);
    }
    return nSize;
}


HDataFileHandle* HDataFileHandle::m_pInstance = NULL;
HDataFileHandle* HDataFileHandle::Instance()
{
    if(!m_pInstance)
    {
        m_pInstance = new HDataFileHandle;
        m_pInstance->setDataFilePath();
    }

    return m_pInstance;
}

HDataFileHandle::HDataFileHandle()
{
}


//这个函数需要在任何模块启动之前调用，所以放在List的构造函数里面
void HDataFileHandle::setDataFilePath()
{
    //获取文件对应文件夹的路径 d:/wf/bin
    QString strDirPath = QCoreApplication::applicationDirPath();
    QString strAppPath = strDirPath.left(strDirPath.lastIndexOf("/"));
    char szTemp[MAX_PATH]="";
    for(int i = 0; i <= DFPATH_LAST;i++)
    {
        //先获取存在的路径
        QString strTemp;
        if(0 == qstrlen(szTemp))
        {
            strTemp = strAppPath + "/" + strDefaultPath[i];
        }
        else
        {
            strTemp = szTemp;
        }
        strDataFilePath[i] = strTemp;
    }
}

void  HDataFileHandle::getDataFilePath(int nPath,char* filename)
{
    if(DFPATH_EXECUTE == nPath)//bin路径
    {
        QString tmp = szExecutePath;
        QByteArray text = tmp.toLocal8Bit();
        char *data = new char[text.size() + 1];
        qstrcpy(filename,data);
        delete [] data;
    }
    else if(DFPATH_SYSTEM == nPath)//系统路径
    {
        QString tmp = szSystemPath;
        QByteArray text = tmp.toLocal8Bit();
        char *data = new char[text.size() + 1];
        qstrcpy(filename,data);
        delete [] data;
    }
    else if(0 <= nPath && nPath <= DFPATH_LAST)//各种文件夹路径
    {
        qstrcpy(filename,strDataFilePath[nPath].toLocal8Bit().data());
        //QString strname = QString(filename);
    }
   // return true;
}

bool HDataFileHandle::getDataFileName(int nFileType,char* pBuffer)
{
    if(NULL == pBuffer)
        return false;

    QString strFile;
    switch(nFileType)
    {
        case FILE_TYPE_STATION:
                strFile = "wfstation.dat";
                break;
        case FILE_TYPE_DIGITAL:
                strFile = "wfdigit.dat";
                break;
        case FILE_TYPE_ANALOGUE:
                strFile = "wfanalog.dat";
                break;
        case FILE_TYPE_EQUIPMENTGROUP:
                strFile = "wfequipmentgroup.dat";
                break;
        case FILE_TYPE_EQUIPMENT:
                strFile = "wfequipment.dat";
                break;
        case FILE_TYPE_POWERGRADE:
                strFile = "wfpowergrade.dat";
                break;
        case FILE_TYPE_POINTTERM:
                strFile = "wfpointterm.dat";
                break;
        case FILE_TYPE_LOCKTYPE:
                strFile = "wflocktype.dat";
                break;
        case FILE_TYPE_OPERATERULE:
                strFile = "wfOperteRule.dat";
                break;
        case FILE_TYPE_OPERATETICKETHEAD:
                strFile = "wfOperateTicketHead.dat";
                break;
        case FILE_TYPE_RELAY:
                strFile = "wfRelay.dat";
                break;
        case FILE_TYPE_GLOSSARY:
                strFile = "wfglossary.dat";
                break;
        case FILE_TYPE_GLOSSARYGROUP:
                strFile = "wfglossarygroup.dat";
                break;
        case FILE_TYPE_EVENTTICKETDATA:
                strFile = "wfEventTicketData.dat";
                break;
        case FILE_TYPE_REPORTHEAD:
                strFile = "wfReportHead.dat";
                break;
        case FILE_TYPE_WORKNOTEHEAD:
                strFile = "wfWorkNoteHead.dat";
                break;
        case FILE_TYPE_REPORT:
                strFile = "wfReport.dat";
                break;
        case FILE_TYPE_MEASURE:
                strFile = "wfmeasure.dat";
                break;
        case FILE_TYPE_LIMIT:
                strFile = "wflimit.dat";
                break;
        case FILE_TYPE_SYMBOL:
                strFile = "wfsymbol.dat";
                break;
        case FILE_TYPE_PASSWD:
                strFile = "wfpassword.dat";
                break;
        case FILE_TYPE_FORMULA:
                strFile = "wfformula.dat";
                break;
        case FILE_TYPE_ITEM:
                strFile = "wfitem.dat";
                break;
        case FILE_TYPE_GRAPHDB:
                strFile = "graph.dat";
                break;
        case FILE_TYPE_STATECHANGEINFO:
                strFile = "wfstatechangeinfo.dat";
                break;
        case FILE_TYPE_DIGITALLOCKNO:
                strFile = "wfdigitallockno.dat";
                break;
        case FILE_TYPE_DIGITALEXT:
                strFile = "wfditialfromut.dat";
                break;
        case FILE_TYPE_STEPJDX:
                strFile = "wfstepjdx.dat";
                break;
        case FILE_TYPE_ANALOGEXT:
                strFile = "wfanalogext.dat";
                break;
        case FILE_TYPE_JDPAD:
                strFile = "wfjdxpad.dat";
                break;
        case FILE_TYPE_OPWF:
                strFile = "wfonepointwf.dat";
                break;
        default:
                strFile = "";
                break;
    }
    if(strFile.isEmpty())
    {
            *pBuffer = 0;
            return false;
    }

    char szFileName[MAX_PATH];
    getDataFilePath(DFPATH_DATA,szFileName);
    qstrcpy(pBuffer,szFileName);//文件路径
    QDir dir;
    if(!dir.exists(szFileName))
    {
        if(!dir.mkpath(szFileName))
            return false;
    }
    strcat(pBuffer,"/");
    strcat(pBuffer,strFile.toLocal8Bit().data());
    return true;
}
///////////////////////////////////////////////////////////////////////////////////



/*
void initDbRecord(quint32 uFileType,void* pRecord)
{
    if ( FILE_TYPE_STATION == uFileType )
    {
        StructStation* pStation = (StructStation*)pRecord;
        memset( pStation, 0, sizeof(StructStation) );
    }
    else if ( FILE_TYPE_ANALOG == uFileType )
    {
        StructAnalogue* pAnalogue = (StructAnalogue*)pRecord;
        memset( pAnalogue, 0, sizeof(StructAnalogue) );
    }
    else if ( FILE_TYPE_DIGITAL == uFileType )
    {
        StructDigital* pDigital = (StructDigital*)pRecord;
        memset( pDigital, 0, sizeof(StructDigital) );
    }
    else if (FILE_TYPE_RELAY == uFileType)
    {
        RELAY* pRelay=(RELAY*)pRecord;
        memset(pRelay,0,sizeof(RELAY));
    }
    else if ( FILE_TYPE_EquipmentGroup == uFileType )
    {
        StructEquipmentGroup* pData = (StructEquipmentGroup*)pRecord;
        memset( pData, 0, sizeof(StructEquipmentGroup) );
    }
    else if ( FILE_TYPE_PowerGrade == uFileType )
    {
        StructPowerGrade* pData = (StructPowerGrade*)pRecord;
        memset( pData, 0, sizeof(StructPowerGrade) );
    }
    else if ( FILE_TYPE_PointTerm == uFileType )
    {
        StructPointTerm* pData = (StructPointTerm*)pRecord;
        memset( pData, 0, sizeof(StructPointTerm) );
    }
    else if ( FILE_TYPE_PointTermGlossary == uFileType )
    {
        StructPointTermGlossary* pData = (StructPointTermGlossary*)pRecord;
        memset( pData, 0, sizeof(StructPointTermGlossary) );
    }
    else if ( FILE_TYPE_REPORTHEAD == uFileType )
    {
        StructReportInfo* pReportInfo = (StructReportInfo*)pRecord;
        memset( pReportInfo, 0, sizeof(StructReportInfo) );
    }
    else if ( FILE_TYPE_WORKNOTEHEAD == uFileType )
    {
        StructWorknoteInfo* pWorknoteInfo = (StructWorknoteInfo*)pRecord;
        memset( pWorknoteInfo, 0, sizeof(StructWorknoteInfo) );
    }
    else if ( FILE_TYPE_REPORT == uFileType )
    {
        StructFrontDef* pReport = (StructFrontDef*)pRecord;
        memset( pReport, 0, sizeof(StructFrontDef) );
    }
    else if ( FILE_TYPE_LockType == uFileType )
    {
        StructLockType* pData = (StructLockType*)pRecord;
        memset( pData, 0, sizeof(StructLockType) );
    }
    else if ( FILE_TYPE_OperateRule ==uFileType)
    {
        StructOperateRule* pData = (StructOperateRule*)pRecord;
        memset( pData, 0, sizeof(StructOperateRule) );
    }
    else if ( FILE_TYPE_OperateTicketHead ==uFileType)
    {
        StructOperateTicketHead* pData = (StructOperateTicketHead*)pRecord;
        memset( pData, 0, sizeof(StructOperateTicketHead) );
    }
    else if ( FILE_TYPE_MEASURE == uFileType )
    {
        //MEASURE* pMeasure = (MEASURE*)pRecord;
        //memset( pMeasure, 0, sizeof(MEASURE) );
        //pMeasure->wNo = (WORD)-1;
    }
    else if ( FILE_TYPE_LIMIT == uFileType )
    {
        //LIMIT* pLimit = (LIMIT*)pRecord;
        //memset( pLimit, 0, sizeof(LIMIT) );
        //pLimit->wNo = (WORD)-1;
    }
    else if ( FILE_TYPE_GRAPHDB == uFileType )
    {
        //GRAPHINFO* pGraphInfo = (GRAPHINFO*)pRecord;
        //memset( pGraphInfo, 0, sizeof(GRAPHINFO) );
        //pGraphInfo->btType = NORMAL_GRAPH;
        //pGraphInfo->nPYear = 1995;
        //pGraphInfo->nPMonth = 2;
        //pGraphInfo->nPDay = 23;
        //pGraphInfo->wFormula = (WORD)-1;
    }
    else if ( FILE_TYPE_FORMULA == uFileType )
    {
        //FORMULA* pFormula = (FORMULA*)pRecord;
        //memset( pFormula, 0, sizeof(FORMULA) );
        //pFormula->wNo = (WORD)-1;
        //pFormula->wMessage = (WORD)-1;
    }
    else if ( FILE_TYPE_ITEM == uFileType )
    {
        //ITEM* pItem = (ITEM*)pRecord;
        //memset( pItem, 0, sizeof(ITEM) );
        //pItem->btType = ITEM_NULL;
    }
    else if( FILE_TYPE_StateChangeInfo == uFileType )//{{tengjy add for SUBQ00013349 20050906//}}
    {
        StructStateChangeInfo* pData = (StructStateChangeInfo*)pRecord;
        memset( pData, 0, sizeof(StructStateChangeInfo) );
    }
    else if( FILE_TYPE_WfDigitalLockNo == uFileType )
    {
        StructWfDigitalLockNo* pData = (StructWfDigitalLockNo*)pRecord;
        memset( pData, 0, sizeof(StructWfDigitalLockNo) );
    }
    else if( FILE_TYPE_DIGITALEXT == uFileType )
    {
        StructDigitalExt* pData = (StructDigitalExt*)pRecord;
        memset( pData, 0, sizeof(StructDigitalExt) );
    }
    else if( FILE_TYPE_STEPJDX == uFileType )//{{2006-12-22 by tengjy for SUBQ00027624//}}
    {
        StructStepJDPadInfo* pData = (StructStepJDPadInfo*)pRecord;
        memset( pData, 0, sizeof(StructStepJDPadInfo) );
    }
    else if( FILE_TYPE_JDPAD == uFileType )
    {
        StructJDXPad* pData = (StructJDXPad*)pRecord;
        memset( pData, 0, sizeof(StructJDXPad) );
    }
    else if(FILE_TYPE_OPWF == uFileType)
    {
        StructOnePointWfOnOff* pData = (StructOnePointWfOnOff*)pRecord;
        memset(pData,0,sizeof(StructOnePointWfOnOff));
    }
}*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getDataFilePath(int nPath,char* filename)
{
    HDataFileHandle *pInstance = HDataFileHandle::Instance();
    if(!pInstance) return;
    pInstance->getDataFilePath(nPath,filename);
}


bool createDB( int nFileType )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
    HDataFileHandle *pInstance = HDataFileHandle::Instance();
    char szFile[MAX_PATH];
    if(!pInstance->getDataFileName(nFileType,szFile))//filetype,filename
        return false;
    bool bOk = pInstance->dataFileList.createDataFile(nFileType,szFile);
    if(!bOk)
        return false;
    return true;
}

bool openDB( int nFileType )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
    HDataFileHandle *pInstance = HDataFileHandle::Instance();
    char szFile[MAX_PATH];
    if(!pInstance->getDataFileName(nFileType,szFile))
        return false;

    bool bOk = pInstance->dataFileList.openDataFile(nFileType,szFile);
    if(!bOk)
        return false;

    DATAFILEHEADER Header;
    pInstance->dataFileList.loadDataFileHeader(szFile,&Header);
    if(Header.btType != nFileType)
    {
        pInstance->dataFileList.closeDataFile(nFileType);
        return false;
    }
    return true;
}

void closeDB( int nFileType )
{
     HDataFileHandle *pInstance = HDataFileHandle::Instance();
    if(nFileType < FILE_TYPE_LAST)
        pInstance->dataFileList.closeDataFile(nFileType);
}

bool loadDataFileHeader( int nFileType, DATAFILEHEADER* pHeader )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
     HDataFileHandle *pInstance = HDataFileHandle::Instance();
   // DATAFILEHEADER Header;
   // if(loadDataFileHeader(nFileType,&Header) != -1 || wSize[uFileType] > Header.wRecLength)
   //     initDbRecord();
     char szFile[MAX_PATH];
     if(!pInstance->getDataFileName(nFileType,szFile))
         return false;
     return pInstance->dataFileList.loadDataFileHeader(szFile,pHeader);
}

bool saveDataFileHeader( int nFileType, DATAFILEHEADER* pHeader )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
     HDataFileHandle *pInstance = HDataFileHandle::Instance();
   // DATAFILEHEADER Header;
   // if(loadDataFileHeader(nFileType,&Header) != -1 || wSize[uFileType] > Header.wRecLength)
   //     initDbRecord();
     char szFile[MAX_PATH];
     if(!pInstance->getDataFileName(nFileType,szFile))
         return false;
     return pInstance->dataFileList.saveDataFileHeader(szFile,pHeader);
}

bool loadDBRecord( int nFileType, quint16 wRec, void* pRecord )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
     HDataFileHandle *pInstance = HDataFileHandle::Instance();
   // DATAFILEHEADER Header;
   // if(loadDataFileHeader(nFileType,&Header) != -1 || wSize[uFileType] > Header.wRecLength)
   //     initDbRecord();
     char szFile[MAX_PATH];
     if(!pInstance->getDataFileName(nFileType,szFile))
         return false;
     int nSize = getFileTypeSize(nFileType);
     return pInstance->dataFileList.loadDataFileRecord(szFile,wRec,(char*)pRecord,(quint32)nSize);
}

bool saveDBRecord( int nFileType, quint16 wRec, void* pRecord )
{
    if(nFileType > FILE_TYPE_LAST)
        return false;
    HDataFileHandle *pInstance = HDataFileHandle::Instance();
    char szFile[MAX_PATH];
    if(!pInstance->getDataFileName(nFileType,szFile))
        return false;
    int nSize = getFileTypeSize(nFileType);
    return pInstance->dataFileList.saveDataFileRecord(szFile,wRec,(char*)pRecord,(quint32)nSize);
}




















