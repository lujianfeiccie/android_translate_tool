
// TranslateForAndroidDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TranslateForAndroid.h"
#include "TranslateForAndroidDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTranslateForAndroidDlg �Ի���




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
END_MESSAGE_MAP()


// CTranslateForAndroidDlg ��Ϣ�������
void ReadFromFile(CString &xml_to_excel,
	CString &xml_path,
	CString &excel_path,
	CString &language,
	CString &singleFile,
	CString &directory,
	CString &fuzzy)
{
	Config::ReadConfig("xml_to_excel_path",xml_to_excel.GetBuffer(1024));
	xml_to_excel.ReleaseBuffer();
	Config::ReadConfig("chinese_xml_path",xml_path.GetBuffer(1024));
	xml_path.ReleaseBuffer();
	Config::ReadConfig("excel_path",excel_path.GetBuffer(1024));
	excel_path.ReleaseBuffer();	
	Config::ReadConfig("language",language.GetBuffer(1024));
	language.ReleaseBuffer();	
	Config::ReadConfig("singleFile",singleFile.GetBuffer(1024));
	singleFile.ReleaseBuffer();	
	Config::ReadConfig("directory",directory.GetBuffer(1024));
	directory.ReleaseBuffer();	
	Config::ReadConfig("fuzzy",fuzzy.GetBuffer(1024));
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
	Config::WriteConfig("xml_to_excel_path",xml_to_excel);
	Config::WriteConfig("chinese_xml_path",xml_path);
	Config::WriteConfig("excel_path",excel_path);	
	Config::WriteConfig("language",language);	
	Config::WriteConfig("singleFile",singleFile);	
	Config::WriteConfig("directory",directory);		
	Config::WriteConfig("fuzzy",fuzzy);		
}
BOOL CTranslateForAndroidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CString xml_to_excel_path;
	CString xml_path;
	CString excel_path;
	CString language;
	CString singleFile;
	CString directory;
	CString fuzzy;
	ReadFromFile(xml_to_excel_path,xml_path,excel_path,language,singleFile,directory,fuzzy);
	m_edit_xml_to_excel.SetWindowTextA(xml_to_excel_path);
	m_edit_xml_path.SetWindowTextA(xml_path);
	m_edit_excel_path.SetWindowTextA(excel_path);
	m_edit_language.SetWindowTextA(language);
	m_edit_xml_directory.SetWindowTextA(directory);
	setRadioEnableForSingle("1"==singleFile);
	m_radio_single.SetCheck("1"==singleFile);
	m_radio_directory.SetCheck("1"!=singleFile);
	m_check_fuzzy.SetCheck("1"==fuzzy);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTranslateForAndroidDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTranslateForAndroidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTranslateForAndroidDlg::OnBnClickedBtnGo()
{
	CString xml_to_excel_path;
	m_edit_xml_to_excel.GetWindowTextA(xml_to_excel_path);

	if(""==xml_to_excel_path.Trim())
	{
			MessageBox("Xml path can't be empty");
			return;
	}
	
	char directory[1024];

	Util::GetDirectoryByFileName(xml_to_excel_path,directory);
	
	strcat(directory,EXCEL_FILE_NAME);

	
	ExcelTool::getInstance()->OpenAndWriteTemplate(directory);

	CMarkup xml;

	
	Util::LOG("Load=%d",xml.Load(xml_to_excel_path));

	while(xml.FindChildElem())
	{
	//	Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->Add(xml.GetChildData());
	}	


	ExcelTool::getInstance()->Close();
	MessageBox("success");
}

