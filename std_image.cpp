/*
*
*	Megan Grass
*	March 07, 2024
*
*/


#ifdef LIB_JPEG
#include <stdio.h>
#include <cstdio>
#include <jpeglib.h>
#include <setjmp.h>
#pragma comment(lib, "jpeg-static.lib")
#pragma comment(lib, "turbojpeg-static.lib")
#endif

#ifdef LIB_PNG
#include <stdio.h>
#include <cstdio>
#include <png.h>
#endif


#include "std_image.h"


void Standard_Image::Close(void)
{
	b_Open = false;
	m_Depth = 0;
	m_Width = 0;
	m_Height = 0;
	m_Palette.clear();
	m_Pixels.clear();
}

void Standard_Image::SetPalette(std::size_t iColor, DWORD Color)
{
	if (iColor < m_Palette.size())
	{
		m_Palette[iColor].B = (Color & 0xFF);
		m_Palette[iColor].G = ((Color >> 8) & 0xFF);
		m_Palette[iColor].R = ((Color >> 16) & 0xFF);
		m_Palette[iColor].A = ((Color >> 24) & 0xFF);
	}
}

void Standard_Image::SetPalette(std::size_t iColor, Pixel_32bpp Color)
{
	if (iColor < m_Palette.size())
	{
		m_Palette[iColor] = Color;
	}
}

DWORD Standard_Image::GetPixel(uint32_t X, uint32_t Y)
{
	uint32_t Offset = (m_Height - Y - 1) * (m_Width * (m_Depth / 8));

	uint32_t Pixel = (X * m_Depth / 8) + Offset;

	switch (m_Depth)
	{
	case 4:
		Pixel = (X / 2) + ((m_Height - Y - 1) * (m_Width / 2));
		if (X & 1)
		{
			return m_Pixels.data()[Pixel] & 0x0F;
		}
		else
		{
			return m_Pixels.data()[Pixel] >> 4;
		}
	case 8:
		return m_Pixels.data()[Pixel];
	case 16:
	{
		return *reinterpret_cast<uint16_t*>(&m_Pixels.data()[Pixel]);
	}
	case 24:
	{
		return *reinterpret_cast<uint32_t*>(&m_Pixels.data()[Pixel]) | (0xFF << 24);
	}
	case 32:
	{
		return *reinterpret_cast<uint32_t*>(&m_Pixels.data()[Pixel]);
	}
	default:
		return 0;
	}
}

void Standard_Image::SetPixel(uint32_t X, uint32_t Y, DWORD Color)
{
	uint32_t Offset = (m_Height - Y - 1) * (m_Width * (m_Depth / 8));

	uint32_t Pixel = (X * m_Depth / 8) + Offset;

	switch (m_Depth)
	{
	case 4:
		Pixel = (X / 2) + ((m_Height - Y - 1) * (m_Width / 2));
		if (X & 1)
		{
			m_Pixels.data()[Pixel] = (m_Pixels.data()[Pixel] & 0xF0) | (Color & 0x0F);
		}
		else
		{
			m_Pixels.data()[Pixel] = (m_Pixels.data()[Pixel] & 0x0F) | (Color & 0x0F) << 4;
		}
		break;
	case 8:
		m_Pixels.data()[Pixel] = (Color & 0xFF);
		break;
	case 16:
		*reinterpret_cast<Pixel_16bpp*>(&m_Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_16bpp*>(&Color);
		break;
	case 24:
		*reinterpret_cast<Pixel_24bpp*>(&m_Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_24bpp*>(&Color);
		break;
	case 32:
		*reinterpret_cast<Pixel_32bpp*>(&m_Pixels.data()[Pixel]) = *reinterpret_cast<Pixel_32bpp*>(&Color);
		break;
	}
}

bool Standard_Image::DecompressRLE(WORD Depth, LONG Width, LONG Height, const std::vector<uint8_t>& Input, std::vector<uint8_t>& Output)
{
	if (Depth != 4 && Depth != 8)
	{
		return false;
	}

	LONG x = 0;
	LONG y = 0;
	std::size_t pInput = 0;

	std::vector<uint8_t> Pixels(Depth == 4 ? (Width * Height) / 2 : Width * Height);

	while (pInput < Input.size() && y < Height)
	{
		uint8_t D0 = Input[pInput++];
		uint8_t D1 = Input[pInput++];

		if (D0 == 0)
		{
			if (D1 == 0)
			{
				x = 0;
				y++;
			}
			else if (D1 == 1)
			{
				break;
			}
			else if (D1 == 2)
			{
				x += Input[pInput++];
				y += Input[pInput++];
			}
			else
			{
				for (std::uint8_t i = 0; i < D1; i++, x++)
				{
					if (Depth == 4)
					{
						if (i % 2)
						{
							Pixels[y * (Width / 2) + (x / 2)] |= (Input[pInput] & 0x0F);
							pInput++;
						}
						else
						{
							Pixels[y * (Width / 2) + (x / 2)] = (Input[pInput] & 0xF0) >> 4;
						}
					}
					else
					{
						Pixels[y * Width + x] = Input[pInput++];
					}
				}
				if (D1 & 1)
				{
					pInput++;
				}
			}
		}
		else
		{
			for (std::uint8_t i = 0; i < D0; i++, x++)
			{
				if (Depth == 4)
				{
					if (i % 2)
					{
						Pixels[y * (Width / 2) + (x / 2)] |= (D1 & 0x0F);
					}
					else
					{
						Pixels[y * (Width / 2) + (x / 2)] = (D1 & 0xF0) >> 4;
					}
				}
				else
				{
					Pixels[y * Width + x] = D1;
				}
			}
		}
	}

	Output = Pixels;

	return true;
}

bool Standard_Image::DecompressBitfields(WORD Depth, LONG Width, LONG Height, const std::vector<uint8_t>& Input, std::vector<uint8_t>& Output, uint32_t Red, uint32_t Green, uint32_t Blue, uint32_t Alpha)
{
	std::vector<uint8_t> Pixels(Width * Height * 4);

	uint32_t RedShift = 0, GreenShift = 0, BlueShift = 0, AlphaShift = 0;
	while (((Red >> RedShift) & 1) == 0) { RedShift++; }
	while (((Green >> GreenShift) & 1) == 0) { GreenShift++; }
	while (((Blue >> BlueShift) & 1) == 0) { BlueShift++; }
	while (((Alpha >> AlphaShift) & 1) == 0) { AlphaShift++; }

	std::size_t pInput = 0;
	std::size_t pOutput = 0;

	for (LONG y = 0; y < Height; y++)
	{
		for (LONG x = 0; x < Width; x++, pInput += 4)
		{
			uint32_t Pixel = *reinterpret_cast<const uint32_t*>(&Input[pInput]);

			Pixels[pOutput++] = (Pixel & Blue) >> BlueShift;
			Pixels[pOutput++] = (Pixel & Green) >> GreenShift;
			Pixels[pOutput++] = (Pixel & Red) >> RedShift;
			Pixels[pOutput++] = (Pixel & Alpha) >> AlphaShift;
		}
	}

	Output = Pixels;

	return true;
}

#ifdef LIB_JPEG
struct JPEG_Error_Manager
{
	struct jpeg_error_mgr pub;
	jmp_buf setjmp_buffer;
};

static void JPEG_Error_Exit(j_common_ptr cinfo)
{
	JPEG_Error_Manager* Error = (JPEG_Error_Manager*)cinfo->err;
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo, buffer);
	throw std::runtime_error(buffer);
}

static void JPEG_Output_Message(j_common_ptr cinfo)
{
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo, buffer);
	throw std::runtime_error(buffer);
}

