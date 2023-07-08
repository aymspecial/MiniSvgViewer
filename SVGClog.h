#pragma once

#include "TinyTool.h"

class SVGClog
{
public:
	static HBITMAP LoadSvg2Hbitmap( const std::wstring _fileName, int _width, int _height = -1 );
};
