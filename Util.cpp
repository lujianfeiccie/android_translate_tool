#include "StdAfx.h"
#include "Util.h"

Util::Util(void)
{
}
Util::~Util(void)
{
}
void __cdecl Util::LOG(const TCHAR* fmt, ...)
{
   /* char buf[4096], *p = buf;
    va_list args;
 
 
    va_start(args, fmt);
    p += vsnprintf_s(p, sizeof(buf), _TRUNCATE, fmt, args);
    va_end(args);
 
 
    while ( p > buf && isspace(p[-1]) )
        *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';
 
 
    OutputDebugStringA(buf); //output as ANSI string //OutputDebugString*/
}  
void Util::GetFileDirectory(TCHAR* fileDirectory)
{
	CString sPath;
	
	//获取主程序所在路径,存在sPath中
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer ();
    int nPos;
	nPos=sPath.ReverseFind ('\\');
	sPath=sPath.Left (nPos);
	wcscpy(fileDirectory,sPath.GetBuffer());
	sPath.ReleaseBuffer();
}
void Util::GetDirectoryByFileName(const TCHAR* fileName,TCHAR* directory)
{
	CString path;
	path.Format(TEXT("%s"),fileName);
	int start = path.ReverseFind('\\');
	CString directory_str = path.Left(start);
	wcscpy(directory,directory_str.GetBuffer(1024));
	directory_str.ReleaseBuffer();
}
void Util::getUrl(TCHAR* url,TCHAR* q,TCHAR* from,TCHAR* to)
{
	CString tmp;
	tmp.Format(L"%s?client_id=%s&q=%s&from=%s&to=%s",
		API_URL,API_KEY,q,from,to);
	wcscpy(url,tmp.GetBuffer());
	tmp.ReleaseBuffer();
}

void Util::charTowchar(const char *chr, wchar_t *wchar, int size)  
{     
    MultiByteToWideChar( CP_ACP, 0, chr,  
        strlen(chr)+1, wchar, size/sizeof(wchar[0]));  
}

void Util::wcharTochar(const wchar_t *wchar, char *chr, int length)  
{  
    WideCharToMultiByte( CP_ACP, 0, wchar, -1,  
        chr, length, NULL, NULL );  
}  