bool Standard_Image::DecompressJPEG(const std::vector<uint8_t>& Input, std::vector<uint8_t>& OutPixels, WORD& OutDepth, LONG& OutWidth, LONG& OutHeight) try
{
	struct jpeg_decompress_struct cInfo {};
	struct JPEG_Error_Manager Error {};

	cInfo.err = jpeg_std_error(&Error.pub);

	Error.pub.error_exit = JPEG_Error_Exit;
	Error.pub.output_message = JPEG_Output_Message;

	if (setjmp(Error.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cInfo);
		return false;
	}

	jpeg_create_decompress(&cInfo);
	jpeg_mem_src(&cInfo, Input.data(), (unsigned long)Input.size());

	if (jpeg_read_header(&cInfo, TRUE) != JPEG_HEADER_OK)
	{
		jpeg_destroy_decompress(&cInfo);
		return false;
	}

	if (!jpeg_start_decompress(&cInfo))
	{
		jpeg_destroy_decompress(&cInfo);
		return false;
	}

	std::size_t RowStride = (size_t)(cInfo.output_width * cInfo.output_components);

	std::vector<uint8_t> Pixels(cInfo.output_width * cInfo.output_height * cInfo.output_components);

	while (cInfo.output_scanline < cInfo.output_height)
	{
		uint8_t* Row = &Pixels[(size_t)(cInfo.output_scanline * RowStride)];
		jpeg_read_scanlines(&cInfo, &Row, 1);
	}

	if (!jpeg_finish_decompress(&cInfo))
	{
		jpeg_destroy_decompress(&cInfo);
		return false;
	}

	jpeg_destroy_decompress(&cInfo);

	OutDepth = (WORD)cInfo.output_components * 8;

	OutWidth = (LONG)cInfo.output_width;
	OutHeight = (LONG)cInfo.output_height;

	OutPixels = Pixels;

	return true;
}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot read JPEG file from memory\r\n\r\nJPEG Message: %hs", e.what());
	return false;
}

