#include "StdAfx.h"
#include "Util.h"

Util::Util(void)
{
}
Util::~Util(void)
{
}
void __cdecl Util::LOG(const char* fmt, ...)
{
    char buf[4096], *p = buf;
    va_list args;
 
 
    va_start(args, fmt);
    p += vsnprintf_s(p, sizeof(buf), _TRUNCATE, fmt, args);
    va_end(args);
 
 
    while ( p > buf && isspace(p[-1]) )
        *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';
 
 
    OutputDebugStringA(buf); //output as ANSI string //OutputDebugString
}  
void Util::GetFileDirectory(char* fileDirectory)
{
	CString sPath;
	
	//获取主程序所在路径,存在sPath中
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer ();
    int nPos;
	nPos=sPath.ReverseFind ('\\');
	sPath=sPath.Left (nPos);
	strcpy(fileDirectory,sPath.GetBuffer());
	sPath.ReleaseBuffer();
}
void Util::GetDirectoryByFileName(const char* fileName,char* directory)
{
	CString path;
	path.Format("%s",fileName);
	int start = path.ReverseFind('\\');
	CString directory_str = path.Left(start);
	strcpy(directory,directory_str.GetBuffer(1024));
	directory_str.ReleaseBuffer();
}
void Util::getUrl(char* url,char* q,char* from,char* to)
{
	CString tmp;
	tmp.Format("%s?client_id=%s&q=%s&from=%s&to=%s",
		API_URL,API_KEY,q,from,to);
	strcpy(url,tmp.GetBuffer());
	tmp.ReleaseBuffer();
}
int Util::UTF8ToGBK(CString &strOut,const char* szSrc)
{
	if(szSrc==NULL)
	{
	strOut="";
	return -1;
	}
	WCHAR *strSrc;
	TCHAR *szRes;
	int i = MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, NULL, 0);
	strSrc = new WCHAR[i+1];
	MultiByteToWideChar(CP_UTF8, 0, szSrc, -1, strSrc, i);
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new TCHAR[i+1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
	strOut = szRes;
	delete []strSrc;
	delete []szRes;
return 0;
}