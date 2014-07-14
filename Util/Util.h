#pragma once
class Util
{
public:
 Util(void);
    static void __cdecl LOG(const char *format, ...);
	static void GetFileDirectory(char* fileDirectory);
	static void GetDirectoryByFileName(const char* fileName,char* directory);
public:
 ~Util(void);
};


