/*
*
*	Megan Grass
*	March 07, 2024
*
*/


#pragma once

#include "std_basic_fstream.h"

#include "std_string.h"

#ifdef GetPalette
#undef GetPalette
#endif

#ifdef SetGetPalette
#undef SetGetPalette
#endif

#ifdef GetPixel
#undef GetPixel
#endif

#ifdef SetPixel
#undef SetPixel
#endif


#pragma pack(push, 1)


struct Pixel_4bpp
{
	std::uint8_t Pix0 : 4;
	std::uint8_t Pix1 : 4;
};


struct Pixel_8bpp
{
	std::uint8_t Pixel : 8;
};


struct Pixel_16bpp
{
	std::uint16_t B : 5;
	std::uint16_t G : 5;
	std::uint16_t R : 5;
	std::uint16_t A : 1;
	explicit Pixel_16bpp(void) : B(0), G(0), R(0), A(0) {}
	explicit Pixel_16bpp(uint16_t Pixel) : B(Pixel & 0x1F), G((Pixel & 0x7E0) >> 5), R((Pixel & 0xF800) >> 10), A((Pixel & 0x8000) >> 15) {}
};


struct Pixel_16bppL
{
	std::uint16_t R : 5;
	std::uint16_t G : 5;
	std::uint16_t B : 5;
	std::uint16_t A : 1;
	explicit Pixel_16bppL(void) : R(0), G(0), B(0), A(0) {}
	explicit Pixel_16bppL(std::uint16_t R, std::uint16_t G, std::uint16_t B, std::uint16_t A) : R(R), G(G), B(B), A(A) {}
	explicit Pixel_16bppL(uint16_t Pixel) : R(Pixel & 0x1F), G((Pixel & 0x7E0) >> 5), B((Pixel & 0xF800) >> 10), A((Pixel & 0x8000) >> 15) {}
	bool operator ! (void) const { return !this->R && !this->G && !this->B && !this->A; }
	bool operator = (const Pixel_16bppL& External) { std::memcpy(this, &External, sizeof(Pixel_16bppL)); return true; }
	bool operator == (const Pixel_16bppL& External) const { return (this->R == External.R) && (this->G == External.G) && (this->B == External.B) && (this->A == External.A); }
	bool operator != (const Pixel_16bppL& External) const { return (this->R != External.R) || (this->G != External.G) || (this->B != External.B) || (this->A != External.A); }
	[[nodiscard]] std::uint8_t Red(void) const { return ((R << 3) | (R >> 2)); }
	[[nodiscard]] std::uint8_t Green(void) const { return ((G << 3) | (G >> 2)); }
	[[nodiscard]] std::uint8_t Blue(void) const { return ((B << 3) | (B >> 2)); }
	[[nodiscard]] bool Alpha(void) const { return A; }
};


struct Pixel_24bpp
{
	std::uint8_t B : 8;
	std::uint8_t G : 8;
	std::uint8_t R : 8;
};


struct Pixel_24bppL
{
	std::uint8_t R : 8;
	std::uint8_t G : 8;	
	std::uint8_t B : 8;
	explicit Pixel_24bppL(void) : R(0), G(0), B(0) {}
	explicit Pixel_24bppL(std::uint8_t R, std::uint8_t G, std::uint8_t B) : R(R), G(G), B(B) {}
};


struct Pixel_32bpp
{
	std::uint8_t B : 8;
	std::uint8_t G : 8;
	std::uint8_t R : 8;
	std::uint8_t A : 8;
};


struct Pixel_32bppL
{
	std::uint8_t R : 8;
	std::uint8_t G : 8;
	std::uint8_t B : 8;
	std::uint8_t A : 8;
};


typedef struct Pixel_4bpp Pixel_4bpp;

typedef struct Pixel_8bpp Pixel_8bpp;

typedef struct Pixel_16bpp Pixel_16bpp;

typedef struct Pixel_24bpp Pixel_24bpp;

typedef struct Pixel_32bpp Pixel_32bpp;

typedef struct Pixel_16bppL Pixel_16bppL;

typedef struct Pixel_24bppL Pixel_24bppL;

