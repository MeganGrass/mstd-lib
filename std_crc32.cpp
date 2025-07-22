


#include "std_crc32.h"


std::uint32_t Cyclic_Redundancy_Check::Table[256]{};

std::once_flag Cyclic_Redundancy_Check::bInitialized;


std::uint32_t Cyclic_Redundancy_Check::GetCRC32(const void* _Data, std::uintmax_t _Size) const noexcept
{
	const std::uint8_t* Data = reinterpret_cast<const std::uint8_t*>(_Data);
	std::uint32_t CRC32 = 0xFFFFFFFF;
	for (std::uint32_t i = 0; i < _Size; i++)
	{
		CRC32 = Table[(CRC32 ^ Data[i]) & 0xFF] ^ (CRC32 >> 8);
	}
	return CRC32 ^= 0xFFFFFFFF;
}