bool Standard_Image::OpenQuasiJPEG(StdFile& File, std::uintmax_t pSource)
{
	std::vector<uint8_t> JPEGData;

	if (!File.IsOpen())
	{
		if (!File.Open(File.GetPath(), FileAccessMode::Read, true, false))
		{
			Str.Message(L"Standard Image Error: could not open at 0x%llX in \"%ws\"", pSource, File.GetPath().filename().wstring().c_str());
			return false;
		}
	}

	uintmax_t FileSize = File.Size();
	uintmax_t pData = pSource;
	uint16_t Marker = 0;

	std::pair <uintmax_t, uintmax_t> SOS = std::make_pair(0, 0);
	uintmax_t EOI = NULL;

	// Search for Start-Of-Image (SOI) marker (0xFF 0xDA)
	for (uintmax_t i = pSource; i < FileSize - 1; i++, pData++)
	{
		File.Read(pData, &Marker, sizeof(uint16_t));

		if (std::endian::native == std::endian::little)
		{
			Marker = std::byteswap<uint16_t>(Marker);
		}

		if (Marker == 0xFFDA)
		{
			uint16_t ChunkSize{};
			File.Read(pData + sizeof(uint16_t), &ChunkSize, sizeof(uint16_t));

			if (std::endian::native == std::endian::little)
			{
				ChunkSize = std::byteswap<uint16_t>(ChunkSize);
			}

			SOS.first = pData;
			SOS.second = pData + sizeof(uint16_t) + ChunkSize;

			pData = SOS.second;

			break;
		}
	}

	if (!SOS.first)
	{
		std::cout << "Standard Image: Error, could not find Start-Of-Image (SOI) marker (0xFF 0xDA)" << std::endl;
		return false;
	}

	// Search for End-Of-Image (EOI) marker (0xFF 0xD9)
	for (uintmax_t i = pData; i < FileSize - 1; i++, pData++)
	{
		File.Read(pData, &Marker, sizeof(uint16_t));

		if (std::endian::native == std::endian::little)
		{
			Marker = std::byteswap<uint16_t>(Marker);
		}

		if (Marker == 0xFFD9)
		{
			EOI = pData;
			break;
		}
	}

	if (!EOI)
	{
		std::cout << "Standard Image: Error, could not find End-Of-Image (EOI) marker (0xFF 0xD9)" << std::endl;
		return false;
	}

	// Convert each 0xFF between SOS and EOI to 0xFF 0x00
	size_t Size = (size_t)(EOI - SOS.second);
	std::vector<uint8_t> ScanData(Size);

	File.Read(pSource + SOS.second, ScanData.data(), ScanData.size());

	for (size_t i = 0; i < ScanData.size(); i++)
	{
		if (ScanData[i] == 0xFF)
		{
			ScanData.insert(ScanData.begin() + i + 1, 0x00);
		}
	}

	// Read jpeg header
	Size = (size_t)SOS.second;
	std::vector<uint8_t> Header(Size);
	File.Read(pSource, Header.data(), Header.size());

	File.Close();

	// Create jpeg file buffer with updated scan data
	Marker = 0xFFD9;
	if (std::endian::native == std::endian::little)
	{
		Marker = std::byteswap<uint16_t>(Marker);
	}

	std::size_t OutputSize = Header.size() + ScanData.size() + sizeof(uint16_t) * 2;
	if (OutputSize % sizeof(std::size_t))
	{
		OutputSize += sizeof(std::size_t) - (OutputSize % sizeof(std::size_t));
	}

	JPEGData.resize(OutputSize);
	std::memcpy(JPEGData.data(), Header.data(), Header.size());
	std::memcpy(JPEGData.data() + Header.size(), ScanData.data(), ScanData.size());
	std::memcpy(JPEGData.data() + Header.size() + ScanData.size(), &Marker, sizeof(uint16_t));

	WORD Depth{};
	LONG Width{}, Height{};

	if (!DecompressJPEG(JPEGData, JPEGData, Depth, Width, Height))
	{
		return false;
	}

	Close();

	m_Depth = Depth;

	m_Width = Width;
	m_Height = Height;

	m_Pixels.resize(JPEGData.size());

	uint8_t Alpha{};

	for (LONG Y = 0; Y < m_Height; Y++)
	{
		for (LONG X = 0; X < m_Width; X++)
		{
			uint8_t* Pixel = &JPEGData[(size_t)(Y * m_Width + X) * (m_Depth / 8)];
			if (m_Depth == 32)
			{
				Alpha = Pixel[3];
			}
			else
			{
				Alpha = 0xFF;
			}
			SetPixel(X, Y, Pixel[2] | (Pixel[1] << 8) | (Pixel[0] << 16) | (Alpha << 24));
		}
	}

	return b_Open = true;
}

bool Standard_Image::OpenQuasiJPEG(std::filesystem::path Path, std::uintmax_t pSource)
{
	StdFile m_File;
	m_File.SetPath(Path);
	return OpenQuasiJPEG(m_File, pSource);
}

bool Standard_Image::OpenJPEG(std::filesystem::path Path, std::uintmax_t pSource) try
{
	FILE* File = nullptr;

#ifdef _WINDOWS
	if (_wfopen_s(&File, Path.wstring().c_str(), L"rb"))
	{
		Str.Message(L"Standard Image Error: could not open \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#else
	File = fopen(Path.string().c_str(), "rb");
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not open \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#endif

	if (File && fseek(File, (LONG)pSource, SEEK_SET))
	{
		Str.Message(L"Standard Image Error: could not seek to 0x%llX in \"%ws\"", pSource, Path.filename().wstring().c_str());
		if (File) { fclose(File); }
		return false;
	}

	struct jpeg_decompress_struct cInfo {};
	struct JPEG_Error_Manager Error {};

	cInfo.err = jpeg_std_error(&Error.pub);

	Error.pub.error_exit = JPEG_Error_Exit;
	Error.pub.output_message = JPEG_Output_Message;

	if (setjmp(Error.setjmp_buffer))
	{
		jpeg_destroy_decompress(&cInfo);
		if (File) { fclose(File); }
		return false;
	}

	jpeg_create_decompress(&cInfo);

	jpeg_stdio_src(&cInfo, File);

	if (jpeg_read_header(&cInfo, TRUE) != JPEG_HEADER_OK)
	{
		jpeg_destroy_decompress(&cInfo);
		if (File) { fclose(File); }
		return false;
	}

	if (!jpeg_start_decompress(&cInfo))
	{
		jpeg_destroy_decompress(&cInfo);
		if (File) { fclose(File); }
		return false;
	}

	std::size_t RowStride = (size_t)(cInfo.output_width * cInfo.output_components);

	std::vector<uint8_t> Pixels(cInfo.output_width * cInfo.output_height * cInfo.output_components);

	while (cInfo.output_scanline < cInfo.output_height)
	{
		uint8_t* Row = &Pixels[(size_t)(cInfo.output_scanline * RowStride)];

		jpeg_read_scanlines(&cInfo, &Row, 1);
	}

	if (!jpeg_finish_decompress(&cInfo))
	{
		jpeg_destroy_decompress(&cInfo);
		if (File) { fclose(File); }
		return false;
	}

	jpeg_destroy_decompress(&cInfo);

	if (File)
	{
		fclose(File);
	}

	Close();

	m_Depth = (WORD)cInfo.output_components * 8;

	m_Width = (LONG)cInfo.output_width;
	m_Height = (LONG)cInfo.output_height;

	m_Pixels.resize(Pixels.size());

	uint8_t Alpha{};

	for (LONG Y = 0; Y < m_Height; Y++)
	{
		for (LONG X = 0; X < m_Width; X++)
		{
			uint8_t* Pixel = &Pixels[(size_t)(Y * m_Width + X) * cInfo.output_components];
			if (m_Depth == 32)
			{
				Alpha = Pixel[3];
			}
			else
			{
				Alpha = 0xFF;
			}
			SetPixel(X, Y, Pixel[2] | (Pixel[1] << 8) | (Pixel[0] << 16) | (Alpha << 24));
		}
	}

	return b_Open = true;
}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot read JPEG file at 0x%llx in \"%ws\"\r\n\r\nJPEG Message: %hs", pSource, Path.filename().wstring().c_str(), e.what());
	return false;
}

