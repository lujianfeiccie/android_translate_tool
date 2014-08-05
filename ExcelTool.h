#pragma once

typedef void (*EXCEL_CALL_BACK) (CString str,int total,int index,LPVOID lpvoid);

class ExcelTool
{
private:
	ExcelTool(void);
	CString GetExcelDriver();
	CDatabase* database;
	void WriteTemplate();
	void WriteTemplate(CString path);
public:
	
	~ExcelTool(void);
	static ExcelTool* instance;
	static ExcelTool* getInstance();

	void OpenAndWriteTemplate(CString excel_path);
	void Open(CString excel_path);
	void Close();
	void Add(CString text);	
	void Update(CString origin,CString other);	
	void GetString(CString chinese,CString foreign,CString &result,BOOL fuzzy=TRUE);
	void GetString(EXCEL_CALL_BACK callback=NULL,LPVOID lpvoid=NULL);
};
