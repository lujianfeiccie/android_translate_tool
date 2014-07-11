
// TranslateForAndroidDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


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
};
