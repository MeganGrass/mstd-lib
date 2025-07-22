

#pragma once


#include <cstdint>

#include <cstring>

#include <mutex>


class Cyclic_Redundancy_Check {
private:

	static std::uint32_t Table[256];

	static std::once_flag bInitialized;

	static void InitializeTable(void) noexcept
	{
		std::call_once(bInitialized, []() {
			for (std::uint32_t i = 0; i < 256; i++)
			{
				std::uint32_t CRC32 = i;
				for (std::uint32_t x = 0; x < 8; x++)
				{
					CRC32 = (CRC32 & 1) ? (0xEDB88320 ^ (CRC32 >> 1)) : (CRC32 >> 1);
				}
				Table[i] = CRC32;
			}
			});
	}

public:


	/*
		Construction
	*/
	explicit Cyclic_Redundancy_Check(void) noexcept
	{
		InitializeTable();
	}


	/*
		Deconstruction
	*/
	~Cyclic_Redundancy_Check(void) = default;


	/*
		Get the CRC32 checksum of a data source
	*/
	[[nodiscard]] std::uint32_t GetCRC32(const void* _Data, std::uintmax_t _Size) const noexcept;


};