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
	void Close();
	void Add(CString text);
};
