#pragma once
#include <cstdint>
#include <memory>
#include "Cartridge.h"

#include "olcPixelGameEngine.h"

class PPU
{
public:
	PPU();
	~PPU();

	//Communicate with the main bus
	uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
	void cpuWrite(uint16_t addr, uint8_t data);

	//Communicate with the PPU bus
	uint8_t ppuRead(uint16_t addr, bool bReadOnly = false);
	void ppuWrite(uint16_t addr, uint8_t data);

	/*enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI
	} mirror = HORIZONTAL;	*/

private:
	// Cartridge
	std::shared_ptr<Cartridge> cart;

public:
	// Memory
	uint8_t tblName[2][1024]; // VRAM
	uint8_t tblPalette[32];	  // Palette RAM
	uint8_t tblPattern[2][4096]; //Javid stuff

public:
	// Interface
	void ConnectCartridge(const std::shared_ptr<Cartridge> &cartridge);
	void Clock();

	bool nmi = false;

private:
	olc::Pixel palScreen[0x40];
	olc::Sprite sprScreen = olc::Sprite(256, 240);
	olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
	olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
	//Debugging Utils
	olc::Sprite &GetScreen();
	olc::Sprite &GetNameTable(uint8_t i);
	olc::Sprite &GetPatternTable(uint8_t i, uint8_t palette);
	olc::Pixel &GetColorFromPaletteRam(uint8_t palette, uint8_t pixel);
	bool frame_complete = false;

private:
	int16_t scanline = 0;
	int16_t cycle = 0;

	union
	{
		struct
		{
			uint8_t unused : 5;
			uint8_t sprite_overflow : 1;
			uint8_t sprite_zero_hit : 1;
			uint8_t vertical_blank : 1;
		};

		uint8_t reg;
	} status;

	union
	{
		struct
		{
			uint8_t grayscale : 1;
			uint8_t render_bg_left : 1;
			uint8_t render_spr_left : 1;
			uint8_t render_bg : 1;
			uint8_t render_spr : 1;
			uint8_t enhance_red : 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blue : 1;
		};

		uint8_t reg;
	} mask;

	union PPUCTRL
	{
		struct
		{
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_spr : 1;
			uint8_t pattern_bg : 1;
			uint8_t spr_size : 1;
			uint8_t slave_mode : 1; //Do not set this on real hardware or it will fry the PPU!
			uint8_t enable_nmi : 1;
		};

		uint8_t reg;
	} control;

	uint8_t address_latch = 0x00;
	uint8_t ppu_data_buffer = 0x00;
	uint16_t ppu_address = 0x0000;
};

