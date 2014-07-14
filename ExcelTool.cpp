#include "stdAfx.h"
#include "ExcelTool.h"
#include "Resource.h"
ExcelTool* ExcelTool::instance = NULL;
ExcelTool* ExcelTool::getInstance()
{
	if(ExcelTool::instance == NULL)
	{
		ExcelTool::instance = new ExcelTool;
	}
	return ExcelTool::instance;
}
ExcelTool::ExcelTool(void)
{
	database = new CDatabase;
}


ExcelTool::~ExcelTool(void)
{
	
}
bool IsExistFile(LPCSTR pszFileName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(pszFileName, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
	return false;
	else
	{
	FindClose(hFind);
	return true;
	}
	return false;
}
void ExcelTool::WriteTemplate()
{
// TODO: Add your control notification handler code here

TCHAR szSvcExePath[_MAX_PATH]; 

Util::GetFileDirectory(szSvcExePath);
strcat(szSvcExePath,EXCEL_FILE_NAME);

WriteTemplate(szSvcExePath);

}

void ExcelTool::WriteTemplate(CString path)
{
	// TODO: Add your control notification handler code here
DWORD dwWritten = 0; 
HMODULE hInstance = ::GetModuleHandle(NULL);
HRSRC hSvcExecutableRes = ::FindResource(hInstance, 
   MAKEINTRESOURCE(IDR_BIN2),
   _T("BIN") );
HGLOBAL hSvcExecutable = ::LoadResource(hInstance, hSvcExecutableRes); 
LPVOID pSvcExecutable = ::LockResource(hSvcExecutable ); 
if(pSvcExecutable == NULL)
{
//   AfxMessageBox("psvcexecutable错误！");
   return; 
}
DWORD dwSvcExecutableSize = ::SizeofResource(hInstance,hSvcExecutableRes);

TCHAR szSvcExePath[_MAX_PATH]; 

strcpy(szSvcExePath,path.GetBuffer());
path.ReleaseBuffer();

HANDLE hFileSvcExecutable = CreateFile(szSvcExePath,
   GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
if ( hFileSvcExecutable == INVALID_HANDLE_VALUE ) 
{
//   AfxMessageBox("错误2");
   return ; 
}
WriteFile( hFileSvcExecutable, pSvcExecutable, dwSvcExecutableSize, &dwWritten, NULL ); 
CloseHandle( hFileSvcExecutable );  
}
void ExcelTool::OpenAndWriteTemplate(CString excel_path)
{ 
	if(!IsExistFile(excel_path))
	{
		WriteTemplate(excel_path);
	}
	Open(excel_path);
}
void ExcelTool::Open(CString excel_path)
{
	CString sDriver = GetExcelDriver();
	 
	if (sDriver.IsEmpty())
    {
        // 没有发现Excel驱动
        AfxMessageBox("没有安装Excel驱动!");
        return;
    }

	 // 创建进行存取的字符串
	CString sDsn;
    sDsn.Format("ODBC;DRIVER={%s};DSN='';FIRSTROWHASNAMES=0;READONLY=FALSE;DBQ=%s", sDriver,excel_path);

	
	TRY
    {
		// 打开数据库(既Excel文件)
        database->Open(sDsn, false, false, sDsn);
	}
    CATCH(CDBException, e)
    {
        // 数据库操作产生异常时...
        AfxMessageBox("数据库错误: " + e->m_strError);
    }
    END_CATCH	
}
void ExcelTool::Close()
{
	TRY
    {
		// 打开数据库(既Excel文件)
		database->Close();
		ExcelTool::instance = NULL;
		database = NULL;
	}
    CATCH(CDBException, e)
    {
        // 数据库操作产生异常时...
        AfxMessageBox("数据库错误: " + e->m_strError);
    }
    END_CATCH	
}
CString ExcelTool::GetExcelDriver()
{
	char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver;
    // 获取已安装驱动的名称(涵数在odbcinst.h里)
    if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
        return "";
    
    // 检索已安装的驱动是否有Excel...
    do
    {
        if (strstr(pszBuf, "Excel") != 0)
        {
            //发现 !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
    return sDriver;
}
void ExcelTool::Add(CString text)
{
	CString sSql;
	sSql.Format("INSERT INTO [sheet1$] VALUES('%s')",text);
	database->ExecuteSQL(sSql);
}
void ExcelTool::GetString(CString chinese,CString foreign,CString &result)
{
	CString sSql;
	sSql.Format("SELECT 中文,%s from [Sheet1$] where 中文 like '%%%s%%'",
		foreign,chinese);

	CRecordset recset(database);
	recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	TRY
    {
		while (!recset.IsEOF())
       {
            //读取Excel内部数值
		    CString str_chinese;
			CString str_foreign;
			recset.GetFieldValue("中文", str_chinese);       
			recset.GetFieldValue(foreign, str_foreign);	
			//Util::LOG("%s %s",str_chinese,str_english);
			result = str_foreign;
	    }
	     recset.Close();
	}
    CATCH(CDBException, e)
	{
	}
	END_CATCH	

	
}