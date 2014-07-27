
// TranslateForAndroidDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

const int WM_MSG_STATUS = WM_USER+100;

enum MSG_TYPE
{
	MSG_Processing,
	MSG_Finish,
	MSG_FinishParagraphProcessing,
	MSG_Loading,
	MSG_XML_PATH_Empty
};
static UINT indicators[]={
IDS_STRING_STATUS
};
// CTranslateForAndroidDlg 对话框
class CTranslateForAndroidDlg : public CDialogEx
{
// 构造
public:
	CTranslateForAndroidDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TRANSLATEFORANDROID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGo();
	afx_msg void OnBnClickedButtonTest();
	// editor for xml path
	CEdit m_edit_xml_path;
	// editor for excel path
	CEdit m_edit_excel_path;
	afx_msg void OnBnClickedBtnXmlBrowser();
	afx_msg void OnBnClickedBtnExcelBrowser();
	// edit for language
	CEdit m_edit_language;
	// Xml path to excel
	CEdit m_edit_xml_to_excel;
	afx_msg void OnBnClickedBtnBrowserToExcel();
	// Directory with Xml files in it
	CEdit m_edit_xml_directory;
	afx_msg void OnBnClickedBtnBrowserDirectory();
	afx_msg void OnBnClickedRadioSingle();
	afx_msg void OnBnClickedRadioDirectory();
    void setRadioEnableForSingle(BOOL m_b_flag);
	CString ShowDirectoryDlg();
	void WriteXml(CString filePath,CString language);
	void ReadAllFilesInDir(CString dir);
	// Browser for xml path
	CButton m_btn_browser_xml_path;
	// Browser for directory
	CButton m_btn_browser_directory;
	
	// Radio for single
	CButton m_radio_single;
	// Radio for directory
	CButton m_radio_directory;
	// Check box for fuzzy search
	CButton m_check_fuzzy;
	CStatusBar m_statusbar_status;

	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);
	void SendMessageStatus(MSG_TYPE type);

	CString m_str_xml_to_excel_path;

	CString m_str_excel_path;
	CString m_str_xml_path;
	CString m_str_language;
	CString m_str_xml_directory;
	int m_int_check_fuzzy;
	CButton m_btn_go_xml2excel;
	CButton m_btn_go_excel2xml;

	BOOL PreTranslateMessage(MSG* pMsg);

};
