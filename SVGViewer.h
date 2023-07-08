// SVGViewer.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once
#if !defined(AFX_SINGLETON_H__418129AE_FFE7_40DE_B3A3_13A7BD3C44FD__INCLUDED_)
#define AFX_SINGLETON_H__418129AE_FFE7_40DE_B3A3_13A7BD3C44FD__INCLUDED_

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "SingleInstance.h"		

// CSVGViewerApp:
// このクラスの実装については、SVGViewer.cpp を参照してください
//

class CSVGViewerApp : public CWinApp, public CSingleInstance
{
public:
	CSVGViewerApp();
	virtual ~CSVGViewerApp() {};

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVGViewerApp)
public:
	virtual BOOL InitInstance();
	virtual void WakeUp ( LPCTSTR aCommandLine ) const ;

	//}}AFX_VIRTUAL

	// Implementation

	//{{AFX_MSG(CSVGViewerApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_SINGLETON_H__418129AE_FFE7_40DE_B3A3_13A7BD3C44FD__INCLUDED_)