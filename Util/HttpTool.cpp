#include "StdAfx.h"
#include "HttpTool.h"

CHttpTool::CHttpTool(void)
{
}

CHttpTool::~CHttpTool(void)
{
}

void CHttpTool::request(char* url,HTTP_TOOL_CALL_BACK callback)
{
	DWORD dwServiceType;
	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;

	BOOL   OK=AfxParseURL(   //词法分析   	
		url,   //被分析URL串   		
		dwServiceType,   //服务类型，ftp，http等   		
		strServerName,   //服务器名   		
		strObject,   //URL中被查询对象   		
		nPort);   //URL指定的端口，可能为空  

	CInternetSession session;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000 * 20);
	session.SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	CHttpConnection* pConnection = session.GetHttpConnection(strServerName,nPort);
	CHttpFile* pFile = pConnection->OpenRequest( CHttpConnection::HTTP_VERB_GET,
												strObject);

	CString szHeaders = "Accept: audio/x-aiff, audio/basic, audio/midi,\
						 audio/mpeg, audio/wav, image/jpeg, image/gif, image/jpg, image/png,\
						 image/mng, image/bmp, text/plain, text/html, text/htm\r\n";

	pFile->AddRequestHeaders(szHeaders);

	Util::LOG("SendRequest");
	pFile->SendRequest();

	DWORD dwRet;
	pFile->QueryInfoStatusCode(dwRet);


	CString result;
	if(dwRet != HTTP_STATUS_OK)
	{
		CString errText;
		errText.Format("请求出错，错误码：%d", dwRet);
		AfxMessageBox(errText);
	}
	else
	{
		int len = pFile->GetLength();
		char buf[2000];
		int numread;
		CString filepath;
		CString strFile = "response.txt";
		filepath.Format(".\\%s", strFile);
		//CFile myfile( filepath,
			//		  CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		while ((numread = pFile->Read(buf,sizeof(buf)-1)) > 0)
		{
			buf[numread] = '\0';
			result += buf;
			//myfile.Write(buf, numread);
		}
		//myfile.Close();
	}

	session.Close();
	pFile->Close(); 
	delete pFile;

	if(NULL != callback)
	{
		callback(dwRet,result.GetBuffer());
		result.ReleaseBuffer();
	}
	//Util::LOG("Finish");
}