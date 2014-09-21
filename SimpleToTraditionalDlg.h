#pragma once

#include "Resource.h"
#include "afxwin.h"
// CSimpleToTraditionalDlg �Ի���
enum MSG_TYPE;
class CSimpleToTraditionalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimpleToTraditionalDlg)

public:
	CSimpleToTraditionalDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSimpleToTraditionalDlg();

// �Ի�������
	enum { IDD = IDD_SIMPLETOTRADITIONALDLG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_browser;
	CButton m_btn_browser;
	CButton m_btn_export;
	CButton m_btn_go;
	CStatusBar m_statusbar_status;
	afx_msg void OnBnClickedBtnExport();
	void SendMessageStatus(MSG_TYPE type,CString msg=L"");
	LONG OnMessageReceive(WPARAM wParam,LPARAM lParam);
	void setEnable(BOOL enable);

	CString m_strFileName;
	afx_msg void OnBnClickedBtnGo();
	afx_msg void OnBnClickedBtnBrowser();
};
