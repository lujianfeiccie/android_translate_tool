
// TranslateForAndroidDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TranslateForAndroid.h"
#include "TranslateForAndroidDlg.h"
#include "afxdialogex.h"
#include "TranslateApiDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTranslateForAndroidDlg 对话框




CTranslateForAndroidDlg::CTranslateForAndroidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTranslateForAndroidDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTranslateForAndroidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_XML_PATH, m_edit_xml_path);
	DDX_Control(pDX, IDC_EDIT_EXCEL_PATH, m_edit_excel_path);
	DDX_Control(pDX, IDC_EDIT_LANGUAGE, m_edit_language);
	DDX_Control(pDX, IDC_EDIT_PATH_TO_EXCEL, m_edit_xml_to_excel);
	DDX_Control(pDX, IDC_EDIT_DIRECTORY, m_edit_xml_directory);
	DDX_Control(pDX, IDC_BTN_XML_BROWSER, m_btn_browser_xml_path);
	DDX_Control(pDX, IDC_BTN_BROWSER_DIRECTORY, m_btn_browser_directory);
	DDX_Control(pDX, IDC_RADIO_SINGLE, m_radio_single);
	DDX_Control(pDX, IDC_RADIO_DIRECTORY, m_radio_directory);
	DDX_Control(pDX, IDC_CHECK_FUZZY, m_check_fuzzy);
	DDX_Control(pDX, ID_BTN_GO, m_btn_go_xml2excel);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_btn_go_excel2xml);
}

BEGIN_MESSAGE_MAP(CTranslateForAndroidDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_GO, &CTranslateForAndroidDlg::OnBnClickedBtnGo)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CTranslateForAndroidDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BTN_XML_BROWSER, &CTranslateForAndroidDlg::OnBnClickedBtnXmlBrowser)
	ON_BN_CLICKED(IDC_BTN_EXCEL_BROWSER, &CTranslateForAndroidDlg::OnBnClickedBtnExcelBrowser)
	ON_BN_CLICKED(IDC_BTN_BROWSER_TO_EXCEL, &CTranslateForAndroidDlg::OnBnClickedBtnBrowserToExcel)
	ON_BN_CLICKED(IDC_BTN_BROWSER_DIRECTORY, &CTranslateForAndroidDlg::OnBnClickedBtnBrowserDirectory)
	ON_BN_CLICKED(IDC_RADIO_SINGLE, &CTranslateForAndroidDlg::OnBnClickedRadioSingle)
	ON_BN_CLICKED(IDC_RADIO_DIRECTORY, &CTranslateForAndroidDlg::OnBnClickedRadioDirectory)
	ON_MESSAGE(WM_MSG_STATUS,&CTranslateForAndroidDlg::OnMessageReceive)
	ON_COMMAND(ID_TOOL_TRANSLATE, &CTranslateForAndroidDlg::OnToolTranslate)
END_MESSAGE_MAP()


// CTranslateForAndroidDlg 消息处理程序
void ReadFromFile(CString &xml_to_excel,
	CString &xml_path,
	CString &excel_path,
	CString &language,
	CString &singleFile,
	CString &directory,
	CString &fuzzy)
{
	Config::ReadConfig(L"xml_to_excel_path",xml_to_excel.GetBuffer(1024));
	xml_to_excel.ReleaseBuffer();
	Config::ReadConfig(L"chinese_xml_path",xml_path.GetBuffer(1024));
	xml_path.ReleaseBuffer();
	Config::ReadConfig(L"excel_path",excel_path.GetBuffer(1024));
	excel_path.ReleaseBuffer();	
	Config::ReadConfig(L"language",language.GetBuffer(1024));
	language.ReleaseBuffer();	
	Config::ReadConfig(L"singleFile",singleFile.GetBuffer(1024));
	singleFile.ReleaseBuffer();	
	Config::ReadConfig(L"directory",directory.GetBuffer(1024));
	directory.ReleaseBuffer();	
	Config::ReadConfig(L"fuzzy",fuzzy.GetBuffer(1024));
	fuzzy.ReleaseBuffer();	
}

