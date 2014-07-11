
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
END_MESSAGE_MAP()


// CTranslateForAndroidDlg ��Ϣ�������
void ReadFromFile(CString &xml_path,
	CString &excel_path,
	CString &language)
{
	Config::ReadConfig("chinese_xml_path",xml_path.GetBuffer(1024));
	xml_path.ReleaseBuffer();
	Config::ReadConfig("excel_path",excel_path.GetBuffer(1024));
	excel_path.ReleaseBuffer();	
	Config::ReadConfig("language",language.GetBuffer(1024));
	language.ReleaseBuffer();	
}

void WriteToFile(CString xml_path,
	CString excel_path,
	CString language)
{
	Config::WriteConfig("chinese_xml_path",xml_path);
	Config::WriteConfig("excel_path",excel_path);	
	Config::WriteConfig("language",language);	
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
	CString xml_path;
	CString excel_path;
	CString language;
	ReadFromFile(xml_path,excel_path,language);
	m_edit_xml_path.SetWindowTextA(xml_path);
	m_edit_excel_path.SetWindowTextA(excel_path);
	m_edit_language.SetWindowTextA(language);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExcelTool::getInstance()->Open();

	CMarkup xml;

	char xmlfilename[100];
	Util::GetFileDirectory(xmlfilename);
	strcat(xmlfilename,XML_FILE_NAME);     // ������ȡ��Excel�ļ���

	Util::LOG("Load=%d",xml.Load(xmlfilename));

	while(xml.FindChildElem())
	{
	//	Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->Add(xml.GetChildData());
	}	
	ExcelTool::getInstance()->Close();
	MessageBox("success");
}


void CTranslateForAndroidDlg::OnBnClickedButtonTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString excel_path;
	CString xml_path;
	CString language;
	
	m_edit_excel_path.GetWindowTextA(excel_path);
	m_edit_xml_path.GetWindowTextA(xml_path);
	m_edit_language.GetWindowTextA(language);

	if(""==excel_path.Trim() ||
		""==xml_path.Trim() ||
		""==language.Trim())
	{
		MessageBox("Edit Box can not be empty!");
		return;
	}


	ExcelTool::getInstance()->Open(excel_path);
	
	CMarkup xml;

	
	Util::LOG("Load=%d",xml.Load(xml_path));

	

	CString result;
	while(xml.FindChildElem())
	{
		//Util::LOG("%s",xml.GetChildData());
		ExcelTool::getInstance()->GetString(xml.GetChildData(),language,result);
		xml.SetChildData(result);
	}	
	xml.Save(xml_path);
	
	ExcelTool::getInstance()->Close();

	MessageBox("success");
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
	CString xml_path;
	CString excel_path;
	CString language;
	m_edit_xml_path.GetWindowTextA(xml_path);
	m_edit_excel_path.GetWindowTextA(excel_path);
	m_edit_language.GetWindowTextA(language);
	WriteToFile(xml_path,excel_path,language);
	
	CDialog::OnClose();	
}