bool Standard_Image::SaveJPG(std::filesystem::path Path, std::uintmax_t pSource, bool b_Truncate) try
{
	if (!b_Open)
	{
		Str.Message(L"Standard Image Error: image is not open");
		return false;
	}

	if (!IsValid())
	{
		Str.Message(L"Standard Image Error: pixel data is empty, cannot create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	FILE* File = nullptr;

#ifdef _WINDOWS
	if (_wfopen_s(&File, Path.wstring().c_str(), b_Truncate ? L"wb" : L"rb+"))
	{
		Str.Message(L"Standard Image Error: could not save \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#else
	File = fopen(Path.string().c_str(), b_Truncate ? "wb" : "rb+");
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not save \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#endif

	if (File && fseek(File, (LONG)pSource, SEEK_SET))
	{
		Str.Message(L"Standard Image Error: could not seek to 0x%llX in \"%ws\"", pSource, Path.filename().wstring().c_str());
		if (File) { fclose(File); }
		return false;
	}

	struct jpeg_compress_struct cInfo {};
	struct JPEG_Error_Manager Error {};

	cInfo.err = jpeg_std_error(&Error.pub);

	Error.pub.error_exit = JPEG_Error_Exit;
	Error.pub.output_message = JPEG_Output_Message;

	if (setjmp(Error.setjmp_buffer))
	{
		jpeg_destroy_compress(&cInfo);
		if (File) { fclose(File); }
		return false;
	}

	jpeg_create_compress(&cInfo);

	jpeg_stdio_dest(&cInfo, File);

	cInfo.image_width = m_Width;
	cInfo.image_height = m_Height;
	cInfo.input_components = 4;
	cInfo.in_color_space = JCS_EXT_RGBA;

	jpeg_set_defaults(&cInfo);
	jpeg_set_quality(&cInfo, 100, TRUE);

	jpeg_start_compress(&cInfo, TRUE);

	std::size_t RowStride = (size_t)(m_Width * cInfo.input_components);
	std::vector<uint8_t> RowBuffer(RowStride);

	while (cInfo.next_scanline < cInfo.image_height)
	{
		for (std::size_t i = 0; i < RowStride; i += cInfo.input_components)
		{
			uint32_t Pixel = GetPixel((uint32_t)(i / cInfo.input_components), cInfo.next_scanline);

			if (m_Depth == 4 || m_Depth == 8)
			{
				Pixel_32bpp Color = m_Palette[Pixel];
				RowBuffer[i] = Color.R;
				RowBuffer[i + 1] = Color.G;
				RowBuffer[i + 2] = Color.B;
				RowBuffer[i + 3] = Color.A;
			}
			else if (m_Depth == 16)
			{
				Pixel_16bpp Pixel16 = *reinterpret_cast<Pixel_16bpp*>(&Pixel);
				RowBuffer[i] = ((Pixel16.R << 3) | (Pixel16.R >> 2));
				RowBuffer[i + 1] = ((Pixel16.G << 3) | (Pixel16.G >> 2));
				RowBuffer[i + 2] = ((Pixel16.B << 3) | (Pixel16.B >> 2));
				RowBuffer[i + 3] = Pixel16.A ? 0x00 : 0xFF;
			}
			else
			{
				RowBuffer[i] = ((Pixel & 0xFF0000) >> 16);
				RowBuffer[i + 1] = ((Pixel & 0x00FF00) >> 8);
				RowBuffer[i + 2] = (Pixel & 0x0000FF);
				RowBuffer[i + 3] = ((Pixel & 0xFF000000) >> 24);
			}
		}
		JSAMPROW RowPointer = RowBuffer.data();
		jpeg_write_scanlines(&cInfo, &RowPointer, 1);
	}

	jpeg_finish_compress(&cInfo);
	jpeg_destroy_compress(&cInfo);

	if (File)
	{
		fclose(File);
	}

	return true;

}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot save JPEG file \"%ws\"\r\n\r\nJPEG Message: %hs", Path.filename().wstring().c_str(), e.what());
	return false;
}
#endif

#ifdef LIB_PNG
static void PNG_Error_Handler(png_structp png_ptr, png_const_charp error_msg)
{
	throw std::runtime_error(error_msg);
}

static void PNG_Warning_Handler(png_structp png_ptr, png_const_charp warning_msg)
{
	throw std::runtime_error(warning_msg);
}

bool Standard_Image::DecompressPNG(const std::vector<uint8_t>&Input, std::vector<uint8_t>&OutPixels, std::vector<Pixel_32bpp> OutPalette) try
{
	OutPalette.clear();

	png_image Image{};
	Image.version = PNG_IMAGE_VERSION;

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, PNG_Error_Handler, PNG_Warning_Handler);
	if (!png_ptr)
	{
		png_image_free(&Image);
		return false;
	}

	if (!png_image_begin_read_from_memory(&Image, Input.data(), Input.size()))
	{
		return false;
	}

	if (Image.format & PNG_FORMAT_FLAG_COLORMAP)
	{
		std::vector<uint8_t> Palette(PNG_IMAGE_COLORMAP_SIZE(Image));

		if (!png_image_finish_read(&Image, nullptr, nullptr, 0, Palette.data()))
		{
			png_image_free(&Image);
			return false;
		}

		OutPalette.resize(Image.colormap_entries);

		for (std::size_t i = 0; i < OutPalette.size(); i++)
		{
			OutPalette[i].B = Palette[i * 3 + 0];
			OutPalette[i].G = Palette[i * 3 + 1];
			OutPalette[i].R = Palette[i * 3 + 2];
			OutPalette[i].A = 0;
		}
	}

	std::vector<uint8_t> Pixels(PNG_IMAGE_SIZE(Image));

	if (!png_image_finish_read(&Image, nullptr, Pixels.data(), 0, nullptr))
	{
		png_image_free(&Image);
		return false;
	}

	png_image_free(&Image);

	OutPixels = Pixels;

	return true;
}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot read PNG file from memory\r\n\r\nPNG Message: %hs", e.what());
	return false;
}

