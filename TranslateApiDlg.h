#pragma once


// TranslateApiDlg 对话框

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
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnGoTranslate();	
};
