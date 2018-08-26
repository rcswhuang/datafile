#include "datafilehandle.h"
#include "publicdata.h"
#include "hruleeditapi.h"
#include "hformulapi.h"
#include <QCoreApplication>
#include <QDir>

typedef struct _tagDefaultPath
{
    ushort nFileType;
    char*  szPath;
}DEFAULTPATH;

QString strDataFilePath[DFPATH_LAST + 1];
#define MAX_PATH 1024
//如果ini中没有对应的Key则取默认
DEFAULTPATH DefaultPath[] =
{
    //path,id,szPath
    DFPATH_DATA,"data",
    DFPATH_GRAPH,"graph",
    DFPATH_ICON,"icon",
    DFPATH_BITMAP,"bitmap",
    DFPATH_MACRO,"macro",
    DFPATH_MEDIA,"media",
    DFPATH_OPSHEET,"opsheet",
    DFPATH_WORKNOTE,"worknote",
    DFPATH_EVENT,"event",
    DFPATH_REPORT,"report",
    DFPATH_SIGNPAD,"signpad",
    DFPATH_FIL,"fil",
    DFPATH_INI,"ini",
    DFPATH_PLUGIN,"plugin",
    DFPATH_BIN,"bin"
};

int nFiles[ FILE_TYPE_LAST + 1 ];

int getFileTypeSize(int nFileType)
{
    int nSize = (int)-1;
    if(nFileType == FILE_TYPE_STATION)
    {
        nSize = sizeof(STATION);
    }
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
    else if(nFileType == FILE_TYPE_OPTERM)
    {
        nSize = sizeof(OPTERM);
    }
    else if(nFileType == FILE_TYPE_OPTERMGROUP)
    {
        nSize = sizeof(OPTERMGROUP);
    }
    else if(nFileType == FILE_TYPE_DIGITALLOCKNO)
    {
        nSize = sizeof(DIGITALLOCKNO);
    }
    else if(nFileType == FILE_TYPE_RULE)
    {
        nSize = sizeof(RULE);
    }
    else if(nFileType == FILE_TYPE_FORMULA)
    {
        nSize = sizeof(FORMULA);
    }
    else if(nFileType == FILE_TYPE_ITEM)
    {
        nSize = sizeof(ITEM);
    }
    else if(nFileType == FILE_TYPE_OPSHEETINFO)
    {
        nSize = sizeof(OPSHEETINFO);
    }
    else if(nFileType == FILE_TYPE_OPSHEETHEAD)
    {
        nSize = sizeof(OPSHEETSTEP);
    }
    return nSize;
}



HDataFileHandle::HDataFileHandle()
{
}

void HDataFileHandle::initDataFilePath()
{
    //1.在系统目录下面寻找，如果找不到
    //2.在datafile.dll上层目录寻找，然后将wfconfig.ini拷贝到系统目录下
    //3.在wfconfig.ini下面寻找对应路径，
}
void  HDataFileHandle::getDataFilePath(int nPath,QString& path)
{
    path = "";
    if(0 <= nPath && nPath <= DFPATH_LAST)//各种文件夹路径
    {
        path += QString(DefaultPath[nPath].szPath);
    }
}

bool HDataFileHandle::getDataFileName(int nFileType,QString& file)
{
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
        case FILE_TYPE_RULE:
                strFile = "wfrule.dat";
                break;
        case FILE_TYPE_OPSHEETHEAD:
                strFile = "wfopsheethead.dat";
                break;
        case FILE_TYPE_RELAY:
                strFile = "wfrelay.dat";
                break;
        case FILE_TYPE_OPTERM:
                strFile = "wfopterm.dat";
                break;
        case FILE_TYPE_OPTERMGROUP:
                strFile = "wfglossarygroup.dat";
                break;
        case FILE_TYPE_EVENTTICKETDATA:
                strFile = "wfEventTicketData.dat";
                break;
        case FILE_TYPE_OPSHEETINFO:
                strFile = "wfsheet.dat";
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
            return false;
    }

    QString strPath;
    getDataFilePath(DFPATH_DATA,strPath);
    QDir dir;
    if(!dir.exists(strPath))
    {
        if(!dir.mkpath(strPath))
            return false;
    }
    strPath += "/";
    strPath += strFile;
    file = strPath;
    return true;
}
///////////////////////////////////////////////////////////////////////////////////

HDataFileHandle dbfileHandle;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getDataFilePath(int nPath,char* szPath)
{
    QString strPath;
    dbfileHandle.getDataFilePath(nPath,strPath);
    qstrcpy(szPath,strPath.toLocal8Bit().data());
}

int createDB( int nFileType )
{
    if(nFileType > FILE_TYPE_LAST)
        return (int)-1;
    QString strFile;
    if(!dbfileHandle.getDataFileName(nFileType,strFile))//filetype,filename
        return (int)-1;
    int fd = dbfileHandle.dataFileList.createDataFile(nFileType,strFile);
    return fd;
}

int openDB( int nFileType )
{
    if(nFileType > FILE_TYPE_LAST)
        return (int)-1;
    QString strFile;
    if(!dbfileHandle.getDataFileName(nFileType,strFile))//filetype,filename
        return (int)-1;

    int fd = dbfileHandle.dataFileList.openDataFile(nFileType,strFile);
    
    DATAFILEHEADER Header;
    dbfileHandle.dataFileList.loadDataFileHeader(fd,&Header);
    if(Header.btType != nFileType)
    {
        dbfileHandle.dataFileList.closeDataFile(nFileType);
        return (int)-1;
    }
    return fd;
}

void closeDB( int nFileType )
{
    if(nFileType < FILE_TYPE_LAST)
        dbfileHandle.dataFileList.closeDataFile(nFileType);
}

int createDBFile(const char* szFile)
{
    if(szFile == NULL)
        return (int)-1;
    return dbfileHandle.dataFileList.createDBFile(QString(szFile));
}
    
int openDBFile(const char* szFile)
{
    if(szFile == NULL)
        return (int)-1;
    return dbfileHandle.dataFileList.openDBFile(QString(szFile));
}
    
void closeDBFile(const char* szFile)
{
    if(szFile == NULL)
        return ;
    return dbfileHandle.dataFileList.closeDBFile(QString(szFile));
}

int loadDataFileHeader( int fd, DATAFILEHEADER* pHeader )
{
    if(fd == (int)-1 || NULL == pHeader)
        return (int)-1;

     return dbfileHandle.dataFileList.loadDataFileHeader(fd,pHeader);
}

int saveDataFileHeader( int fd, DATAFILEHEADER* pHeader )
{
    if(fd == (int)-1 || NULL == pHeader)
        return (int)-1;
     return dbfileHandle.dataFileList.saveDataFileHeader(fd,pHeader);
}

int loadDBRecord( int fd, quint16 wRec, void* pRecord )
{
    if(fd == (int)-1 || NULL == pRecord)
        return (int)-1;
     return dbfileHandle.dataFileList.loadDataFileRecord(fd,wRec,(char*)pRecord,(quint32)-1);
}

int saveDBRecord( int fd, quint16 wRec, void* pRecord )
{
    if(fd == (int)-1 || NULL == pRecord)
        return (int)-1;
    return dbfileHandle.dataFileList.saveDataFileRecord(fd,wRec,(char*)pRecord,(quint32)-1);
}




















