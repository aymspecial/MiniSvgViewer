#pragma once

#include "XmlIni.h"

// SVGViewerDlg.h : ヘッダー ファイル

// CSVGViewerDlg ダイアログ
class CSVGViewerDlg : public CDialogEx
{
	// コンストラクション
public:
	CSVGViewerDlg( CWnd* pParent = nullptr );	// 標準コンストラクター

	// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SVGVIEWER_DIALOG };
#endif

protected:
	virtual void DoDataExchange( CDataExchange* pDX );	// DDX/DDV サポート

	// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	wchar_t fileName[ MAX_PATH ] {};
	HBITMAP hBitmap = 0;
	void paintPicture( HWND hWnd );
	XmlIni* iniMetrix { 0 };
	void setWindowMetrix();

public:
	afx_msg void OnClose();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnMove( int x, int y );

	void SetCommandLine ( LPCTSTR aCommand );
};