void WriteToFile(CString &xml_to_excel,
	CString xml_path,
	CString excel_path,
	CString language,
	CString singleFile,
	CString directory,
	CString fuzzy)
{
	Config::WriteConfig(L"xml_to_excel_path",xml_to_excel);
	Config::WriteConfig(L"chinese_xml_path",xml_path);
	Config::WriteConfig(L"excel_path",excel_path);	
	Config::WriteConfig(L"language",language);	
	Config::WriteConfig(L"singleFile",singleFile);	
	Config::WriteConfig(L"directory",directory);		
	Config::WriteConfig(L"fuzzy",fuzzy);		
}
BOOL CTranslateForAndroidDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString xml_to_excel_path;
	CString xml_path;
	CString excel_path;
	CString language;
	CString singleFile;
	CString directory;
	CString fuzzy;
	ReadFromFile(xml_to_excel_path,xml_path,excel_path,language,singleFile,directory,fuzzy);
	m_edit_xml_to_excel.SetWindowText(xml_to_excel_path);
	m_edit_xml_path.SetWindowText(xml_path);
	m_edit_excel_path.SetWindowText(excel_path);
	m_edit_language.SetWindowText(language);
	m_edit_xml_directory.SetWindowText(directory);
	setRadioEnableForSingle("1"==singleFile);
	m_radio_single.SetCheck("1"==singleFile);
	m_radio_directory.SetCheck("1"!=singleFile);
	m_check_fuzzy.SetCheck("1"==fuzzy);

		//Add Status Bar
	if (!m_statusbar_status.Create(this) ||
        !m_statusbar_status.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT))
        )
	{
		   TRACE0("Failed to create status bar\n");
		   return -1;      // fail to create
	}
	m_statusbar_status.SetPaneInfo(0,indicators[0],SBPS_STRETCH,400);	
    
    RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,AFX_IDW_CONTROLBAR_FIRST);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTranslateForAndroidDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTranslateForAndroidDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTranslateForAndroidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT ThreadXmlToExcel(LPVOID lPvoid)
{
	CTranslateForAndroidDlg* dlg = (CTranslateForAndroidDlg*)lPvoid;	

	TCHAR directory[1024];

	Util::GetDirectoryByFileName(dlg->m_str_xml_to_excel_path,directory);
	
	wcscat(directory,EXCEL_FILE_NAME);

	
	ExcelTool::getInstance()->OpenAndWriteTemplate(directory);

	CMarkup xml;

	
	Util::LOG(TEXT("Load=%d"),xml.Load(dlg->m_str_xml_to_excel_path));

	while(xml.FindChildElem())
	{
	//	Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->Add(xml.GetChildData());
	}	


	ExcelTool::getInstance()->Close();
	dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);

	return 0;
}

void CTranslateForAndroidDlg::OnBnClickedBtnGo()
{	
	m_edit_xml_to_excel.GetWindowText(m_str_xml_to_excel_path);
	if(""==m_str_xml_to_excel_path.Trim())
	{
		SendMessageStatus(MSG_TYPE::MSG_XML_PATH_Empty);			
		return ;
	}
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadXmlToExcel,this);
}

void CTranslateForAndroidDlg::ReadAllFilesInDir(CString dir)
{
	   CFileFind fileFinder;
       CString filePath = dir + _T("//*.*");
      
       BOOL bFinished = fileFinder.FindFile(filePath);
       while(bFinished)  //每次循环对应一个类别目录
       {
              bFinished = fileFinder.FindNextFile();
              if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
              {
                     ReadAllFilesInDir(fileFinder.GetFilePath());
              }
              else  //再判断是否为txt文件
              {
                     //获取文件类型
                     CString fileName = fileFinder.GetFileName();
					 
                     int dotPos=fileName.ReverseFind('.');
                     CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
                     if(fileExt == _T(".xml"))  //若是txt文件则开始分类测试
                     {
                     Util::LOG(TEXT("%s"),fileFinder.GetFilePath()); 
					 WriteXml(fileFinder.GetFilePath(),m_str_language);
                     }
              }
       }
 
       fileFinder.Close();
}
void CTranslateForAndroidDlg::WriteXml(CString filePath,CString language)
{
	CMarkup xml;

	Util::LOG(TEXT("Load=%d"),xml.Load(filePath));

	CString result;
	while(xml.FindChildElem())
	{
			//Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->GetString(xml.GetChildData(),language,result,m_int_check_fuzzy);
		Util::LOG(result);
		xml.SetChildData(result);
	}	
	xml.Save(filePath);
}
UINT ThreadExcelToXml(LPVOID lpvoid)
{
	CTranslateForAndroidDlg* dlg = (CTranslateForAndroidDlg*)lpvoid;
	if(dlg->m_int_check_fuzzy!=0){
		ExcelTool::getInstance()->Open(dlg->m_str_excel_path);
	
		dlg->WriteXml(dlg->m_str_xml_path,dlg->m_str_language);
	
		ExcelTool::getInstance()->Close();

		//MessageBox("success");
		dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	}else{
		ExcelTool::getInstance()->Open(dlg->m_str_excel_path);
		dlg->ReadAllFilesInDir(dlg->m_str_xml_directory);
		ExcelTool::getInstance()->Close();
		dlg->SendMessageStatus(MSG_TYPE::MSG_Finish);
	}
	return 0;
}
void CTranslateForAndroidDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_edit_excel_path.GetWindowText(m_str_excel_path);
	m_edit_xml_path.GetWindowText(m_str_xml_path);
	m_edit_language.GetWindowText(m_str_language);
	m_edit_xml_directory.GetWindowText(m_str_xml_directory);

	if(m_radio_single.GetCheck()!=0){
		if(""==m_str_xml_path.Trim())
		{
			AfxMessageBox(_T("CHN Xml path can not be empty!"));
			return;
		}
	}else{
		if(""==m_str_xml_directory.Trim())
		{
			AfxMessageBox(_T("CHN Directory can not be empty!"));
			return;
		}
	}
	if(""==m_str_excel_path.Trim() ||
		""==m_str_language.Trim())
	{
		AfxMessageBox(_T("Excel path or language can not be empty"));
		return;
	}
	m_int_check_fuzzy = m_check_fuzzy.GetCheck();
	SendMessageStatus(MSG_TYPE::MSG_Processing);
	AfxBeginThread(ThreadExcelToXml,this);
}


