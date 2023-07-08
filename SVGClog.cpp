#include "pch.h"
#include "SVGClog.h"
#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

HBITMAP
SVGClog::LoadSvg2Hbitmap( const std::wstring _fileName, int _width, int _height )
{
	HBITMAP hReturn {};
	NSVGimage* image = NULL;
	NSVGrasterizer* raster = NULL;
	unsigned char* img;
	char filename[ MAX_PATH ] {};

	UTF8ToShiftJis( filename, _fileName.c_str() );
	int iWidth = 0;
	int iHeight = 0;
	float scale = 1.0f;

	TRACE( "parsing %s\n", filename );
	image = nsvgParseFromFile( filename, "px", 96.0f );
	if( image == NULL )
	{
		TRACE( "Could not open SVG image.\n" );
		goto error;
	}
	iWidth = (int)image->width;
	iHeight = (int)image->height;

	// Scale の計算
	if( _height == -1 )  // 「_height = おまかせ」の場合
	{
		scale = (float)_width / iWidth;
	}
	// 指定されている場合
	else
	{
		float indicateRate = (float)_width / _height;
		float svgRate = (float)iWidth / iHeight;

		// SVGデータの横がはみ出ている場合
		if( indicateRate < svgRate )
		{
			scale = (float)_width / iWidth;
			TRACE( "Gate A:%f _width:%d,_height:%d\n", scale, _width, _height );
		}
		// 縦がはみ出ている場合
		else
		{
			scale = (float)_height / iHeight;
			TRACE( "Gate B:%f _width:%d,_height:%d\n", scale,_width, _height );
		}
	}

	_width = (int)( scale * iWidth );
	_height = (int)( scale * iHeight );

	raster = nsvgCreateRasterizer();
	if( raster == NULL )
	{
		TRACE( "Could not init rasterizer.\n" );
		goto error;
	}

	img = (unsigned char*)malloc( _width * _height * 4 );
	if( img == NULL )
	{
		TRACE( "Could not alloc image buffer.\n" );
		goto error;
	}

	TRACE( "rasterizing image %d x %d\n", _width, _height );
	nsvgRasterize( raster, image, 0, 0, scale, img, _width, _height, _width * 4 );


#pragma warning (disable: 6011)
	for( int iy = 0; iy < _height; iy++ )
	{
		int pLine = iy * _width * 4;
		for( int ix = 0; ix < _width; ix++ )
		{
			int pPixel = pLine + ix * 4;
			char work = img[ pPixel + 0 ];
			img[ pPixel + 0 ] = img[ pPixel + 2 ];
			img[ pPixel + 2 ] = work;
		}
	}

	// ビットマップ作成
	hReturn = CreateBitmap( 
		_width,		// 幅
		_height,     // 高さ
		4,			// カラープレーンの数
		8,			// 1ピクセルのビット数(色数)
		img );		// ピクセルの配列
	free( img );

error:
	nsvgDeleteRasterizer( raster );
	nsvgDelete( image );

	return hReturn;
}
