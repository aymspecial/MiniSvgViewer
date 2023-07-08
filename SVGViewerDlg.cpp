// SVGViewerDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "SVGClog.h"
#include "SVGViewer.h"
#include "SVGViewerDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma region CAboutDlg
// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV サポート

	// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx( IDD_ABOUTBOX )
{}

void CAboutDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CAboutDlg, CDialogEx )
END_MESSAGE_MAP()
#pragma endregion

// CSVGViewerDlg ダイアログ

CSVGViewerDlg::CSVGViewerDlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_SVGVIEWER_DIALOG, pParent ), hBitmap( 0 )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CSVGViewerDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CSVGViewerDlg, CDialogEx )
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_MOVE()
END_MESSAGE_MAP()

// CSVGViewerDlg メッセージ ハンドラー

extern CSVGViewerApp theApp;

BOOL CSVGViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT( ( IDM_ABOUTBOX & 0xFFF0 ) == IDM_ABOUTBOX );
	ASSERT( IDM_ABOUTBOX < 0xF000 );

	CMenu* pSysMenu = GetSystemMenu( FALSE );
	if( pSysMenu != nullptr )
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString( IDS_ABOUTBOX );
		ASSERT( bNameValid );
		if( !strAboutMenu.IsEmpty() )
		{
			pSysMenu->AppendMenu( MF_SEPARATOR );
			pSysMenu->AppendMenu( MF_STRING, IDM_ABOUTBOX, strAboutMenu );
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon( m_hIcon, TRUE );		// 大きいアイコンの設定
	SetIcon( m_hIcon, FALSE );		// 小さいアイコンの設定

	// 初期化
	iniMetrix = new XmlIni( L"WindowMetrix.xml" );
	auto winX = iniMetrix->GetIniInt( "MainWindow", "PosX", 256 );
	auto winY = iniMetrix->GetIniInt( "MainWindow", "PosY", 256 );
	auto winW = iniMetrix->GetIniInt( "MainWindow", "PosW", 1280 );
	auto winH = iniMetrix->GetIniInt( "MainWindow", "PosH", 1024 );
	this->SetWindowPos( this, winX, winY, winW, winH, SWP_NOMOVE | SWP_NOZORDER );

	CCommandLineInfo cmdInfo;
	theApp.ParseCommandLine( cmdInfo );
	wcscpy_s( fileName, cmdInfo.m_strFileName.GetBuffer() );
#ifdef _DEBUG
	if( wcslen( fileName ) == 0 )
		wcscpy_s( fileName, L"W:\\SVGLoader\\Ghostscript_Tiger.svg" );
#endif
	auto hWnd = GetDlgItem( IDC_PICTURE )->GetSafeHwnd();
	int itmWidth;
	int itmHeight;
	RECT r;
	::GetWindowRect( hWnd, &r );
	itmWidth = r.right - r.left;
	itmHeight = r.bottom - r.top;

	hBitmap = SVGClog::LoadSvg2Hbitmap( fileName, itmWidth, itmHeight );

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSVGViewerDlg::OnSysCommand( UINT nID, LPARAM lParam )
{
	if( ( nID & 0xFFF0 ) == IDM_ABOUTBOX )
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand( nID, lParam );
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
// 下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
// これは、Framework によって自動的に設定されます。

void CSVGViewerDlg::OnPaint()
{
	if( IsIconic() )
	{
		CPaintDC dc( this ); // 描画のデバイス コンテキスト

		SendMessage( WM_ICONERASEBKGND, reinterpret_cast<WPARAM>( dc.GetSafeHdc() ), 0 );

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics( SM_CXICON );
		int cyIcon = GetSystemMetrics( SM_CYICON );
		CRect rect;
		GetClientRect( &rect );
		int x = ( rect.Width() - cxIcon + 1 ) / 2;
		int y = ( rect.Height() - cyIcon + 1 ) / 2;

		// アイコンの描画
		dc.DrawIcon( x, y, m_hIcon );
	}
	else
	{
		CDialogEx::OnPaint();
		paintPicture( GetDlgItem( IDC_PICTURE )->GetSafeHwnd() );
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSVGViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>( m_hIcon );
}

void CSVGViewerDlg::SetCommandLine( LPCTSTR aCommand )
{
	TRACE( L"%s\n", aCommand );

	std::wstring allCom( aCommand );
	auto coms = SplitString( aCommand, L" " );
	auto _com = coms[ 1 ];
	_com.erase( std::remove( _com.begin(), _com.end(), '\"' ), _com.end() );
	wcscpy_s( fileName, _com.c_str() );

	RECT wRect;
	auto hWnd = GetDlgItem( IDC_PICTURE )->GetSafeHwnd();
	::GetWindowRect( hWnd, &wRect );
	TRACE( L"Size:%ldx%ld\n", wRect.right - wRect.left, wRect.bottom - wRect.top );
	int itmWidth = wRect.right - wRect.left;
	int itmHeight = wRect.bottom - wRect.top;

	if( hBitmap != 0 )
		DeleteObject( hBitmap );

	// いちいちファイルから読み込みなおす（のもどうかと思うが）
	if( fileName != nullptr )
		hBitmap = SVGClog::LoadSvg2Hbitmap( fileName, itmWidth, itmHeight );

	this->Invalidate( true );
}

void
CSVGViewerDlg::paintPicture( HWND hWnd )
{
	PAINTSTRUCT ps;
	auto hdc = ::BeginPaint( hWnd, &ps );
	RECT rt;
	::GetClientRect( hWnd, &rt );

	// 最初は薄緑で塗る
	FillRect( hdc, &rt, CreateSolidBrush( 0xeeffee ) );

	auto hmemdc = CreateCompatibleDC( hdc );
	SelectObject( hmemdc, hBitmap );
	BitBlt( hdc, 0, 0,
			rt.right - rt.left, rt.bottom - rt.top, hmemdc, 0, 0, SRCCOPY );

	DeleteDC( hmemdc );
	::EndPaint( hWnd, &ps );
}

void CSVGViewerDlg::setWindowMetrix()
{
	if( iniMetrix == nullptr )
		return;

	RECT wRect;
	::GetWindowRect( this->GetSafeHwnd(), &wRect );

	iniMetrix->SetIniInt( "MainWindow", "PosX", wRect.left );
	iniMetrix->SetIniInt( "MainWindow", "PosY", wRect.top );
	iniMetrix->SetIniInt( "MainWindow", "PosW", wRect.right - wRect.left );
	iniMetrix->SetIniInt( "MainWindow", "PosH", wRect.bottom - wRect.top );
	iniMetrix->WriteFlush();
}

void CSVGViewerDlg::OnClose()
{
	DeleteObject( hBitmap );
	delete iniMetrix;

	CDialogEx::OnClose();
}


void CSVGViewerDlg::OnSize( UINT nType, int cx, int cy )
{
	CDialogEx::OnSize( nType, cx, cy );

	RECT wRect;
	auto hWnd = GetDlgItem( IDC_PICTURE )->GetSafeHwnd();
	::GetWindowRect( hWnd, &wRect );
	TRACE( L"Size:%ldx%ld\n", wRect.right - wRect.left, wRect.bottom - wRect.top );
	int itmWidth = wRect.right - wRect.left;
	int itmHeight = wRect.bottom - wRect.top;

	if( hBitmap != 0 )
		DeleteObject( hBitmap );

	// いちいちファイルから読み込みなおす（のもどうかと思うが）
	if( fileName != nullptr )
		hBitmap = SVGClog::LoadSvg2Hbitmap( fileName, itmWidth, itmHeight );

	this->setWindowMetrix();
}


void CSVGViewerDlg::OnMove( int x, int y )
{
	CDialogEx::OnMove( x, y );

	this->setWindowMetrix();
}
