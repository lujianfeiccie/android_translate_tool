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
	
	
	std::list<combo_value_type>::iterator it = m_list_combo.begin();
	for(;it!=m_list_combo.end();++it)
	{
		Util::LOG(L"name=%s value=%s\n",(*it).name,(*it).value);
		m_combo_from.AddString((*it).name);
		m_combo_to.AddString((*it).name);
	}
	m_combo_from.SetCurSel(0);
	m_combo_to.SetCurSel(1);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CTranslateApiDlg::addCombo(CString key,CString value)
{	
	combo_value_type m_combo_value_type = {key,value};	
	m_list_combo.push_back(m_combo_value_type);
}
void CTranslateApiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, m_edit_excel_path);
	DDX_Control(pDX, IDC_COMBO_FROM, m_combo_from);
	DDX_Control(pDX, IDC_COMBO_TO, m_combo_to);
	DDX_Control(pDX, IDC_EDIT_FROM, m_edit_from);
	DDX_Control(pDX, IDC_EDIT_TO, m_edit_to);
}


BEGIN_MESSAGE_MAP(CTranslateApiDlg, CDialogEx)
	ON_WM_CLOSE()
	
	ON_BN_CLICKED(IDC_BTN_GO_TRANSLATE, &CTranslateApiDlg::OnBnClickedBtnGoTranslate)
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CTranslateApiDlg::OnBnClickedBtnBrowser)
	ON_CBN_SELCHANGE(IDC_COMBO_FROM, &CTranslateApiDlg::OnCbnSelchangeComboFrom)
	ON_CBN_SELCHANGE(IDC_COMBO_TO, &CTranslateApiDlg::OnCbnSelchangeComboTo)
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
		
		//unsigned char high = str_dst.c_str()[0];
		//unsigned char low = str_dst.c_str()[1];

		//char str_tmp[1024];
		//Util::enc_utf8_to_unicode_one(str_dst.c_str(),str_tmp);
	}

}
UINT ThreadHttpRequest(LPVOID lpvoid)
{	
	TCHAR url_request_tmp[500];
	
	CString q = Util::UrlEncode(L"这是一个苹果");
	Util::getUrl(url_request_tmp,q.GetBuffer(),L"zh",L"en");
	q.ReleaseBuffer();	

	CHttpTool httpTool;
	httpTool.request(url_request_tmp,CALL_BACK_HTTP);
	//Util::LOG(L"Finish");
	return 0;
}

void CTranslateApiDlg::OnBnClickedBtnGoTranslate()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxBeginThread(ThreadHttpRequest,this);
}


void CTranslateApiDlg::OnBnClickedBtnBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTranslateApiDlg::OnCbnSelchangeComboFrom()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo_from.GetCurSel();
	
}


void CTranslateApiDlg::OnCbnSelchangeComboTo()
{
	// TODO: 在此添加控件通知处理程序代码
}
