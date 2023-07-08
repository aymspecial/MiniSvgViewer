#include "pch.h"
#include "TinyTool.h"

// UTF8 から SJIS へ変換
void
UTF8ToShiftJis( LPSTR bufShiftJis, LPCWSTR bufUTF8 )
{
	int ret = ::WideCharToMultiByte( CP_ACP, 0, bufUTF8, -1, bufShiftJis, MAX_PATH, NULL, NULL );
}

// SJIS から UTF8 へ変換
void
ShiftJisToUtf8( LPWSTR bufUTF8, LPCSTR bufShiftJis )
{
	int lenUnicode = MultiByteToWideChar( CP_ACP, 0, bufShiftJis, (int)strlen( bufShiftJis ) + 1, bufUTF8, MAX_PATH );
}

// String を separator で分割する
std::vector<std::wstring>
SplitString( const std::wstring inString, const std::wstring separator )
{
	auto ret = std::vector<std::wstring>();
	auto separator_length = separator.length(); // 区切り文字の長さ

	if( separator_length == 0 )
	{
		ret.push_back( inString );
	}
	else
	{
		auto offset = std::string::size_type( 0 );
		while( 1 )
		{
			auto pos = inString.find( separator, offset );
			if( pos == std::string::npos )
			{
				ret.push_back( inString.substr( offset ) );
				break;
			}
			ret.push_back( inString.substr( offset, pos - offset ) );
			offset = pos + separator_length;
		}
	}

	return ret;
}