/*
*
*	Megan Grass
*	March 07, 2024
*
*
*	TODO:
*
*/


#pragma once

#include "std_basic_fstream.h"

#include "std_string.h"


enum class ImageFormat : int
{
	BMP = 0 << 0,
};


/*
	Standard Image
*/
class Standard_Image :
	protected Standard_Exception {
private:

	#pragma pack(push, 1)

	#ifndef BITMAPFILEHEADER
		struct BITMAPFILEHEADER {
			WORD	bfType;
			DWORD	bfSize;
			WORD	bfReserved1;
			WORD	bfReserved2;
			DWORD	bfOffBits;
		};
	#endif

	#ifndef BITMAPINFOHEADER
		struct BITMAPINFOHEADER {
			DWORD	biSize;
			LONG	biWidth;
			LONG	biHeight;
			WORD	biPlanes;
			WORD	biBitCount;
			DWORD	biCompression;
			DWORD	biSizeImage;
			LONG	biXPelsPerMeter;
			LONG	biYPelsPerMeter;
			DWORD	biClrUsed;
			DWORD	biClrImportant;
		};
	#endif

	#ifndef RGBQUAD
		struct RGBQUAD {
			BYTE	rgbBlue;
			BYTE	rgbGreen;
			BYTE	rgbRed;
			BYTE	rgbReserved;
		};
	#endif

	#pragma pack(pop)

	#ifndef LOBYTE
	#define LOBYTE(w)           ((BYTE)(((uint64_t)(w)) & 0xFF))
	#endif

	#ifndef HIBYTE
	#define HIBYTE(w)           ((BYTE)((((uint64_t)(w)) >> 8) & 0xFF))
	#endif

	#ifndef RGB
	#define RGB(r,g,b)          ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	#endif

	#ifndef GetRValue
	#define GetRValue(rgb)      (LOBYTE(rgb))
	#endif

	#ifndef GetGValue
	#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
	#endif

	#ifndef GetBValue
	#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
	#endif

	#ifndef GetAValue
	#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
	#endif

	// Pixels
	std::vector<uint8_t> Pixels;

	// Format
	ImageFormat Format;

	// Width
	uint32_t Width;

	// Height
	uint32_t Height;

	// Depth
	uint32_t Depth;

	// Palette
	std::vector<RGBQUAD> Palette;

	// Get Format
	ImageFormat GetFormat(ImageFormat _Format);

	// Get Depth
	uint32_t GetDepth(uint32_t _Depth);

	// Initialize Palette
	void InitializePalette(void);

	// Get Pixel Size
	uint32_t GetPixelSize(void);

public:

	/*
		Construction
	*/
	explicit Standard_Image(ImageFormat _Format, uint32_t _Width, uint32_t _Height, uint32_t _Depth, DWORD Color = 0) :
		Pixels(),
		Format(ImageFormat::BMP),
		Width(0),
		Height(0),
		Depth(0),
		Palette()
	{
		Create(_Format, _Width, _Height, _Depth, Color);
	}

	explicit Standard_Image(void) :
		Pixels(),
		Format(ImageFormat::BMP),
		Width(0),
		Height(0),
		Depth(0),
		Palette()
	{
	}

	virtual ~Standard_Image(void) noexcept
	{
		Close();
	}

	/*
		Create a blank canvas
	*/
	void Create(ImageFormat _Format, uint32_t _Width, uint32_t _Height, uint32_t _Depth, DWORD Color = 0);

	/*
		Close
	*/
	void Close(void);

	/*
		Get width
	*/
	[[nodiscard]] uint32_t GetWidth(void) const { return Width; }

	/*
		Get Height
	*/
	[[nodiscard]] uint32_t GetHeight(void) const { return Height; }

	/*
		Get Depth
	*/
	[[nodiscard]] uint32_t GetDepth(void) const { return Depth; }

	/*
		Get Palette
	*/
	[[nodiscard]] std::vector<RGBQUAD>& GetPalette(void) { return Palette; }

	/*
		Get Pixels
	*/
	[[nodiscard]] std::vector<uint8_t>& GetData(void) { return Pixels; }

	/*
		Set Palette
	*/
	void SetPalette(size_t iPalette, DWORD Color);

	/*
		Get Pixel
	*/
	DWORD GetPixel(uint32_t X, uint32_t Y);

	/*
		Set Pixel
	*/
	void SetPixel(uint32_t X, uint32_t Y, DWORD Color);

	/*
		Save as Bitmap
	*/
	bool SaveAsBitmap(std::filesystem::path Path);

};