typedef struct Pixel_32bppL Pixel_32bppL;


struct Microsoft_RIFF_Palette
{
	std::int8_t RIFF[4];
	std::uint32_t FileSize;
	std::int8_t PAL[4];
	std::int8_t data[4];
	std::uint16_t DataSize;
	std::uint16_t Version;
	std::uint16_t nColors;
};


#pragma pack(pop)

enum class ImageType : int32_t
{
	null = 0,						// no data
	RAW = (1 << 0),					// raw data
	BMP = (1 << 1),					// Bitmap Graphic (*.BMP) File
	PAL = (1 << 2),					// Microsoft RIFF Palette (*.PAL) File
#ifdef LIB_PNG
	PNG = (1 << 3),					// Portable Network Graphics (*.PNG)
#endif
#ifdef LIB_JPEG
	JPG = (1 << 4),					// Joint Photographic Experts Group (*.JPEG)
#endif
	TM2 = (1 << 28),				// Sony PlayStation 2 Texture Map (*.TM2;*.CL2)
	PXL = (1 << 29),				// Sony PlayStation Texture Pixels (*.PXL)
	CLT = (1 << 30),				// Sony PlayStation Texture CLUT (*.CLT)
	TIM = (1 << 31),				// Sony PlayStation Texture Image (*.TIM)
};

enum class ImageIO : int32_t
{
	null = 0,						// no operation
	Raw = (1 << 0),					// r/w raw data
	Palette = (1 << 1),				// r/w palette data (incompatible with Pixel when Raw is active)
	Pixel = (1 << 2),				// r/w pixel data (incompatible with Palette when Raw is active)
	PaletteSingle = (1 << 3),		// r/w single palette
	PaletteAdd = (1 << 4),			// append palette data
	OpenOnComplete = (1 << 26),		// open file type after operation (incompatible with Raw)
	SaveAll = (1 << 27),			// export multiple images as file type (incompatible with Import)
	SaveAs = (1 << 28),				// export image as file/type (incompatible with Import)
	Truncate = (1 << 29),			// truncate file to image size + file pointer on write
	Import = (1 << 30),				// import image/data from file (incompatible with SaveAs/Multi)
	Write = (1 << 31),				// write image/data to file

	IO = (Import | Write),			// write all data from file type to another file

	All = (Palette | Pixel),		// r/w palette and pixel data
	New = (Write | Truncate),		// write image/data to truncated file

	WriteAll = (Write | All),		// write all palette and pixel data
	WritePalette = (Write | Palette),	// write palette data
	WritePixel = (Write | Pixel),	// write pixel data

	ImportAll = (Import | All),		// import all palette and pixel data
	ImportPalette = (Import | Palette),	// import palette data
	ImportPixel = (Import | Pixel),	// import pixel data

	SaveAsNew = (SaveAs | New),		// save data as truncated file/type
	SaveMultiNew = (SaveAll | New),	// write multiple images to truncated files

	WriteRawPalette = (Raw | WritePalette),	// write raw palette data only (incompatible with ReadRawPalette, WriteRawPixel and ReadRawPixel)
	ReadRawPalette = (Raw | ImportPalette),	// read raw palette data only (incompatible with WriteRawPalette, WriteRawPixel and ReadRawPixel)
	WriteRawPixel = (Raw | WritePixel),	// write raw pixel data only (incompatible with WriteRawPalette, ReadRawPalette and ReadRawPixel)
	ReadRawPixel = (Raw | ImportPixel),	// read raw pixel data only (incompatible with WriteRawPalette, ReadRawPalette and WriteRawPixel)

	PaletteSingleAdd = (Palette | PaletteSingle | PaletteAdd),	// r/w single palette and append
};

static ImageIO operator | (ImageIO _Mode0, ImageIO _Mode1)
{
	return static_cast<ImageIO>(std::to_underlying(_Mode0) | std::to_underlying(_Mode1));
}


#if defined(_WIN64)
typedef std::uint64_t ULONG_PTR, * PULONG_PTR;
#else
typedef unsigned long ULONG_PTR, * PULONG_PTR;
#endif
typedef ULONG_PTR DWORD_PTR, * PDWORD_PTR;

