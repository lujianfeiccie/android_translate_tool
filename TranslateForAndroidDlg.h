
// TranslateForAndroidDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CTranslateForAndroidDlg �Ի���
class CTranslateForAndroidDlg : public CDialogEx
{
// ����
public:
	CTranslateForAndroidDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRANSLATEFORANDROID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
