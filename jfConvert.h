// jfConvert.h: interface for the CjfConvert class.
// BigLee 2009.01.06 Shanghai,China
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JFCONVERT_H__88C5CCE8_ACF0_44D3_B657_D58B463B2807__INCLUDED_)
#define AFX_JFCONVERT_H__88C5CCE8_ACF0_44D3_B657_D58B463B2807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TOTAL_CHAR		2359
#define TOTAL_CHAR_BUF	7080
class CjfConvert  
{
public:
	static CString strCvt(const char *psz,BOOL bToFt);
	static CString strJ2F(const wchar_t *psz);	
	static CString strJ2F(const char *psz);
	static CString strF2J(const char *psz);
	static char * F2J(char *psz);
	static char * J2F(char *psz);	
	CjfConvert();
	virtual ~CjfConvert();
	static char m_szJJ[TOTAL_CHAR_BUF];
	static char m_szJF[TOTAL_CHAR_BUF];
	static char m_szFJ[TOTAL_CHAR_BUF];
	static char m_szFF[TOTAL_CHAR_BUF];

};

#endif // !defined(AFX_JFCONVERT_H__88C5CCE8_ACF0_44D3_B657_D58B463B2807__INCLUDED_)
