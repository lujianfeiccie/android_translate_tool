// CTranslateApiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TranslateForAndroid.h"
#include "TranslateApiDlg.h"
#include "afxdialogex.h"

UINT indicators_translate_api_dlg[]={
IDS_STRING_STATUS
};
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
	DDX_Control(pDX, IDC_EDIT_PATH, m_edit_excel_path);
	DDX_Control(pDX, IDC_COMBO_FROM, m_combo_from);
	DDX_Control(pDX, IDC_COMBO_TO, m_combo_to);

	DDX_Control(pDX, IDC_BTN_GO_TRANSLATE, m_btn_go_translate);
	DDX_Control(pDX, IDC_BTN_BROWSER, m_btn_browser);
}


BEGIN_MESSAGE_MAP(CTranslateApiDlg, CDialogEx)
	ON_WM_CLOSE()
	
	ON_BN_CLICKED(IDC_BTN_GO_TRANSLATE, &CTranslateApiDlg::OnBnClickedBtnGoTranslate)
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CTranslateApiDlg::OnBnClickedBtnBrowser)
	ON_CBN_SELCHANGE(IDC_COMBO_FROM, &CTranslateApiDlg::OnCbnSelchangeComboFrom)
	ON_CBN_SELCHANGE(IDC_COMBO_TO, &CTranslateApiDlg::OnCbnSelchangeComboTo)
	ON_MESSAGE(WM_MSG_STATUS,&CTranslateApiDlg::OnMessageReceive)
END_MESSAGE_MAP()


// CTranslateApiDlg 消息处理程序

CString getComboValue(CComboBox& combobox,std::vector<combo_value_type> list)
{
	int selected = combobox.GetCurSel();
	std::vector<combo_value_type>::iterator it = list.begin();
	combo_value_type tmp = *(it+selected);
	return tmp.value;
}
BOOL CTranslateApiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
		//Add Status Bar
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators_translate_api_dlg,sizeof(indicators_translate_api_dlg)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators_translate_api_dlg[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);
	
	addCombo(L"Chinese",L"zh");
	addCombo(L"English",L"en");
	addCombo(L"Japanese",L"jp");
	addCombo(L"Korean",L"kor");
	addCombo(L"Spanish",L"spa");
	addCombo(L"Franch",L"fra");
	addCombo(L"Thai",L"th");
	addCombo(L"Arab",L"ara");
	addCombo(L"Russian",L"ru");
	addCombo(L"Portuguese",L"pt");
	
	
	std::vector<combo_value_type>::iterator it = m_list_combo.begin();
	for(;it!=m_list_combo.end();++it)
	{
		Util::LOG(L"name=%s value=%s\n",(*it).name,(*it).value);
		m_combo_from.AddString((*it).name);
		m_combo_to.AddString((*it).name);
	}
	m_combo_from.SetCurSel(0);
	m_combo_to.SetCurSel(0);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CTranslateApiDlg::addCombo(CString key,CString value)
{	
	combo_value_type m_combo_value_type = {key,value};	
	m_list_combo.push_back(m_combo_value_type);
}

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
			m_edit_excel_path.SetSel(0,-1);
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
		Util::wcharTochar(result,result_tmp,sizeof(result_tmp));
	
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
		
		ExcelTool::getInstance()->Update(cstr_src,cstr_dst);
	}

}

