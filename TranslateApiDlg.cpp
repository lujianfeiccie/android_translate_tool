// CTranslateApiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TranslateForAndroid.h"
#include "TranslateApiDlg.h"
#include "afxdialogex.h"


// CTranslateApiDlg 对话框

IMPLEMENT_DYNAMIC(CTranslateApiDlg, CDialogEx)

CTranslateApiDlg::CTranslateApiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTranslateApiDlg::IDD, pParent)
{
	
}

CTranslateApiDlg::~CTranslateApiDlg()
{
}

void CTranslateApiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTranslateApiDlg, CDialogEx)
	ON_WM_CLOSE()
	
	ON_BN_CLICKED(IDC_BTN_GO_TRANSLATE, &CTranslateApiDlg::OnBnClickedBtnGoTranslate)
END_MESSAGE_MAP()


// CTranslateApiDlg 消息处理程序


BOOL CTranslateApiDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_KEYDOWN)
	{
	BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
	BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;

	// only gets here if CTRL key is pressed
	BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;

	switch( pMsg->wParam )
	{

		case 'A':
		if (bCtrl){
			/*m_edit_excel_path.SetSel(0,-1);
			m_edit_language.SetSel(0,-1);
			m_edit_xml_directory.SetSel(0,-1);
			m_edit_xml_path.SetSel(0,-1);
			m_edit_xml_to_excel.SetSel(0,-1);*/
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}

void CTranslateApiDlg::OnClose()
{
	CDialog::OnClose();	
}
void CALL_BACK_HTTP(unsigned long code,TCHAR* result)
{
	Json::Reader reader;
	Json::Value value;
	CString cstr_from;
	CString cstr_to;
	CString cstr_src;
	CString cstr_dst;

	char result_tmp[1024];
		Util::wcharTochar(result,result_tmp,sizeof(result));
	
	if(reader.parse(result_tmp,value))
	{
		std::string str_from = value["from"].asString();
		std::string str_to = value["to"].asString();
		cstr_from = str_from.c_str();
		cstr_to = str_to.c_str();
		Json::Value trans_result = value["trans_result"];
		int index = 0;
		std::string str_src = trans_result[index]["src"].asString();
		std::string str_dst = trans_result[index]["dst"].asString();
		cstr_src = str_src.c_str();
		cstr_dst = str_dst.c_str();

	}

}
UINT ThreadHttpRequest(LPVOID lpvoid)
{	
	TCHAR url_request_tmp[500];
	Util::getUrl(url_request_tmp,L"今天",L"zh",L"en");
	
	CHttpTool httpTool;
	httpTool.request(url_request_tmp,CALL_BACK_HTTP);
	Util::LOG(L"Finish");
	return 0;
}

void CTranslateApiDlg::OnBnClickedBtnGoTranslate()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadHttpRequest,this);
}