bool Standard_Image::OpenPNG(std::filesystem::path Path, std::uintmax_t pSource) try 
{
	FILE* File = nullptr;

#ifdef _WINDOWS
	if (_wfopen_s(&File, Path.wstring().c_str(), L"rb"))
	{
		Str.Message(L"Standard Image Error: could not open \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#else
	File = fopen(Path.string().c_str(), "rb");
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not open \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#endif

	if (File && fseek(File, (LONG)pSource, SEEK_SET))
	{
		Str.Message(L"Standard Image Error: could not seek to 0x%llX in \"%ws\"", pSource, Path.filename().wstring().c_str());
		if (File) { fclose(File); }
		return false;
	}

	png_structp PNG = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, PNG_Error_Handler, PNG_Warning_Handler);
	if (PNG == nullptr)
	{
		Str.Message(L"Standard Image Error: could not create PNG read struct");
		if (File) { fclose(File); }
		return false;
	}

	png_infop Header = png_create_info_struct(PNG);
	if (Header == nullptr)
	{
		Str.Message(L"Standard Image Error: could not create PNG info struct");
		png_destroy_read_struct(&PNG, nullptr, nullptr);
		if (File) { fclose(File); }
		return false;
	}

	png_infop Footer = png_create_info_struct(PNG);
	if (Footer == nullptr)
	{
		Str.Message(L"Standard Image Error: could not create PNG info struct");
		png_destroy_read_struct(&PNG, &Header, nullptr);
		return false;
	}

	png_init_io(PNG, File);

	png_set_keep_unknown_chunks(PNG, PNG_HANDLE_CHUNK_ALWAYS, nullptr, 0);

	png_read_info(PNG, Header);

	std::size_t nRowBytes = png_get_rowbytes(PNG, Header);
	std::size_t ImageHeight = png_get_image_height(PNG, Header);

	std::unique_ptr<png_byte[]> Pixels = std::make_unique<png_byte[]>(ImageHeight * nRowBytes);
	std::unique_ptr<png_bytep[]> Image = std::make_unique<png_bytep[]>(ImageHeight);

	for (std::size_t i = 0; i < ImageHeight; ++i)
	{
		Image[i] = &Pixels[i * nRowBytes];
	}

	png_read_image(PNG, Image.get());

	png_read_end(PNG, Footer);

	png_uint_32 Width{}, Height{};
	int BitDepth{}, ColorType{}, InterlaceType{}, CompressionMethod{}, FilterMethod{};
	if (!png_get_IHDR(PNG, Header, &Width, &Height, &BitDepth, &ColorType, &InterlaceType, &CompressionMethod, &FilterMethod))
	{
		Str.Message(L"Standard Image Error: could not get PNG header information");
		png_destroy_read_struct(&PNG, &Header, &Footer);
		if (File) { fclose(File); }
		return false;
	}

	if (BitDepth != 4 && BitDepth != 8)
	{
		Str.Message(L"Standard Image Error: unsupported PNG bit depth: %d", BitDepth);
		png_destroy_read_struct(&PNG, &Header, &Footer);
		if (File) { fclose(File); }
		return false;
	}

	if (ColorType != PNG_COLOR_TYPE_RGB && ColorType != PNG_COLOR_TYPE_RGB_ALPHA && ColorType != PNG_COLOR_TYPE_PALETTE)
	{
		Str.Message(L"Standard Image Error: unsupported PNG color type: %d", ColorType);
		png_destroy_read_struct(&PNG, &Header, &Footer);
		if (File) { fclose(File); }
		return false;
	}

	Close();

	switch (ColorType)
	{
	case PNG_COLOR_TYPE_RGB: m_Depth = BitDepth * 3; break;
	case PNG_COLOR_TYPE_RGB_ALPHA: m_Depth = BitDepth * 4; break;
	case PNG_COLOR_TYPE_PALETTE: m_Depth = (BitDepth == 1 || BitDepth == 2 || BitDepth == 4) ? BitDepth : 8; break;
	}

	if (ColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_colorp Palette{};
		int nColors{};

		if (!png_get_PLTE(PNG, Header, &Palette, &nColors))
		{
			Str.Message(L"Standard Image Error: could not get PNG palette");
			png_destroy_read_struct(&PNG, &Header, &Footer);
			if (File) { fclose(File); }
			return false;
		}

		m_Palette.resize(nColors * sizeof(Pixel_32bpp));

		for (int i = 0; i < nColors; i++)
		{
			m_Palette[i].B = Palette[i].blue;
			m_Palette[i].G = Palette[i].green;
			m_Palette[i].R = Palette[i].red;
			m_Palette[i].A = 0xFF;
		}
	}

	m_Width = (LONG)Width;
	m_Height = (LONG)Height;

	m_Pixels.resize((size_t)(m_Depth == 4 ? (m_Width * m_Height) / 2 : m_Width * m_Height * GetPixelSize()));

	if (ColorType == PNG_COLOR_TYPE_RGB)
	{
		for (png_uint_32 Y = 0; Y < Height; Y++)
		{
			for (png_uint_32 X = 0; X < Width; X++)
			{
				png_byte* Pixel = &Image[Y][X * 3];
				SetPixel(X, Y, Pixel[2] | (Pixel[1] << 8) | (Pixel[0] << 16) | (0xFF << 24));
			}
		}
	}
	else if (ColorType == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		for (png_uint_32 Y = 0; Y < Height; Y++)
		{
			for (png_uint_32 X = 0; X < Width; X++)
			{
				png_byte* Pixel = &Image[Y][X * 4];
				SetPixel(X, Y, Pixel[2] | (Pixel[1] << 8) | (Pixel[0] << 16) | (Pixel[3] << 24));
			}
		}
	}
	else if (ColorType == PNG_COLOR_TYPE_PALETTE)
	{
		for (png_uint_32 Y = 0; Y < Height; Y++)
		{
			for (png_uint_32 X = 0; X < Width; X++)
			{
				png_byte Pixel = Image[Y][X];
				SetPixel(X, Y, (uint8_t)Pixel);
			}
		}
	}

	png_destroy_read_struct(&PNG, &Header, &Footer);

	if (File)
	{
		fclose(File);
	}

	return b_Open = true;
}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot read PNG file at 0x%llx in \"%ws\"\r\n\r\nPNG Message: %hs", pSource, Path.filename().wstring().c_str(), e.what());
	return false;
}

