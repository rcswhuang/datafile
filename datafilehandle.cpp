#include "datafilehandle.h"
#include "publicdata.h"
#include "hruleeditapi.h"
#include "hformulapi.h"
#include "hconfigapi.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
typedef struct _tagDefaultPath
{
    ushort nFileType;
    int id;
    std::string  szPath;
}DEFAULTPATH;

QString strDataFilePath[DFPATH_LAST + 1];
#define MAX_PATH 1024
//如果ini中没有对应的Key则取默认
DEFAULTPATH DefaultPath[] =
{
    //type,id,szPath
    {DFPATH_DATA,SYS_PATH_DATA_SET,"data"},
    {DFPATH_GRAPH,SYS_PATH_GRAPH_SET,"graph"},
    {DFPATH_ICON,SYS_PATH_ICON_SET,"icon"},
    {DFPATH_BITMAP,SYS_PATH_BITMAP_SET,"bitmap"},
    //DFPATH_MACRO,SYS_PATH_MACRO_SET,"macro",
    {DFPATH_MEDIA,SYS_PATH_MEDIR_SET,"media"},
    {DFPATH_OPSHEET,SYS_PATH_OPSHEET_SET,"opsheet"},
    {DFPATH_WORKNOTE,SYS_PATH_WORKNOTE_SET,"worknote"},
    {DFPATH_EVENT,SYS_PATH_EVENT_SET,"event"},
    {DFPATH_REPORT,SYS_PATH_REPORT_SET,"report"},
    {DFPATH_SIGNPAD,SYS_PATH_SIGNPAD_SET,"signpad"},
    {DFPATH_FIL,SYS_PATH_FIL_SET,"fil"},
    {DFPATH_INI,SYS_PATH_INI_SET,"ini"},
    {DFPATH_PLUGIN,SYS_PATH_PLUGIN_SET,"plugin"}
    //DFPATH_BIN,"bin"
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
    else if(nFileType == FILE_TYPE_OPSHEET)
    {
        nSize = sizeof(OPSHEETSTEP);
    }
    return nSize;
}

HDataFileHandle::HDataFileHandle()
{
    initDataFilePath();
}

void HDataFileHandle::initDataFilePath()
{
    initSysConfig();
    QVariant var;
    int nPath = SYS_SET_PATH;
    for(int i = 0; i < sizeof(DefaultPath)/sizeof(DEFAULTPATH);i++)
    {
        getSettingValue(nPath,DefaultPath[i].id,var);
        QString path = var.toString() ;//+ "/" + QString::fromStdString(DefaultPath[i].szPath);
        DefaultPath[i].szPath = path.toStdString();
    }
}
void  HDataFileHandle::getDataFilePath(int nPath,QString& path)
{
    for(int i = 0; i < sizeof(DefaultPath)/sizeof(DEFAULTPATH);i++)
    {
        if(nPath == DefaultPath[i].nFileType)
            path = QString::fromStdString(DefaultPath[i].szPath);
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
        case FILE_TYPE_OPSHEET:
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
    //strPath += "/";
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
    //return dbfileHandle.dataFileList.closeDBFile(QString(szFile));
    return;
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




















