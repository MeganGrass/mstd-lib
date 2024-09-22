


#include "std_crc32.h"


std::uint32_t Crc32Table[256]{};


/*
	Get the CRC32 checksum of a data source
*/
std::uint32_t Cyclic_Redundancy_Check::GetCRC32(void* _Data, std::uintmax_t _Size) const
{
	std::uint32_t CRC32 = 0xFFFFFFFF;
	for (std::uint32_t i = 0; i < _Size; i++)
	{
		CRC32 = Crc32Table[(CRC32 ^ ((std::uint8_t*)_Data)[i]) & 0xFF] ^ (CRC32 >> 8);
	}
	return CRC32 ^= 0xFFFFFFFF;
}