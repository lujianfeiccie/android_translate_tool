// SimpleToTraditionalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TranslateForAndroid.h"
#include "SimpleToTraditionalDlg.h"
#include "afxdialogex.h"

UINT indicators_simpleToTraditional[]={
IDS_STRING_STATUS
};


// CSimpleToTraditionalDlg 对话框

IMPLEMENT_DYNAMIC(CSimpleToTraditionalDlg, CDialogEx)

CSimpleToTraditionalDlg::CSimpleToTraditionalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleToTraditionalDlg::IDD, pParent)
{

}

CSimpleToTraditionalDlg::~CSimpleToTraditionalDlg()
{
}

void CSimpleToTraditionalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BROWSER, m_edit_browser);
	DDX_Control(pDX, IDC_BTN_BROWSER, m_btn_browser);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btn_export);
	DDX_Control(pDX, IDC_BTN_GO, m_btn_go);
}


BEGIN_MESSAGE_MAP(CSimpleToTraditionalDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CSimpleToTraditionalDlg::OnBnClickedBtnExport)
	ON_MESSAGE(WM_MSG_STATUS,&CSimpleToTraditionalDlg::OnMessageReceive)
	ON_BN_CLICKED(IDC_BTN_GO, &CSimpleToTraditionalDlg::OnBnClickedBtnGo)
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CSimpleToTraditionalDlg::OnBnClickedBtnBrowser)
END_MESSAGE_MAP()


// CSimpleToTraditionalDlg 消息处理程序
BOOL CSimpleToTraditionalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		//Add Status Bar
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_simpleToTraditional,sizeof(indicators_simpleToTraditional)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_simpleToTraditional[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);
	
	return TRUE;
}
UINT ThreadExportExcel(LPVOID lpvoid)
{
	CSimpleToTraditionalDlg* dlg = (CSimpleToTraditionalDlg*)lpvoid;
	
	ExcelTool::getInstance()->OpenAndWriteTemplate(dlg->m_strFileName);
	ExcelTool::getInstance()->Close();

	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	return 0;
}
void CALLBACK_getString(CString str,int total,int index,LPVOID lpvoid)
{
	CSimpleToTraditionalDlg* dlg = (CSimpleToTraditionalDlg*)lpvoid;
	CString strTraditional = CjfConvert::strJ2F(str);
	ExcelTool::getInstance()->Update(str,strTraditional);
	CString msg;
	msg.Format(L"Processing %d/%d",index+1,total);
	dlg->SendMessageStatus(MSG_TYPE::MSG_Other,msg);
}
UINT ThreadConvertExcel(LPVOID lpvoid)
{
	CSimpleToTraditionalDlg* dlg = (CSimpleToTraditionalDlg*)lpvoid;
	
	ExcelTool::getInstance()->Open(dlg->m_strFileName);
	ExcelTool::getInstance()->GetString(CALLBACK_getString,lpvoid);
	ExcelTool::getInstance()->Close();

	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	return 0;
}
void CSimpleToTraditionalDlg::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
	//CString export_path = 
	
	CString strFilter = L"excel files(*.xls)|*.xls||";
	CFileDialog FileDlg(false,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	m_strFileName = FileDlg.GetPathName();
	CString strFileExt = FileDlg.GetFileExt();
	if(strFileExt == "")
	{
		m_strFileName.Append(L".xls");
	}
	m_edit_browser.SetWindowTextW(m_strFileName);
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadExportExcel,this);
}
void CSimpleToTraditionalDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}

LONG CSimpleToTraditionalDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{	
	case MSG_TYPE::MSG_Processing:
		{
			m_statusbar_status.SetPaneText(0,L"Processing");
			setEnable(FALSE);
		}
		break;
	case MSG_TYPE::MSG_Finish:
		{
			setEnable(TRUE);

			m_statusbar_status.SetPaneText(0,L"Finish");
			MessageBox(L"Success",L"Prompt");

		}
		break;
	case MSG_TYPE::MSG_Loading:
		{
		    m_statusbar_status.SetPaneText(0,L"Loading");
			setEnable(FALSE);
		}
		break;
	case MSG_TYPE::MSG_XML_PATH_Empty:
		{
			//m_statusbar_status.SetPaneText(0,"Xml path can not be empty!");
			MessageBox(L"Xml path can not be empty!",L"Prompt");
		}
		break;	
	}	
	return 0;
}
void CSimpleToTraditionalDlg::setEnable(BOOL enable)
{
	m_edit_browser.EnableWindow(enable);
	m_btn_browser.EnableWindow(enable);
	m_btn_export.EnableWindow(enable);
	m_btn_go.EnableWindow(enable);
}

void CSimpleToTraditionalDlg::OnBnClickedBtnGo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFileName;
	m_edit_browser.GetWindowTextW(strFileName);
	if(strFileName.Trim()==""){
		MessageBox(L"File path cannot be empty");
		return;
	}
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadConvertExcel,this);
}


void CSimpleToTraditionalDlg::OnBnClickedBtnBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString strFilter = L"excel files(*.xls)|*.xls||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	m_strFileName = FileDlg.GetPathName();

	m_edit_browser.SetWindowTextW(m_strFileName);
}