typedef DWORD COLORREF;

#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define GetRValue(rgb)		(LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)		(LOBYTE((rgb)>>16))
#define GetAValue(rgb)      (LOBYTE((rgb)>>24))


/*
	Standard Image
*/
class Standard_Image {
private:

	#pragma pack(push, 1)

#ifndef _WINDOWS

#define far
#define FAR           far
#define near
#define NEAR          near
#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L
#define BI_JPEG       4L
#define BI_PNG        5L

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

#ifndef PBITMAPINFO
		typedef struct tagBITMAPINFO
		{
			BITMAPINFOHEADER    bmiHeader;
			RGBQUAD             bmiColors[1];
		} BITMAPINFO, FAR* LPBITMAPINFO, * PBITMAPINFO;
#endif

#endif

	#pragma pack(pop)

	WORD m_Depth;
	LONG m_Width;
	LONG m_Height;
	std::vector<RGBQUAD> m_Palette;
	std::vector<uint8_t> m_Pixels;

	// Flag
	bool b_Open;

	// Get individual pixel size
	[[nodiscard]] uint16_t GetPixelSize(void)
	{
		switch (m_Depth)
		{
		case 4: return sizeof(Pixel_4bpp);
		case 8: return sizeof(Pixel_8bpp);
		case 16: return sizeof(Pixel_16bpp);
		case 24: return sizeof(Pixel_24bpp);
		case 32: return sizeof(Pixel_32bpp);
		default: return 0;
		}
	}

public:

	Standard_String Str;

	explicit Standard_Image(void) :
		m_Depth(0),
		m_Width(0),
		m_Height(0),
		m_Palette(),
		m_Pixels(),
		b_Open(false)
	{
	}

	explicit Standard_Image(WORD Depth, LONG Width, LONG Height, DWORD CanvasColor = NULL) :
		m_Depth(0),
		m_Width(0),
		m_Height(0),
		m_Palette(),
		m_Pixels(),
		b_Open(false)
	{
		Create(Depth, Width, Height, CanvasColor);
	}

	~Standard_Image(void) = default;

	/*
		Is the texture open?
	*/
	[[nodiscard]] bool IsOpen(void) const { return b_Open; }

	/*
		Does the texture have either palette or pixel data?
	*/
	bool IsValid(void) const { return !(m_Pixels.empty() && m_Palette.empty()); }

	/*
		Clear all data and declare texture as closed
	*/
	void Close(void);

	/*
		Get bits per pixel
	*/
	[[nodiscard]] WORD GetDepth(void) const { return m_Depth; }

	/*
		Get pixel width
	*/
	[[nodiscard]] LONG GetWidth(void) const { return m_Width; }

	/*
		Get pixel height
	*/
	[[nodiscard]] LONG GetHeight(void) const { return m_Height; }

	/*
		Get/Set palette data
	*/
	[[nodiscard]] std::vector<RGBQUAD>& GetPalette(void) { return m_Palette; }

	/*
		Get/Set pixel data
	*/
	[[nodiscard]] std::vector<uint8_t>& GetData(void) { return m_Pixels; }

	/*
		Get palette color
	*/
	RGBQUAD GetPaletteColor(std::size_t iColor) const { return iColor < m_Palette.size() ? m_Palette[iColor] : RGBQUAD(); }

	/*
		Set palette color
		- color data: BGRA (8:8:8:8)
	*/
	void SetPalette(std::size_t iColor, DWORD Color);

	/*
		Set palette color
	*/
	void SetPalette(std::size_t iColor, RGBQUAD Color);

	/*
		Get pixel data
		- return value:
		  4bpp/8bpp: palette index (0-255)
		  16bpp: BGRA (5:5:5:1)
		  24bpp/32bpp: BGRA (8:8:8:8)
	*/
	DWORD GetPixel(uint32_t X, uint32_t Y);

	/*
		Set pixel data
		- color data:
		  4bpp/8bpp: palette index (0-255)
		  16bpp: BGRA (5:5:5:1)
		  24bpp/32bpp: BGRA (8:8:8:8)
	*/
	void SetPixel(uint32_t X, uint32_t Y, DWORD Color);

