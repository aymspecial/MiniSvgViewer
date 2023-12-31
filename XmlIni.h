﻿#pragma once

#include "TinyTool.h"
#include "tinyxml2.h"

#ifdef _DEBUG
#pragma comment(lib, "tinyxml2d.lib")
#else
#pragma comment(lib, "tinyxml2.lib")
#endif

using namespace tinyxml2;

class XmlIni
{
private:
	XmlIni() {}; // 引数無しでは使えない
	tinyxml2::XMLDocument* doc;

	WCHAR lpInifileFullPath[ MAX_PATH ]	{ 0 };

	void makeFullFolder( LPWSTR path );

public:
	XmlIni( LPWSTR inifileName );
	~XmlIni();

	// Write Value
	void SetIniString( LPSTR section, LPSTR key, LPSTR _value );
	void SetIniString( LPSTR section, LPSTR key, LPCWSTR _value );
	void SetIniInt( LPSTR section, LPSTR key, int _value );

	// Get Value
	LPSTR	GetIniString( LPSTR section, LPSTR key, LPSTR defaultValue );
	std::wstring GetIniStringW( LPSTR section, LPSTR key, LPSTR defaultValue );
	int		GetIniInt( LPSTR section, LPSTR key, int defaultValue );

	void ClearDoc();
	void WriteFlush();
};

