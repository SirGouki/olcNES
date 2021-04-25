#pragma once
#include <cstdint>
#include <array>
#include <memory>
#include "CPU.h"
#include "PPU.h"
#include "Cartridge.h"

class Bus
{
public:
	Bus();
	~Bus();

public: //Devices connected to the bus
	CPU cpu; // cpu
	PPU ppu; // ppu
	std::shared_ptr<Cartridge> cart;


	//Fake RAM for testing
	std::array<uint8_t, 2 * 1024> cpuRam;
	

public:	// Bus I/O
	void cpuWrite(uint16_t addr, uint8_t data);
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

public: // System interface (buttons, cartridge slot)
	void insertCartridge(const std::shared_ptr<Cartridge> &Cartridge);
	void reset();
	void clock();

private:
	// Count how many clocks have passed
	uint32_t nSystemClockCounter = 0;
};