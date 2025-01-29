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

DWORD Standard_Image::TransparentColor = RGB(0xFF, 0, 0xFF);

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
		Palette[iPalette].rgbBlue = (Color & 0xFF);
		Palette[iPalette].rgbGreen = ((Color >> 8) & 0xFF);
		Palette[iPalette].rgbRed = ((Color >> 16) & 0xFF);
		Palette[iPalette].rgbReserved = ((Color >> 24) & 0xFF);
	}
}


/*
	Get Pixel
*/
DWORD Standard_Image::GetPixel(uint32_t X, uint32_t Y)
{
	uint32_t Offset = (Height - Y - 1) * (Width * (Depth / 8));

	uint32_t Pixel = (X * Depth / 8) + Offset;

	switch (Depth)
	{
	case 4:
		Pixel = (X / 2) + ((Height - Y - 1) * (Width / 2));
		if (X & 1)
		{
			return Pixels.data()[Pixel] & 0x0F;
		}
		else
		{
			return Pixels.data()[Pixel] >> 4;
		}
	case 8:
		return Pixels.data()[Pixel];
	case 16:
	{
		struct Pixel_16bpp
		{
			std::uint16_t A : 1;
			std::uint16_t R : 5;
			std::uint16_t G : 5;
			std::uint16_t B : 5;
		};
		Pixel_16bpp Color = *reinterpret_cast<Pixel_16bpp*>(&Pixels.data()[Pixel]);
		return (Color.A << 15) | (Color.R << 10) | (Color.G << 5) | Color.B;
	}
	case 24:
	{
		struct Pixel_24bpp
		{
			std::uint8_t R : 8;
			std::uint8_t G : 8;
			std::uint8_t B : 8;
		};
		Pixel_24bpp Color = *reinterpret_cast<Pixel_24bpp*>(&Pixels.data()[Pixel]);
		return (0xFF << 24) | (Color.R << 16) | (Color.G << 8) | Color.B;
	}
	case 32:
	{
		struct Pixel_32bpp
		{
			std::uint8_t A : 8;
			std::uint8_t R : 8;
			std::uint8_t G : 8;
			std::uint8_t B : 8;
		};
		Pixel_32bpp Color = *reinterpret_cast<Pixel_32bpp*>(&Pixels.data()[Pixel]);
		return (Color.A << 24) | (Color.R << 16) | (Color.G << 8) | Color.B;
	}
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

	switch (Depth)
	{
	case 4:
		Pixel = (X / 2) + ((Height - Y - 1) * (Width / 2));
		if (X & 1)
		{
			Pixels.data()[Pixel] = (Pixels.data()[Pixel] & 0xF0) | (Color & 0x0F);
		}
		else
		{
			Pixels.data()[Pixel] = (Pixels.data()[Pixel] & 0x0F) | (Color & 0x0F) << 4;
		}
		break;
	case 8:
		Pixels.data()[Pixel] = (Color & 0xFF);
		break;
	case 16:
	{
		struct Pixel_16bpp
		{
			std::uint16_t A : 1;
			std::uint16_t R : 5;
			std::uint16_t G : 5;
			std::uint16_t B : 5;
		};
		*reinterpret_cast<Pixel_16bpp*>(&Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_16bpp*>(&Color);
	}
		break;
	case 24:
	{
		struct Pixel_24bpp
		{
			std::uint8_t R : 8;
			std::uint8_t G : 8;
			std::uint8_t B : 8;
		};
		*reinterpret_cast<Pixel_24bpp*>(&Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_24bpp*>(&Color);
	}
		break;
	case 32:
	{
		struct Pixel_32bpp
		{
			std::uint8_t A : 8;
			std::uint8_t R : 8;
			std::uint8_t G : 8;
			std::uint8_t B : 8;
		};
		*reinterpret_cast<Pixel_32bpp*>(&Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_32bpp*>(&Color);
	}
		break;
	}
}


/*
	Save as Bitmap
*/
bool Standard_Image::SaveAsBitmap(std::filesystem::path Path)
{
	Standard_String Str;

	if (Pixels.empty())
	{
		Str.Message(L"Standard Image: Error, pixel data is empty");
		return false;
	}

	if (!GetWidth() || !GetHeight())
	{
		Str.Message(L"Standard Image: Error, width or height is zero");
		return false;
	}

	StdFile m_Input { Path, FileAccessMode::Write_Ex, true, true };
	if (!m_Input)
	{
		Str.Message(L"Standard Image: Error, could not create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	// Info Header
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


/*
	Save Microsoft Palette (*.PAL)
*/
void Standard_Image::SaveMicrosoftPalette(std::filesystem::path Path)
{
	Standard_String Str;

	if (Palette.empty())
	{
		Str.Message(L"Standard Image: Error, palette is empty");
		return;
	}

	StdFile m_Input{ Path, FileAccessMode::Write_Ex, true, true };
	if (!m_Input)
	{
		Str.Message(L"Standard Image: Error, could not create \"%ws\"", Path.filename().wstring().c_str());
		return;
	}

	std::uint16_t DataSize = Depth == 4 ? 16 * 4 + 4 : 256 * 4 + 4;
	std::uint16_t Version = 0x0300;
	std::uint16_t nColors = Depth == 4 ? 16 : 256;
	std::uintmax_t pPalette = 0x16;
	std::uint32_t FileSize = 0x0A + DataSize;

	// RIFF Header
	m_Input.WriteStr(0x00, "RIFF\0");
	m_Input.Write(0x04, &FileSize, 4);
	m_Input.WriteStr(0x08, "PAL \0");
	m_Input.WriteStr(0x0C, "data\0");
	m_Input.Write(0x10, &DataSize, 2);
	m_Input.Write(0x12, &Version, 2);
	m_Input.Write(0x14, &nColors, 2);

	// Colors
	for (std::size_t i = 0; i < nColors; i++)
	{
		m_Input.Write(pPalette, &Palette[i], sizeof(RGBQUAD));

		pPalette += sizeof(RGBQUAD);
	}

}


#ifdef _WINDOWS
/*
	Bit blit
*/
void Standard_Image::BitBlit(HWND hWnd, HDC hdcDst, int X, int Y, int DstWidth, int DstHeight, int SrcX, int SrcY, DWORD dwRop) const
{
	// Info Header
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