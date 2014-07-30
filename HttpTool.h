#pragma once


typedef void (*HTTP_TOOL_CALL_BACK) (unsigned long code,TCHAR* result);
class CHttpTool
{
public:
	CHttpTool(void);
	~CHttpTool(void);
	void request(TCHAR* url,HTTP_TOOL_CALL_BACK callback);
};