void CallBack_getFromExcel(CString str,int total,int index,LPVOID lpvoid)
{
	if(""==str.Trim()) return;
    CTranslateApiDlg* dlg = (CTranslateApiDlg*)lpvoid;
	Util::LOG(L"CallBack_getFromExcel=");
	//Util::LOG(result);
		TCHAR url_request_tmp[500];
	
	CString q=str;
	
	CString from = getComboValue(dlg->m_combo_from,dlg->m_list_combo);
	CString to = getComboValue(dlg->m_combo_to,dlg->m_list_combo);

	if("en"!=from.Trim())    //When the q is not from English, encode it to utf8
		q = Util::UrlEncode(q);

	Util::getUrl(url_request_tmp,q.GetBuffer(),from.GetBuffer(),to.GetBuffer());
	from.ReleaseBuffer();
	to.ReleaseBuffer();
	q.ReleaseBuffer();	

	CString msg;
	msg.Format(L"Processing %d/%d",index+1,total);
	dlg->SendMessageStatus(MSG_TYPE::MSG_Other,msg);
	CHttpTool httpTool;
	httpTool.request(url_request_tmp,CALL_BACK_HTTP);
}
UINT ThreadHttpRequest(LPVOID lpvoid)
{	
	CTranslateApiDlg* dlg = (CTranslateApiDlg*)lpvoid;
	

	//Util::LOG(L"Finish");
	dlg->SendMessageStatus(MSG_TYPE::MSG_Processing);
	ExcelTool::getInstance()->Open(dlg->m_str_excel_path);
	Util::LOG(L"Open");
	ExcelTool::getInstance()->GetString(CallBack_getFromExcel,lpvoid);
	Util::LOG(L"GetString");
	ExcelTool::getInstance()->Close();
	Util::LOG(L"Close");
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	return 0;
}

void CTranslateApiDlg::OnBnClickedBtnGoTranslate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString excel_path;
	m_edit_excel_path.GetWindowTextW(excel_path);

	if(""==excel_path.Trim()){
		MessageBox(L"Excel path cannot be empty!");
		return;
	}

	if(!Util::IsExistFile(excel_path)){
		MessageBox(L"Excel file not exist!");
		return;
	}
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	m_str_excel_path = excel_path;
	AfxBeginThread(ThreadHttpRequest,this);
}


void CTranslateApiDlg::OnBnClickedBtnBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CString strFilter = _T("Excel files(*.xls)|*.xls||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_excel_path.SetWindowText(strFileName);
}


void CTranslateApiDlg::OnCbnSelchangeComboFrom()
{
	// TODO: 在此添加控件通知处理程序代码
	int selected1 = m_combo_from.GetCurSel();
	int selected2 = m_combo_to.GetCurSel();
	
	if(selected1 == selected2){
		int size = m_list_combo.size();
		++selected2;
		m_combo_to.SetCurSel(selected2 % size);
	}
}


void CTranslateApiDlg::OnCbnSelchangeComboTo()
{
	// TODO: 在此添加控件通知处理程序代码
	int selected1 = m_combo_to.GetCurSel();
	int selected2 = m_combo_from.GetCurSel();
	
	if(selected1 == selected2){
		int size = m_list_combo.size();
		++selected2;
		m_combo_from.SetCurSel(selected2 % size);
	}
}

void CTranslateApiDlg::SendMessageStatus(MSG_TYPE type,CString msg)
{
	SendMessage(WM_MSG_STATUS,type,(LPARAM)msg.GetBuffer());
	msg.ReleaseBuffer();
}
void CTranslateApiDlg::setEnable(BOOL enable)
{
	m_edit_excel_path.EnableWindow(enable==TRUE);
	m_btn_browser.EnableWindow(enable==TRUE);
	m_combo_from.EnableWindow(enable==TRUE);
	m_combo_to.EnableWindow(enable==TRUE);
	m_btn_go_translate.EnableWindow(enable==TRUE);
}
LONG CTranslateApiDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	Util::LOG(L"CTranslateApiDlg::OnMessageReceive");
	MSG_TYPE type = (MSG_TYPE)wParam;
	CString msg = (TCHAR*)lParam;
	switch(type)
	{
	case MSG_TYPE::MSG_Loading:
		{
			m_statusbar_status.SetPaneText(0,L"Loading");
			setEnable(FALSE);			
		}
		break;
	case MSG_TYPE::MSG_Processing:
		{
			m_statusbar_status.SetPaneText(0,L"Processing");
			setEnable(FALSE);		
		}
		break;
	case MSG_TYPE::MSG_Finish:
		{
			m_statusbar_status.SetPaneText(0,L"Finish");
			setEnable(TRUE);
			MessageBox(L"Finish!");
		}
		break;
	case MSG_TYPE::MSG_Other:
		{
			m_statusbar_status.SetPaneText(0,msg);
		}
		break;
	}
	return 0;
}