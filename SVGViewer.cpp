// SVGViewer.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "SVGViewer.h"
#include "SVGViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSVGViewerApp

BEGIN_MESSAGE_MAP( CSVGViewerApp, CWinApp )
	ON_COMMAND( ID_HELP, &CWinApp::OnHelp )
END_MESSAGE_MAP()


// CSVGViewerApp の構築

CSVGViewerApp::CSVGViewerApp()
{
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CSVGViewerApp オブジェクト

CSVGViewerApp theApp;

void CSVGViewerApp::WakeUp( LPCTSTR aCommandLine ) const
// Name:        WakeUp 
// Type:        Function
// Description: virtual override for wake up, so we can process the command line
{
	// Call parent class to handle the basic functionality
	CSingleInstance::WakeUp( aCommandLine );

	// Send new command line to the dialog
	CSVGViewerDlg* lSingletonDlg = (CSVGViewerDlg*)m_pMainWnd;
	if( lSingletonDlg )
	{
		lSingletonDlg->SetCommandLine( aCommandLine );
	}
}

// CSVGViewerApp の初期化

BOOL CSVGViewerApp::InitInstance()
{
	// We use a GUID here, so that we are sure the string is 100% unique
	if( CSingleInstance::Create( L"9B28AD97-F2F4-4A74-8417-742C23A94528" ) == FALSE )
		return FALSE;

	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof( InitCtrls );
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx( &InitCtrls );

	CWinApp::InitInstance();

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerWindows ) );

	CSVGViewerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