bool Standard_Image::SavePNG(std::filesystem::path Path, std::uintmax_t pSource, bool b_Truncate) try
{
	if (!b_Open)
	{
		Str.Message(L"Standard Image Error: image is not open");
		return false;
	}

	if (!IsValid())
	{
		Str.Message(L"Standard Image Error: pixel data is empty, cannot create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	FILE* File = nullptr;

#ifdef _WINDOWS
	if (_wfopen_s(&File, Path.wstring().c_str(), b_Truncate ? L"wb" : L"rb+"))
	{
		Str.Message(L"Standard Image Error: could not create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#else
	File = fopen(Path.string().c_str(), b_Truncate ? "wb" : "rb+");
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}
#endif

	if (File && fseek(File, (LONG)pSource, SEEK_SET))
	{
		Str.Message(L"Standard Image Error: could not seek to 0x%llX in \"%ws\"", pSource, Path.filename().wstring().c_str());
		if (File) { fclose(File); }
		return false;
	}

	png_structp PNG = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, PNG_Error_Handler, PNG_Warning_Handler);
	if (PNG == nullptr)
	{
		Str.Message(L"Standard Image Error: could not create PNG write struct");
		if (File) { fclose(File); }
		return false;
	}

	png_infop Header = png_create_info_struct(PNG);
	if (Header == nullptr)
	{
		Str.Message(L"Standard Image Error: could not create PNG info struct");
		png_destroy_write_struct(&PNG, nullptr);
		if (File) { fclose(File); }
		return false;
	}

	png_init_io(PNG, File);

	int BitDepth{}, ColorType{};

	BitDepth = ColorType == PNG_COLOR_TYPE_PALETTE ? m_Depth : 8;

	ColorType = m_Depth == 4 || m_Depth == 8 ? PNG_COLOR_TYPE_PALETTE : m_Depth == 16 || m_Depth == 24 ? PNG_COLOR_TYPE_RGB_ALPHA : PNG_COLOR_TYPE_RGB_ALPHA;

	png_set_IHDR(PNG, Header, m_Width, m_Height, BitDepth, ColorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	if (ColorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_colorp Palette = new png_color[m_Palette.size()];
		std::cout << sizeof(Palette) << std::endl;
		for (std::size_t i = 0; i < m_Palette.size(); i++)
		{
			Palette[i].red = m_Palette[i].R;
			Palette[i].green = m_Palette[i].G;
			Palette[i].blue = m_Palette[i].B;
		}
		png_set_PLTE(PNG, Header, Palette, (int)m_Palette.size() / sizeof(Pixel_32bpp));
		delete[] Palette;
	}

	png_write_info(PNG, Header);

	std::size_t nRowBytes = png_get_rowbytes(PNG, Header);
	std::size_t ImageHeight = png_get_image_height(PNG, Header);

	std::unique_ptr<png_byte[]> Pixels = std::make_unique<png_byte[]>(ImageHeight * nRowBytes);
	std::unique_ptr<png_bytep[]> Image = std::make_unique<png_bytep[]>(ImageHeight);

	for (std::size_t i = 0; i < ImageHeight; ++i)
	{
		Image[i] = &Pixels[i * nRowBytes];
	}

	if (ColorType == PNG_COLOR_TYPE_RGB)
	{
		if (m_Depth == 16)
		{
			for (LONG Y = 0; Y < m_Height; Y++)
			{
				for (LONG X = 0; X < m_Width; X++)
				{
					png_byte* Pixel = &Image[Y][X * 3];
					DWORD Color = GetPixel(X, Y);
					Pixel[0] = (png_byte)((Color & 0x7C00) >> 7);
					Pixel[1] = (png_byte)((Color & 0x03E0) >> 2);
					Pixel[2] = (png_byte)((Color & 0x001F) << 3);
				}
			}
		}
		else
		{
			for (LONG Y = 0; Y < m_Height; Y++)
			{
				for (LONG X = 0; X < m_Width; X++)
				{
					png_byte* Pixel = &Image[Y][X * 3];
					DWORD Color = GetPixel(X, Y);
					Pixel[0] = (png_byte)((Color & 0xFF0000) >> 16);
					Pixel[1] = (png_byte)((Color & 0x00FF00) >> 8);
					Pixel[2] = (png_byte)(Color & 0x0000FF);
				}
			}
		}
	}
	else if (ColorType == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		if (m_Depth == 16)
		{
			for (LONG Y = 0; Y < m_Height; Y++)
			{
				for (LONG X = 0; X < m_Width; X++)
				{
					png_byte* Pixel = &Image[Y][X * 4];
					DWORD Color = GetPixel(X, Y);
					Pixel[0] = (png_byte)((Color & 0x7C00) >> 7);
					Pixel[1] = (png_byte)((Color & 0x03E0) >> 2);
					Pixel[2] = (png_byte)((Color & 0x001F) << 3);
					Color & 0x8000 ? Pixel[3] = 0x00 : Pixel[3] = 0xFF;
				}
			}
		}
		else
		{
			for (LONG Y = 0; Y < m_Height; Y++)
			{
				for (LONG X = 0; X < m_Width; X++)
				{
					png_byte* Pixel = &Image[Y][X * 4];
					DWORD Color = GetPixel(X, Y);
					Pixel[0] = (png_byte)((Color & 0xFF0000) >> 16);
					Pixel[1] = (png_byte)((Color & 0x00FF00) >> 8);
					Pixel[2] = (png_byte)(Color & 0x0000FF);
					Pixel[3] = (png_byte)((Color & 0xFF000000) >> 24);
				}
			}
		}
	}
	else if (ColorType == PNG_COLOR_TYPE_PALETTE)
	{
		for (LONG Y = 0; Y < m_Height; Y++)
		{
			for (LONG X = 0; X < m_Width; X++)
			{
				png_byte Pixel = (png_byte)GetPixel(X, Y);
				Image[Y][X] = Pixel;
			}
		}
	}

	png_write_image(PNG, Image.get());

	png_write_end(PNG, Header);

	png_destroy_write_struct(&PNG, &Header);

	if (File)
	{
		fclose(File);
	}

	return true;
}
catch (const std::exception& e)
{
	Str.Message(L"Standard Image Error: cannot write PNG file to \"%ws\"\r\n\r\nPNG Message: %hs", Path.filename().wstring().c_str(), e.what());
	return false;
}
#endif

bool Standard_Image::Create(WORD Depth, LONG Width, LONG Height, DWORD CanvasColor)
{
	if (Depth != 4 && Depth != 8 && Depth != 16 && Depth != 24 && Depth != 32)
	{
		std::cout << "Standard Image: Error, unsupported depth: " << Depth << std::endl;
		return false;
	}

	Close();

	m_Depth = Depth;

	m_Width = Width;
	m_Height = Height;

	switch (m_Depth)
	{
	case 4:
		m_Palette.resize(16 * sizeof(Pixel_32bpp));
		break;
	case 8:
		m_Palette.resize(256 * sizeof(Pixel_32bpp));
		break;
	}

	uint32_t Size = m_Depth == 4 ? (m_Width * m_Height) / 2 : m_Width * m_Height * GetPixelSize();

	m_Pixels.resize(Size);

	if (CanvasColor)
	{
		for (LONG Y = 0; Y < m_Height; Y++)
		{
			for (LONG X = 0; X < m_Width; X++)
			{
				SetPixel(X, Y, CanvasColor);
			}
		}
	}

	return b_Open = true;
}

bool Standard_Image::SaveBMP(std::filesystem::path Path, std::uintmax_t pSource, bool b_Truncate)
{
	if (!b_Open)
	{
		Str.Message(L"Standard Image Error: image is not open");
		return false;
	}

	if (!IsValid())
	{
		Str.Message(L"Standard Image Error: pixel data is empty, cannot create \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	StdFile m_Input;

	if (b_Truncate)
	{
		m_Input.Open(Path, FileAccessMode::Write_Ex, true, true);
	}
	else
	{
		m_Input.Open(Path, FileAccessMode::Read_Ex, true, false);
	}

	if (!m_Input)
	{
		Str.Message(L"Standard Image Error: could not write to \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	Bitmap_Info Info{};
	Info.Size = sizeof(Bitmap_Info);
	Info.Width = m_Width;
	Info.Height = m_Height;
	Info.Planes = 1;
	Info.Depth = m_Depth;
	Info.Compression = Bitmap_Compression::RGB;
	Info.PixelSize = m_Depth == 4 ? (m_Width * m_Height) / 2 : m_Width * m_Height * GetPixelSize();
	Info.MeterWidth = 0;
	Info.MeterHeight = 0;
	Info.PaletteColors = (DWORD)m_Palette.size();
	Info.MaxColors = 0;

	Bitmap_Header Header{};
	Header.BM = 0x4D42;
	Header.PixelPtr = sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + (DWORD)m_Palette.size();
	Header.Size = sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + (DWORD)m_Palette.size() + Info.PixelSize;
	Header.reserved0 = 0;
	Header.reserved1 = 0;
	
	m_Input.Write(pSource, &Header, sizeof(Bitmap_Header));
	m_Input.Write(pSource + sizeof(Bitmap_Header), &Info, sizeof(Bitmap_Info));
	m_Input.Write(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info), m_Palette.data(), m_Palette.size());
	m_Input.Write(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + m_Palette.size(), m_Pixels.data(), m_Pixels.size());

	return true;
}

bool Standard_Image::OpenBMP(std::filesystem::path Path, std::uintmax_t pSource)
{
	StdFile File{ Path, FileAccessMode::Read, true, false };
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not open \"%ws\"", Path.filename().wstring().c_str());
		return false;
	}

	Bitmap_Header Header{};
	File.Read(pSource, &Header, sizeof(Bitmap_Header));

	if (Header.BM != 0x4D42)
	{
		Str.Message(L"Standard Image Error: invalid bitmap file header type (0x%04X)", Header.BM);
		return false;
	}

	if (!Header.PixelPtr || Header.PixelPtr > File.Size())
	{
		Str.Message(L"Standard Image Error: invalid bitmap file header offset (0x%08X)", Header.PixelPtr);
		return false;
	}

	if (!Header.Size || Header.Size > File.Size())
	{
		Str.Message(L"Standard Image Error: invalid bitmap file size (0x%08X)", Header.Size);
		return false;
	}

	if (Header.reserved0 || Header.reserved1)
	{
		Str.Message(L"Standard Image Error: invalid bitmap file header reserved values (0x%04X, 0x%04X)", Header.reserved0, Header.reserved1);
		return false;
	}

	Bitmap_Info Info{};
	File.Read(pSource + sizeof(Bitmap_Header), &Info, sizeof(Bitmap_Info));

	if (Info.Size != sizeof(Bitmap_Info))
	{
		Str.Message(L"Standard Image Error: invalid bitmap info header size (%d)", Info.Size);
		return false;
	}

	if (Info.Planes != 1)
	{
		Str.Message(L"Standard Image Error: invalid bitmap planes (%d)", Info.Planes);
		return false;
	}

	if (Info.Depth != 4 && Info.Depth != 8 && Info.Depth != 16 && Info.Depth != 24 && Info.Depth != 32)
	{
		Str.Message(L"Standard Image Error: unsupported bitmap bit count (%d)", Info.Depth);
		return false;
	}

	if ((Info.Compression != Bitmap_Compression::RGB) &&
		(Info.Compression != Bitmap_Compression::RLE8) &&
		(Info.Compression != Bitmap_Compression::RLE4) &&
		(Info.Compression != Bitmap_Compression::BITFIELDS)
#ifdef LIB_JPEG
		&& (Info.Compression != Bitmap_Compression::JPEG)
#endif
#ifdef LIB_PNG
		&& (Info.Compression != Bitmap_Compression::PNG)
#endif
		)
	{
		Str.Message(L"Standard Image Error: unsupported bitmap compression: %ws",
#ifndef LIB_JPEG
			Info.Compression == Bitmap_Compression::JPEG ? L"JPEG" :
#endif
#ifndef LIB_JPEG
			Info.Compression == Bitmap_Compression::PNG ? L"PNG" :
#endif
			Info.Compression == Bitmap_Compression::CMYK ? L"CMYK" :
			Info.Compression == Bitmap_Compression::CMYKRLE8 ? L"CMYKRLE8" :
			Info.Compression == Bitmap_Compression::CMYKRLE4 ? L"CMYKRLE4" :
			Str.FormatCStyle(L"0x%08X", std::to_underlying(Info.Compression)).c_str());
		return false;
	}

	if (Info.Depth == 4 || Info.Depth == 8)
	{
		DWORD nMaxColors = Info.Depth == 4 ? 16 * sizeof(Pixel_32bpp) : 256 * sizeof(Pixel_32bpp);

		if (!Info.PaletteColors || Info.PaletteColors > nMaxColors)
		{
			Str.Message(L"Standard Image Error: invalid bitmap palette color count (%d)", Info.PaletteColors);
			return false;
		}
	}

	Close();

	m_Depth = Info.Depth;

	m_Width = (uint16_t)Info.Width;
	m_Height = (uint16_t)Info.Height;

	m_Palette.resize(Info.PaletteColors);

	File.Read(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info), m_Palette.data(), m_Palette.size());

	uint32_t Size = m_Depth == 4 ? (m_Width * m_Height) / 2 : m_Width * m_Height * GetPixelSize();

	m_Pixels.resize(Size);

	File.Read(pSource + Header.PixelPtr, m_Pixels.data(), m_Pixels.size());

	if (Info.Compression == Bitmap_Compression::RLE8)
	{
		DecompressRLE(8, m_Width, m_Height, m_Pixels, m_Pixels);
	}
	else if (Info.Compression == Bitmap_Compression::RLE4)
	{
		DecompressRLE(4, m_Width, m_Height, m_Pixels, m_Pixels);
	}
	else if (Info.Compression == Bitmap_Compression::BITFIELDS)
	{
		uint32_t Red, Green, Blue, Alpha = 0xFF000000;
		File.Read(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + m_Palette.size(), &Red, sizeof(uint32_t));
		File.Read(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + m_Palette.size() + sizeof(uint32_t), &Green, sizeof(uint32_t));
		File.Read(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + m_Palette.size() + 2 * sizeof(uint32_t), &Blue, sizeof(uint32_t));
		if (Info.Depth == 32)
		{
			File.Read(pSource + sizeof(Bitmap_Header) + sizeof(Bitmap_Info) + m_Palette.size() + 3 * sizeof(uint32_t), &Alpha, sizeof(uint32_t));
		}
		DecompressBitfields(m_Depth, m_Width, m_Height, m_Pixels, m_Pixels, Red, Green, Blue, Alpha);
	}
#ifdef LIB_JPEG
	else if (Info.Compression == Bitmap_Compression::JPEG)
	{
		DecompressJPEG(m_Pixels, m_Pixels, m_Depth, m_Width, m_Height);
	}
#endif
#ifdef LIB_PNG
	else if (Info.Compression == Bitmap_Compression::PNG)
	{
		DecompressPNG(m_Pixels, m_Pixels, m_Palette);
	}
#endif

	return b_Open = true;
}

void Standard_Image::SavePAL(std::filesystem::path Path)
{
	if (m_Palette.empty())
	{
		Str.Message(L"Standard Image Error: palette is empty");
		return;
	}

	StdFile File{ Path, FileAccessMode::Write_Ex, true, true };
	if (!File)
	{
		Str.Message(L"Standard Image Error: could not create \"%ws\"", Path.filename().wstring().c_str());
		return;
	}

	Microsoft_RIFF_Palette Header{};

	std::memcpy(Header.RIFF, "RIFF", 4);
	Header.Size = (m_Depth == 4 ? 16 * 4 + 4 : 256 * 4 + 4) + 0x0A;
	std::memcpy(Header.PAL, "PAL ", 4);
	std::memcpy(Header.data, "data", 4);
	Header.DataSize = (uint16_t)m_Depth == 4 ? 16 * 4 + 4 : 256 * 4 + 4;
	Header.Version = 0x0300;
	Header.nColors = (uint16_t)m_Depth == 4 ? 16 : 256;

	for (std::size_t i = 0; i < m_Palette.size(); i++)
	{
		File.Write(0x16 + (i * sizeof(Pixel_32bpp)), &m_Palette[i], sizeof(Pixel_32bpp));
	}
}