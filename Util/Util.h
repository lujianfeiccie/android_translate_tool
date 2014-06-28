#pragma once
class Util
{
public:
 Util(void);
    static void __cdecl LOG(const char *format, ...);
	static void GetFileDirectory(char* fileDirectory);
public:
 ~Util(void);
};


