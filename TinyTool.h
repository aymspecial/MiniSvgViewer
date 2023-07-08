#pragma once
#include <sys/types.h>
#include <sys/stat.h>

void UTF8ToShiftJis( LPSTR bufShiftJis, LPCWSTR bufUTF8 );
void ShiftJisToUtf8( LPWSTR bufUTF8, LPCSTR bufShiftJis );

std::vector<std::wstring> SplitString( const std::wstring inString, const std::wstring separator );