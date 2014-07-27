#pragma once
class Util
{
public:
 Util(void);
    static void __cdecl LOG(const char *format, ...);
	static void GetFileDirectory(char* fileDirectory);
	static void GetDirectoryByFileName(const char* fileName,char* directory);
	static void getUrl(char* url,char* q,char* from="auto",char* to="auto");
public:
 ~Util(void);
};


