

#pragma once


#include <cstdint>

#include <cstring>


extern std::uint32_t Crc32Table[256];


class Cyclic_Redundancy_Check {
private:
public:


	/*
		Construction
	*/
	explicit Cyclic_Redundancy_Check(void) noexcept
	{
		for (std::uint32_t i = 0; i < 256; i++)
		{
			std::uint32_t CRC32 = i;
			for (std::uint32_t x = 0; x < 8; x++)
			{
				CRC32 = (CRC32 & 1) ? (0xEDB88320 ^ (CRC32 >> 1)) : (CRC32 >> 1);
			}
			Crc32Table[i] = CRC32;
		}
	}


	/*
		Deconstruction
	*/
	virtual ~Cyclic_Redundancy_Check(void)
	{
		std::memset(Crc32Table, 0, sizeof(std::uint32_t) * 256);
	}


	/*
		Get the CRC32 checksum of a data source
	*/
	[[nodiscard]] std::uint32_t GetCRC32(void* _Data, std::uintmax_t _Size) const;


};