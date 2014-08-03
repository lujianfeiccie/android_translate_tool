#pragma once
#include "afxwin.h"
#include <list>

// TranslateApiDlg 对话框

typedef struct
{
	CString name;
	CString value;
}combo_value_type;

class CTranslateApiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslateApiDlg)

public:
	CTranslateApiDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTranslateApiDlg();

// 对话框数据
	enum { IDD = IDD_TRANSLATEAPIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	BOOL PreTranslateMessage(MSG* pMsg);
	BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnGoTranslate();	
	// Path for excel file
	CEdit m_edit_excel_path;
	afx_msg void OnBnClickedBtnBrowser();
	CComboBox m_combo_from;
	CComboBox m_combo_to;
	CEdit m_edit_from;
	CEdit m_edit_to;
	std::list<combo_value_type> m_list_combo;

	void addCombo(CString key,CString value);
	afx_msg void OnCbnSelchangeComboFrom();
	afx_msg void OnCbnSelchangeComboTo();
};
