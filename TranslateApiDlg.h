#pragma once


// TranslateApiDlg �Ի���

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
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnGoTranslate();	
};
