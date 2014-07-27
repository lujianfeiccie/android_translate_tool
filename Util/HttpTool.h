#pragma once


typedef void (*HTTP_TOOL_CALL_BACK) (unsigned long code,char* result);
class CHttpTool
{
public:
	CHttpTool(void);
	~CHttpTool(void);
	void request(char* url,HTTP_TOOL_CALL_BACK callback);
};