void CTranslateForAndroidDlg::OnBnClickedBtnXmlBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter = _T("xml files(*.xml)|*.xml||");
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_xml_path.SetWindowText(strFileName);
}


void CTranslateForAndroidDlg::OnBnClickedBtnExcelBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter = L"excel files(*.xls)|*.xls||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_excel_path.SetWindowText(strFileName);
}

void CTranslateForAndroidDlg::SendMessageStatus(MSG_TYPE type)
{
	SendMessage(WM_MSG_STATUS,type,0);
}
void CTranslateForAndroidDlg::OnBnClickedBtnBrowserToExcel()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString strFilter = L"xml files(*.xml)|*.xml||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_xml_to_excel.SetWindowText(strFileName);
}
CString CTranslateForAndroidDlg::ShowDirectoryDlg()
{
	 TCHAR           szFolderPath[MAX_PATH] = {0};  
        CString         strFolderPath = TEXT("");  
          
        BROWSEINFO      sInfo;  
        ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
        sInfo.pidlRoot   = 0;  
        sInfo.lpszTitle   = _T("请选择一个文件夹：");  
        sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;  
        sInfo.lpfn     = NULL;  
  
        // 显示文件夹选择对话框  
        LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);   
        if (lpidlBrowse != NULL)  
        {  
            // 取得文件夹名  
            if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))    
            {  
                strFolderPath = szFolderPath;  
            }  
        }  
        if(lpidlBrowse != NULL)  
        {  
            ::CoTaskMemFree(lpidlBrowse);  
        }  
  
        return strFolderPath;  
}

void CTranslateForAndroidDlg::OnBnClickedBtnBrowserDirectory()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_xml_directory.SetWindowText(ShowDirectoryDlg());
}

void CTranslateForAndroidDlg::setRadioEnableForSingle(BOOL m_b_flag)
{
	m_edit_xml_path.EnableWindow(m_b_flag);
	m_btn_browser_xml_path.EnableWindow(m_b_flag);

	m_edit_xml_directory.EnableWindow(!m_b_flag);
	m_btn_browser_directory.EnableWindow(!m_b_flag);
}
void CTranslateForAndroidDlg::OnBnClickedRadioSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	setRadioEnableForSingle(TRUE);
}


void CTranslateForAndroidDlg::OnBnClickedRadioDirectory()
{
	// TODO: 在此添加控件通知处理程序代码
	setRadioEnableForSingle(FALSE);
}
LONG CTranslateForAndroidDlg::OnMessageReceive(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{	
	case MSG_TYPE::MSG_Processing:
		{
			m_btn_go_excel2xml.EnableWindow(FALSE);
			m_btn_go_xml2excel.EnableWindow(FALSE);

		    m_statusbar_status.SetPaneText(0,L"Processing");
		}
		break;
	case MSG_TYPE::MSG_Finish:
		{
			m_btn_go_excel2xml.EnableWindow(TRUE);
			m_btn_go_xml2excel.EnableWindow(TRUE);

			m_statusbar_status.SetPaneText(0,L"Finish");
			MessageBox(L"Success",L"Prompt");
		}
		break;
	case MSG_TYPE::MSG_Loading:
		{
		    m_statusbar_status.SetPaneText(0,L"Loading");
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

//实现edit control全选
BOOL CTranslateForAndroidDlg::PreTranslateMessage(MSG* pMsg)
{
// TODO: Add your specialized code here and/or call the base class
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
			m_edit_language.SetSel(0,-1);
			m_edit_xml_directory.SetSel(0,-1);
			m_edit_xml_path.SetSel(0,-1);
			m_edit_xml_to_excel.SetSel(0,-1);
		}
		break;
		}
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE; 

return CDialog::PreTranslateMessage(pMsg);
}
void CTranslateForAndroidDlg::OnClose()
{
	CString xml_to_excel_path;
	CString xml_path;
	CString excel_path;
	CString language;
	CString singleFile;
	CString directory;
	CString fuzzy;
	m_edit_xml_to_excel.GetWindowText(xml_to_excel_path);
	m_edit_xml_path.GetWindowText(xml_path);
	m_edit_excel_path.GetWindowText(excel_path);
	m_edit_language.GetWindowText(language);
	m_edit_xml_directory.GetWindowText(directory);
	
	if(m_radio_single.GetCheck()!=0)
	{
		singleFile = "1";
	}else{
		singleFile = "0";
	}
	if(m_check_fuzzy.GetCheck()!=0)
	{
		fuzzy = "1";
	}else{
		fuzzy = "0";
	}
	WriteToFile(xml_to_excel_path,xml_path,excel_path,language,singleFile,directory,fuzzy);
	
	CDialog::OnClose();	
}

void CTranslateForAndroidDlg::OnToolTranslate()
{
	// TODO: 在此添加命令处理程序代码
	CTranslateApiDlg dlg;
	dlg.DoModal();
}