void CTranslateForAndroidDlg::ReadAllFilesInDir(CString dir)
{
	   CFileFind fileFinder;
       CString filePath = dir + _T("//*.*");
      
       BOOL bFinished = fileFinder.FindFile(filePath);
       while(bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
       {
              bFinished = fileFinder.FindNextFile();
              if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //����Ŀ¼��ݹ���ô˷���
              {
                     ReadAllFilesInDir(fileFinder.GetFilePath());
              }
              else  //���ж��Ƿ�Ϊtxt�ļ�
              {
                     //��ȡ�ļ�����
                     CString fileName = fileFinder.GetFileName();
					 
                     int dotPos=fileName.ReverseFind('.');
                     CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
                     if(fileExt == _T(".xml"))  //����txt�ļ���ʼ�������
                     {
                     Util::LOG("%s",fileFinder.GetFilePath()); 
					 CString language;
					 m_edit_language.GetWindowTextA(language);
					 WriteXml(fileFinder.GetFilePath(),language);
                     }
              }
       }
 
       fileFinder.Close();
}
void CTranslateForAndroidDlg::WriteXml(CString filePath,CString language)
{
	CMarkup xml;

	Util::LOG("Load=%d",xml.Load(filePath));

	CString result;
	while(xml.FindChildElem())
	{
			//Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->GetString(xml.GetChildData(),language,result,m_check_fuzzy.GetCheck());
		xml.SetChildData(result);
	}	
	xml.Save(filePath);
}
void CTranslateForAndroidDlg::OnBnClickedButtonTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString excel_path;
	CString xml_path;
	CString language;
	CString xml_directory;
	m_edit_excel_path.GetWindowTextA(excel_path);
	m_edit_xml_path.GetWindowTextA(xml_path);
	m_edit_language.GetWindowTextA(language);
	m_edit_xml_directory.GetWindowTextA(xml_directory);

	if(m_radio_single.GetCheck()!=0){
		if(""==xml_path.Trim())
		{
			MessageBox("CHN Xml path can not be empty!");
			return;
		}
	}else{
		if(""==xml_directory.Trim())
		{
			MessageBox("CHN Directory can not be empty!");
			return;
		}
	}
	if(""==excel_path.Trim() ||
		""==language.Trim())
	{
		MessageBox("Excel path or language can not be empty");
		return;
	}

	if(m_radio_single.GetCheck()!=0){
		ExcelTool::getInstance()->Open(excel_path);
	
		WriteXml(xml_path,language);
	
		ExcelTool::getInstance()->Close();

		MessageBox("success");
	}else{
		ExcelTool::getInstance()->Open(excel_path);
		ReadAllFilesInDir(xml_directory);
		ExcelTool::getInstance()->Close();
		MessageBox("success");
	}
}


void CTranslateForAndroidDlg::OnBnClickedBtnXmlBrowser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = "xml files(*.xml)|*.xml||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						(LPCSTR)strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_xml_path.SetWindowTextA(strFileName);
}


void CTranslateForAndroidDlg::OnBnClickedBtnExcelBrowser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = "excel files(*.xls)|*.xls||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						(LPCSTR)strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_excel_path.SetWindowTextA(strFileName);
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
	m_edit_xml_to_excel.GetWindowTextA(xml_to_excel_path);
	m_edit_xml_path.GetWindowTextA(xml_path);
	m_edit_excel_path.GetWindowTextA(excel_path);
	m_edit_language.GetWindowTextA(language);
	m_edit_xml_directory.GetWindowTextA(directory);
	
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

void CTranslateForAndroidDlg::OnBnClickedBtnBrowserToExcel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilter = "xml files(*.xml)|*.xml||";
	CFileDialog FileDlg(true,NULL,NULL,
						OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
						(LPCSTR)strFilter,this);
	if(FileDlg.DoModal()!=IDOK) return;
	CString strFileName = FileDlg.GetPathName();
	m_edit_xml_to_excel.SetWindowTextA(strFileName);
}
CString CTranslateForAndroidDlg::ShowDirectoryDlg()
{
	 TCHAR           szFolderPath[MAX_PATH] = {0};  
        CString         strFolderPath = TEXT("");  
          
        BROWSEINFO      sInfo;  
        ::ZeroMemory(&sInfo, sizeof(BROWSEINFO));  
        sInfo.pidlRoot   = 0;  
        sInfo.lpszTitle   = _T("��ѡ��һ���ļ��У�");  
        sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;  
        sInfo.lpfn     = NULL;  
  
        // ��ʾ�ļ���ѡ��Ի���  
        LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);   
        if (lpidlBrowse != NULL)  
        {  
            // ȡ���ļ�����  
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit_xml_directory.SetWindowTextA(ShowDirectoryDlg());
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	setRadioEnableForSingle(TRUE);
}


void CTranslateForAndroidDlg::OnBnClickedRadioDirectory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	setRadioEnableForSingle(FALSE);
}
