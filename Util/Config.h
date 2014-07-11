#pragma once
#define APP_NAME "APP_NAME"
#define FILE_NAME "config.ini"
class Config
{
public:	
	Config(void);
	~Config(void);
	static void WriteConfig(const char* appname,const char* keyname,const char* value,const char* file);
	static void WriteConfig(const char* keyname,const char* value);
	static void ReadConfig(const char* appname,const char* keyname,	char* value,unsigned int size,const char* file);
	static void ReadConfig(const char* keyname,char* value);
};