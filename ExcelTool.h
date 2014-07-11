#pragma once
class ExcelTool
{
private:
	ExcelTool(void);
	CString GetExcelDriver();
	CDatabase* database;
	void WriteTemplate();
public:
	
	~ExcelTool(void);
	static ExcelTool* instance;
	static ExcelTool* getInstance();

	void Open();
	void Open(CString excel_path);
	void Close();
	void Add(CString text);
	void GetString(CString chinese,CString foreign,CString &result);
};
