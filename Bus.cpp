#include "Bus.h"

/* Bus Layout -
* assume all numbers before : are hex addresses (prefixed with 0x)
* 0000-07FF : 2KB of internal RAM
* 0800-0FFF :
* 1000-17FF : All 3 of these ranges are mirrors of 0000-07FF
* 1800-1FFF :
* 2000-2007 : PPU - Registers
* 2008-3FFF : PPU - Mirrors of 2000-2007 (repeats every 8 bytes)
* 4000-4017 : APU and I/O registers
* 4018-401F : APU and I/O functionality that is normall Disabled.
* 4020-FFFF : Cartridge space: PRG ROM, PRG RAM, and mapper registers.
* 
* ROM Section -
* 6000-7FFF : SRAM or Work RAM
* 8000-FFFF : ROM, commonly with Mapper Registers (MMC1 and UxROM)
* 
* CPU expects the following - 
* FFFA-FFFB : NMI Vector
* FFFC-FFFD : Reset Vector
* FFFE-FFFF : IRQ/BRK vector
* If a mapper doesn't set FFFA-FFFF in to some known Bank, or use some sort of reset detection, the vectors should be stored in all banks.
* 
*/


Bus::Bus()
{
	//init RAM - note: Some NESes set this to a fixed pattern, or set this seemingly at random
	for (auto& i : cpuRam) i = 0x00;

	

	//Connect to the CPU
	cpu.ConnectBus(this);
}

Bus::~Bus()
{
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{
	uint8_t data = 0x00;
	if(cart->cpuRead(addr, data))
	{

	}
	else if(addr >= 0x0000 && addr <= 0x1FFF)
		data = cpuRam[addr & 0x07ff]; //to simulate mirroring
	else if(addr >= 0x2000 && addr <= 0x3FFF)
		data = ppu.cpuRead(addr & 0x0007, bReadOnly);
	


	return data;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &Cartridge)
{
	this->cart = Cartridge;
	ppu.ConnectCartridge(Cartridge);
}

void Bus::reset()
{
	cpu.reset();
	nSystemClockCounter = 0;
}

void Bus::clock()
{
	ppu.Clock();

	if(nSystemClockCounter % 3 == 0)
		cpu.clock();

	if(ppu.nmi)
	{
		ppu.nmi = false;
		cpu.nmi();
	}

	nSystemClockCounter++;

}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
	if(cart->cpuWrite(addr, data))
	{

	}
	else if(addr >= 0x0000 && addr <= 0x1FFF) //later this will be used to decide which device on the bus to communicate with
		cpuRam[addr & 0x07ff] = data;
	else if(addr >= 0x2000 && addr <= 0x3FFF)
		ppu.cpuWrite(addr & 0x0007, data);
}