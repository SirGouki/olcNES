#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Mapper_000.h"


class Cartridge
{
public:
	Cartridge(const std::string &sFileName);
	~Cartridge();

	bool ImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI
	} mirror = HORIZONTAL;

private:
	bool bImageValid = false;
	std::vector<uint8_t> vPRGMemory; //Program ROM
	std::vector<uint8_t> vCHRMemory; //CHR ROM

	uint8_t nMapperID = 0; //which mapper to use
	uint8_t nPRGBanks = 0; // how many "partitions" are in the PRG
	uint8_t nCHRBanks = 0; // how many "partitions" are in the CHR

	std::shared_ptr<Mapper> pMapper;

public:

	//Comunicate with the main bus
	bool cpuRead(uint16_t addr, uint8_t &data);
	bool cpuWrite(uint16_t addr, uint8_t data);

	//Communication with the PPU bus
	bool ppuRead(uint16_t addr, uint8_t &data);
	bool ppuWrite(uint16_t addr, uint8_t data);

};