	/*
		Get 16-bit color from pixel data
	*/
	[[nodiscard]] Pixel_16bpp Get16bpp(uint32_t X, uint32_t Y) { return *reinterpret_cast<Pixel_16bpp*>(&m_Pixels[(size_t)(X * m_Depth / 8) + (size_t)((m_Height - Y - 1) * (m_Width * (m_Depth / 8)))]); }

	/*
		Get 24-bit color from pixel data
	*/
	[[nodiscard]] Pixel_24bpp Get24bpp(uint32_t X, uint32_t Y) { return *reinterpret_cast<Pixel_24bpp*>(&m_Pixels[(size_t)(X * m_Depth / 8) + (size_t)((m_Height - Y - 1) * (m_Width * (m_Depth / 8)))]); }

	/*
		Get 32-bit color from pixel data
	*/
	[[nodiscard]] Pixel_32bpp Get32bpp(uint32_t X, uint32_t Y) { return *reinterpret_cast<Pixel_32bpp*>(&m_Pixels[(size_t)(X * m_Depth / 8) + (size_t)((m_Height - Y - 1) * (m_Width * (m_Depth / 8)))]); }

	/*
		Decompress RLE data (4-bit/8-bit)
	*/
	bool DecompressRLE(WORD Depth, LONG Width, LONG Height, const std::vector<uint8_t>& Input, std::vector<uint8_t>& Output);

	/*
		Decompress bitfields data
	*/
	bool DecompressBitfields(WORD Depth, LONG Width, LONG Height, const std::vector<uint8_t>& Input, std::vector<uint8_t>& Output, uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t Alpha);

#ifdef LIB_JPEG
	/*
		Decompress JPEG data
	*/
	bool DecompressJPEG(const std::vector<uint8_t>& Input, std::vector<uint8_t>& OutPixels, WORD& OutDepth, LONG& OutWidth, LONG& OutHeight);

	/*
		Open Joint Photographic Experts Group (*.JPEG) file
	*/
	bool OpenJPEG(std::filesystem::path Path, std::uintmax_t pSource = 0);

	/*
		Open Quasi-JPEG file
	*/
	bool OpenQuasiJPEG(StdFile& File, std::uintmax_t pSource);

	/*
		Open Quasi-JPEG file
	*/
	bool OpenQuasiJPEG(std::filesystem::path Path, std::uintmax_t pSource = 0);

	/*
		Save Joint Photographic Experts Group (*.JPEG) file
	*/
	bool SaveJPG(std::filesystem::path Path, std::uintmax_t pSource = 0, bool b_Truncate = true);
#endif

#ifdef LIB_PNG
	/*
		Decompress PNG data
	*/
	bool DecompressPNG(const std::vector<uint8_t>& Input, std::vector<uint8_t>& OutPixels, std::vector<RGBQUAD> OutPalette);

	/*
		Open Portable Network Graphics (*.PNG) file
	*/
	bool OpenPNG(std::filesystem::path Path, std::uintmax_t pSource = 0);

	/*
		Save Portable Network Graphics (*.PNG) file
	*/
	bool SavePNG(std::filesystem::path Path, std::uintmax_t pSource = 0, bool b_Truncate = true);
#endif

	/*
		Create bitmap/raster
		- canvas color data:
		  4bpp/8bpp: palette index (0-255)
		  16bpp: BGRA (5:5:5:1)
		  24bpp/32bpp: BGRA (8:8:8:8)
	*/
	bool Create(WORD Depth, LONG Width, LONG Height, DWORD CanvasColor = NULL);

	/*
		Open Bitmap Graphic (*.BMP) file
	*/
	bool OpenBMP(std::filesystem::path Path, std::uintmax_t pSource = 0);

	/*
		Save Bitmap Graphic (*.BMP) file
	*/
	bool SaveBMP(std::filesystem::path Path, std::uintmax_t pSource = 0, bool b_Truncate = true);

	/*
		Save Microsoft RIFF Palette (*.PAL) file
	*/
	void SavePAL(std::filesystem::path Path);

};