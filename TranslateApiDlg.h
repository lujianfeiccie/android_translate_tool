#pragma once
#include "afxwin.h"
#include <vector>

// TranslateApiDlg �Ի���

typedef struct
{
	CString name;
	CString value;
}combo_value_type;


class CTranslateApiDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslateApiDlg)

public:
	CTranslateApiDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTranslateApiDlg();

// �Ի�������
	enum { IDD = IDD_TRANSLATEAPIDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	std::vector<combo_value_type> m_list_combo;

	void addCombo(CString key,CString value);
	afx_msg void OnCbnSelchangeComboFrom();
	afx_msg void OnCbnSelchangeComboTo();	
	CStatusBar m_statusbar_status;
	void SendMessageStatus(MSG_TYPE type,CString msg=NULL);
	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);
	CString m_str_excel_path;
};
