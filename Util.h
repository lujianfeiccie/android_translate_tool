#pragma once
class Util
{
public:
 Util(void);
    static void __cdecl LOG(const TCHAR *format, ...);
	static void GetFileDirectory(TCHAR* fileDirectory);
	static void GetDirectoryByFileName(const TCHAR* fileName,TCHAR* directory);
	static void getUrl(TCHAR* url,TCHAR* q,TCHAR* from=L"auto",TCHAR* to=L"auto");
	static void charTowchar(const char *chr, wchar_t *wchar, int size);
	static void wcharTochar(const wchar_t *wchar, char *chr, int length);
public:
 ~Util(void);
};


