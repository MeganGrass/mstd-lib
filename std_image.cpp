/*
*
*	Megan Grass
*	March 07, 2024
*
*
*	TODO: 
*
*/


#include "std_image.h"


/*
	Get Format
*/
ImageFormat Standard_Image::GetFormat(ImageFormat _Format) try
{
	switch (_Format)
	{
	case ImageFormat::BMP:
		return ImageFormat::BMP;
	default:
		throw std::exception("Unsupported Image Format");
	}
}
catch (...) { Exception(std::current_exception(), false); return ImageFormat::BMP; }


/*
	Get Depth
*/
uint32_t Standard_Image::GetDepth(uint32_t _Depth) try
{
	switch (_Depth)
	{
	case 1:
	case 4:
	case 8:
	case 16:
	case 24:
	case 32:
		return _Depth;
	default:
		throw std::exception("Unsupported Image Depth");
	}
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Initialize Palette
*/
void Standard_Image::InitializePalette(void) try
{
	uint32_t Size = 0;
	switch (Depth)
	{
	case 1:
		Size = 4 * sizeof(RGBQUAD);
		Palette.resize(Size);
		Palette[1].rgbRed = 0xFF;
		Palette[1].rgbGreen = 0xFF;
		Palette[1].rgbBlue = 0xFF;
		Palette[1].rgbReserved = 0;
		break;
	case 4:
		Size = 16 * sizeof(RGBQUAD);
		Palette.resize(Size);
		for (uint32_t i = 0; i < 16; i++)
		{
			Palette[i].rgbRed = 0xFF;
			Palette[i].rgbGreen = 0xFF;
			Palette[i].rgbBlue = 0xFF;
			Palette[i].rgbReserved = 0;
		}
		break;
	case 8:
		Size = 256 * sizeof(RGBQUAD);
		Palette.resize(Size);
		for (uint32_t i = 0; i < 256; i++)
		{
			Palette[i].rgbRed = 0xFF;
			Palette[i].rgbGreen = 0xFF;
			Palette[i].rgbBlue = 0xFF;
			Palette[i].rgbReserved = 0;
		}
		break;
	default:
		Palette.clear();
		break;
	}
}
catch (...) { Exception(std::current_exception()); }


/*
	Get Pixel Size
*/
uint32_t Standard_Image::GetPixelSize(void) try
{
	switch (Depth)
	{
	case 1:
		return 1;
	case 4:
		return 1;
	case 8:
		return 1;
	case 16:
		return 2;
	case 24:
		return 3;
	case 32:
		return 4;
	default:
		throw std::exception("Unsupported Image Depth");
	}
}
catch (...) { Exception(std::current_exception()); return 0; }


/*
	Create
*/
void Standard_Image::Create(ImageFormat _Format, uint32_t _Width, uint32_t _Height, uint32_t _Depth, DWORD Color)
{
	Format = GetFormat(_Format);
	Width = _Width;
	Height = _Height;
	Depth = GetDepth(_Depth);
	InitializePalette();
	uint32_t Size = Width * Height * GetPixelSize();
	if (Depth == 4) { Size = (Width * Height) / 2; }
	Pixels.resize(Size);
	for (uint32_t Y = 0; Y < Height; Y++)
	{
		for (uint32_t X = 0; X < Width; X++)
		{
			SetPixel(X, Y, Color);
		}
	}
}


/*
	Close
*/
void Standard_Image::Close(void)
{
	Width = 0;
	Height = 0;
	Depth = 0;
	Palette.clear();
	Pixels.clear();
}


/*
	Set Palette
*/
void Standard_Image::SetPalette(size_t iPalette, DWORD Color)
{
	if (iPalette < Palette.size())
	{
		Palette[iPalette].rgbRed = GetRValue(Color);
		Palette[iPalette].rgbGreen = GetGValue(Color);
		Palette[iPalette].rgbBlue = GetBValue(Color);
		Palette[iPalette].rgbReserved = GetAValue(Color);
	}
}


/*
	Get Pixel
*/
DWORD Standard_Image::GetPixel(uint32_t X, uint32_t Y)
{
	uint32_t Offset = (Height - Y - 1) * (Width * (Depth / 8));

	uint32_t Pixel = (X * Depth / 8) + Offset;

	uint32_t Shift = 0;

	uint32_t Mask = 0;

	switch (Depth)
	{
	case 4:
		Offset = (Height - Y - 1) * (Width / 2);
		Pixel = (X / 2) + Offset;
		return Pixels.data()[Pixel];
	case 8:
		return Pixels.data()[Pixel];
	case 16:
		return (Pixels.data()[Pixel + 0] << 8) | Pixels.data()[Pixel + 1];
	case 24:
		return (Pixels.data()[Pixel + 0] << 16) | (Pixels.data()[Pixel + 1] << 8) | Pixels.data()[Pixel + 2];
	case 32:
		return (Pixels.data()[Pixel + 0] << 24) | (Pixels.data()[Pixel + 1] << 16) | (Pixels.data()[Pixel + 2] << 8) | Pixels.data()[Pixel + 3];
	default:
		return 0;
	}
}


/*
	Set Pixel
*/
void Standard_Image::SetPixel(uint32_t X, uint32_t Y, DWORD Color)
{
	uint32_t Offset = (Height - Y - 1) * (Width * (Depth / 8));

	uint32_t Pixel = (X * Depth / 8) + Offset;

	uint32_t Shift = 0;

	uint32_t Mask = 0;

	switch (Depth)
	{
	case 4:
		Offset = (Height - Y - 1) * (Width / 2);
		Pixel = (X / 2) + Offset;
		Pixels.data()[Pixel] = GetRValue(Color);
		break;
	case 8:
		Pixels.data()[Pixel] = GetRValue(Color);
		break;
	case 16:
		Pixels.data()[Pixel + 0] = GetRValue(Color);
		Pixels.data()[Pixel + 1] = GetGValue(Color);
		break;
	case 24:
		Pixels.data()[Pixel + 0] = GetRValue(Color);
		Pixels.data()[Pixel + 1] = GetGValue(Color);
		Pixels.data()[Pixel + 2] = GetBValue(Color);
		break;
	case 32:
		Pixels.data()[Pixel + 0] = GetRValue(Color);
		Pixels.data()[Pixel + 1] = GetGValue(Color);
		Pixels.data()[Pixel + 2] = GetBValue(Color);
		Pixels.data()[Pixel + 3] = GetAValue(Color);
		break;
	}
}


/*
	Get bitmap info
*/
PBITMAPINFO Standard_Image::GetBitmapInfo(void) const
{
	// biSizeImage
	std::uint32_t biSizeImage = Width * Height * (Depth / 8);
	std::uint32_t Padding = (4 - (Width * Depth) % 4) % 4;
	biSizeImage += Padding * Height;

	// Header
	BITMAPINFOHEADER InfoHeader{};
	InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	InfoHeader.biWidth = Width;
	InfoHeader.biHeight = Height;
	InfoHeader.biPlanes = 1;
	InfoHeader.biBitCount = Depth;
	InfoHeader.biCompression = BI_RGB;
	InfoHeader.biSizeImage = biSizeImage;
	InfoHeader.biXPelsPerMeter = 0;
	InfoHeader.biYPelsPerMeter = 0;
	InfoHeader.biClrUsed = static_cast<DWORD>(Palette.size());
	InfoHeader.biClrImportant = 0;

	// Info
	PBITMAPINFO Info = (PBITMAPINFO)new char[sizeof(BITMAPINFOHEADER) + Palette.size() * sizeof(RGBQUAD)];
	Info->bmiHeader = InfoHeader;
	for (std::size_t i = 0; i < Palette.size(); i++)
	{
		Info->bmiColors[i] = Palette.data()[i];
	}

	// Complete
	return Info;
}


/*
	Save as Bitmap
*/
bool Standard_Image::SaveAsBitmap(std::filesystem::path Path)
{
	Standard_String Str;

	StdFile m_Input { Path, FileAccessMode::Write_Ex, true, true };
	if (!m_Input)
	{
		Str.Message("Standard Image: Error, could not create %s", Path.filename().c_str());
		return false;
	}

	// Info Header
	PBITMAPINFO Info = GetBitmapInfo();

	// File Header
	BITMAPFILEHEADER FileHeader{};
	FileHeader.bfType = 0x4D42;
	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + static_cast<DWORD>(Palette.size());
	FileHeader.bfSize = FileHeader.bfOffBits + Info->bmiHeader.biSizeImage;
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;
	
	// Write Data
	m_Input.Write(0, &FileHeader, sizeof(BITMAPFILEHEADER));
	m_Input.Write(sizeof(BITMAPFILEHEADER), &Info->bmiHeader, sizeof(BITMAPINFOHEADER));
	m_Input.Write(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), Palette.data(), Palette.size());
	m_Input.Write(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + Palette.size(), Pixels.data(), Pixels.size());

	// Complete
	return true;
}


#ifdef _WINDOWS
/*
	Bit blit
*/
void Standard_Image::BitBlit(HWND hWnd, HDC hdcDst, int X, int Y, int DstWidth, int DstHeight, int SrcX, int SrcY, DWORD dwRop) const
{
	PBITMAPINFO Info = GetBitmapInfo();

	HDC hDC = NULL;
	hdcDst ? hDC = hdcDst : hDC = GetDC(hWnd);

	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, Width, Height);
	SetDIBits(hMemDC, hBitmap, 0, Height, Pixels.data(), Info, DIB_RGB_COLORS);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	BitBlt(hDC, X, Y, DstWidth, DstHeight, hMemDC, SrcX, SrcY, dwRop);

	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	if (!hdcDst) ReleaseDC(hWnd, hDC);

	delete[] reinterpret_cast<char*>(Info);
}
#endif