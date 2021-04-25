

#include "CPU.h"
#include "Bus.h"
#include <iostream>

CPU::CPU()
{
	using A = CPU;
	lookup =
	{
		{ "BRK", &A::BRK, &A::IMM, 7 },{ "ORA", &A::ORA, &A::IZX, 6 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 3 },{ "ORA", &A::ORA, &A::ZP0, 3 },{ "ASL", &A::ASL, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "PHP", &A::PHP, &A::IMP, 3 },{ "ORA", &A::ORA, &A::IMM, 2 },{ "ASL", &A::ASL, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::NOP, &A::IMP, 4 },{ "ORA", &A::ORA, &A::ABS, 4 },{ "ASL", &A::ASL, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BPL", &A::BPL, &A::REL, 2 },{ "ORA", &A::ORA, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "ORA", &A::ORA, &A::ZPX, 4 },{ "ASL", &A::ASL, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "CLC", &A::CLC, &A::IMP, 2 },{ "ORA", &A::ORA, &A::ABY, 4 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "ORA", &A::ORA, &A::ABX, 4 },{ "ASL", &A::ASL, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
		{ "JSR", &A::JSR, &A::ABS, 6 },{ "AND", &A::AND, &A::IZX, 6 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "BIT", &A::BIT, &A::ZP0, 3 },{ "AND", &A::AND, &A::ZP0, 3 },{ "ROL", &A::ROL, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "PLP", &A::PLP, &A::IMP, 4 },{ "AND", &A::AND, &A::IMM, 2 },{ "ROL", &A::ROL, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "BIT", &A::BIT, &A::ABS, 4 },{ "AND", &A::AND, &A::ABS, 4 },{ "ROL", &A::ROL, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BMI", &A::BMI, &A::REL, 2 },{ "AND", &A::AND, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "AND", &A::AND, &A::ZPX, 4 },{ "ROL", &A::ROL, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "SEC", &A::SEC, &A::IMP, 2 },{ "AND", &A::AND, &A::ABY, 4 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "AND", &A::AND, &A::ABX, 4 },{ "ROL", &A::ROL, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
		{ "RTI", &A::RTI, &A::IMP, 6 },{ "EOR", &A::EOR, &A::IZX, 6 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 3 },{ "EOR", &A::EOR, &A::ZP0, 3 },{ "LSR", &A::LSR, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "PHA", &A::PHA, &A::IMP, 3 },{ "EOR", &A::EOR, &A::IMM, 2 },{ "LSR", &A::LSR, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "JMP", &A::JMP, &A::ABS, 3 },{ "EOR", &A::EOR, &A::ABS, 4 },{ "LSR", &A::LSR, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BVC", &A::BVC, &A::REL, 2 },{ "EOR", &A::EOR, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "EOR", &A::EOR, &A::ZPX, 4 },{ "LSR", &A::LSR, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "CLI", &A::CLI, &A::IMP, 2 },{ "EOR", &A::EOR, &A::ABY, 4 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "EOR", &A::EOR, &A::ABX, 4 },{ "LSR", &A::LSR, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
		{ "RTS", &A::RTS, &A::IMP, 6 },{ "ADC", &A::ADC, &A::IZX, 6 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 3 },{ "ADC", &A::ADC, &A::ZP0, 3 },{ "ROR", &A::ROR, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "PLA", &A::PLA, &A::IMP, 4 },{ "ADC", &A::ADC, &A::IMM, 2 },{ "ROR", &A::ROR, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "JMP", &A::JMP, &A::IND, 5 },{ "ADC", &A::ADC, &A::ABS, 4 },{ "ROR", &A::ROR, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BVS", &A::BVS, &A::REL, 2 },{ "ADC", &A::ADC, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "ADC", &A::ADC, &A::ZPX, 4 },{ "ROR", &A::ROR, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "SEI", &A::SEI, &A::IMP, 2 },{ "ADC", &A::ADC, &A::ABY, 4 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "ADC", &A::ADC, &A::ABX, 4 },{ "ROR", &A::ROR, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
		{ "???", &A::NOP, &A::IMP, 2 },{ "STA", &A::STA, &A::IZX, 6 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 6 },{ "STY", &A::STY, &A::ZP0, 3 },{ "STA", &A::STA, &A::ZP0, 3 },{ "STX", &A::STX, &A::ZP0, 3 },{ "???", &A::XXX, &A::IMP, 3 },{ "DEY", &A::DEY, &A::IMP, 2 },{ "???", &A::NOP, &A::IMP, 2 },{ "TXA", &A::TXA, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "STY", &A::STY, &A::ABS, 4 },{ "STA", &A::STA, &A::ABS, 4 },{ "STX", &A::STX, &A::ABS, 4 },{ "???", &A::XXX, &A::IMP, 4 },
		{ "BCC", &A::BCC, &A::REL, 2 },{ "STA", &A::STA, &A::IZY, 6 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 6 },{ "STY", &A::STY, &A::ZPX, 4 },{ "STA", &A::STA, &A::ZPX, 4 },{ "STX", &A::STX, &A::ZPY, 4 },{ "???", &A::XXX, &A::IMP, 4 },{ "TYA", &A::TYA, &A::IMP, 2 },{ "STA", &A::STA, &A::ABY, 5 },{ "TXS", &A::TXS, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 5 },{ "???", &A::NOP, &A::IMP, 5 },{ "STA", &A::STA, &A::ABX, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "???", &A::XXX, &A::IMP, 5 },
		{ "LDY", &A::LDY, &A::IMM, 2 },{ "LDA", &A::LDA, &A::IZX, 6 },{ "LDX", &A::LDX, &A::IMM, 2 },{ "???", &A::XXX, &A::IMP, 6 },{ "LDY", &A::LDY, &A::ZP0, 3 },{ "LDA", &A::LDA, &A::ZP0, 3 },{ "LDX", &A::LDX, &A::ZP0, 3 },{ "???", &A::XXX, &A::IMP, 3 },{ "TAY", &A::TAY, &A::IMP, 2 },{ "LDA", &A::LDA, &A::IMM, 2 },{ "TAX", &A::TAX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "LDY", &A::LDY, &A::ABS, 4 },{ "LDA", &A::LDA, &A::ABS, 4 },{ "LDX", &A::LDX, &A::ABS, 4 },{ "???", &A::XXX, &A::IMP, 4 },
		{ "BCS", &A::BCS, &A::REL, 2 },{ "LDA", &A::LDA, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 5 },{ "LDY", &A::LDY, &A::ZPX, 4 },{ "LDA", &A::LDA, &A::ZPX, 4 },{ "LDX", &A::LDX, &A::ZPY, 4 },{ "???", &A::XXX, &A::IMP, 4 },{ "CLV", &A::CLV, &A::IMP, 2 },{ "LDA", &A::LDA, &A::ABY, 4 },{ "TSX", &A::TSX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 4 },{ "LDY", &A::LDY, &A::ABX, 4 },{ "LDA", &A::LDA, &A::ABX, 4 },{ "LDX", &A::LDX, &A::ABY, 4 },{ "???", &A::XXX, &A::IMP, 4 },
		{ "CPY", &A::CPY, &A::IMM, 2 },{ "CMP", &A::CMP, &A::IZX, 6 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "CPY", &A::CPY, &A::ZP0, 3 },{ "CMP", &A::CMP, &A::ZP0, 3 },{ "DEC", &A::DEC, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "INY", &A::INY, &A::IMP, 2 },{ "CMP", &A::CMP, &A::IMM, 2 },{ "DEX", &A::DEX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 2 },{ "CPY", &A::CPY, &A::ABS, 4 },{ "CMP", &A::CMP, &A::ABS, 4 },{ "DEC", &A::DEC, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BNE", &A::BNE, &A::REL, 2 },{ "CMP", &A::CMP, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "CMP", &A::CMP, &A::ZPX, 4 },{ "DEC", &A::DEC, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "CLD", &A::CLD, &A::IMP, 2 },{ "CMP", &A::CMP, &A::ABY, 4 },{ "NOP", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "CMP", &A::CMP, &A::ABX, 4 },{ "DEC", &A::DEC, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
		{ "CPX", &A::CPX, &A::IMM, 2 },{ "SBC", &A::SBC, &A::IZX, 6 },{ "???", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "CPX", &A::CPX, &A::ZP0, 3 },{ "SBC", &A::SBC, &A::ZP0, 3 },{ "INC", &A::INC, &A::ZP0, 5 },{ "???", &A::XXX, &A::IMP, 5 },{ "INX", &A::INX, &A::IMP, 2 },{ "SBC", &A::SBC, &A::IMM, 2 },{ "NOP", &A::NOP, &A::IMP, 2 },{ "???", &A::SBC, &A::IMP, 2 },{ "CPX", &A::CPX, &A::ABS, 4 },{ "SBC", &A::SBC, &A::ABS, 4 },{ "INC", &A::INC, &A::ABS, 6 },{ "???", &A::XXX, &A::IMP, 6 },
		{ "BEQ", &A::BEQ, &A::REL, 2 },{ "SBC", &A::SBC, &A::IZY, 5 },{ "???", &A::XXX, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 8 },{ "???", &A::NOP, &A::IMP, 4 },{ "SBC", &A::SBC, &A::ZPX, 4 },{ "INC", &A::INC, &A::ZPX, 6 },{ "???", &A::XXX, &A::IMP, 6 },{ "SED", &A::SED, &A::IMP, 2 },{ "SBC", &A::SBC, &A::ABY, 4 },{ "NOP", &A::NOP, &A::IMP, 2 },{ "???", &A::XXX, &A::IMP, 7 },{ "???", &A::NOP, &A::IMP, 4 },{ "SBC", &A::SBC, &A::ABX, 4 },{ "INC", &A::INC, &A::ABX, 7 },{ "???", &A::XXX, &A::IMP, 7 },
	};
	
	
}

CPU::~CPU()
{

}

/*CPU::Reset() //emulation of the Reset button
* {
*	sp -= 3;
*	SetFlag(I, true);
*	//Set 0x4015 to 0;
*	//APU Triangle phase set to 0;
*	//APU DPCM && 1
*	//if 2A03G APU Frame Counter = 0, else no change
* }
*/

uint8_t CPU::cpuRead(uint16_t addr)
{
	return bus->cpuRead(addr, false);
}

void CPU::cpuWrite(uint16_t addr, uint8_t data)
{
	bus->cpuWrite(addr, data);
}

void CPU::clock()
{
	if (cycles == 0)
	{
		SetFlag(U, true);

		opcode = cpuRead(pc);
		pc++;

		cycles = lookup[opcode].cycles;
		if(lookup[opcode].name == "JSR")
		{
			uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)(); //use the opcode to call the address mode function
			uint8_t additional_cycle2 = (this->*lookup[opcode].operate)(); //use the opcode to call the opcode function
			cycles += (additional_cycle1 & additional_cycle2);
		}
		else
		{
			uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)(); //use the opcode to call the address mode function
			uint8_t additional_cycle2 = (this->*lookup[opcode].operate)(); //use the opcode to call the opcode function
			cycles += (additional_cycle1 & additional_cycle2);
		}

		 //adds cycles based on the returned value of the address mode and the opcode performed.
		SetFlag(U, true);
	}

	cycles--;
	clock_count++;
}

uint8_t CPU::GetFlag(FLAGS2A03 f)
{
	return ((status & f) > 0 ? 1 : 0);
}

void CPU::SetFlag(FLAGS2A03 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

// Addressing Modes
uint8_t CPU::IMP()
{
	fetched = a;
	return 0;
}

uint8_t CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

uint8_t CPU::ZP0()
{
	addr_abs = cpuRead(pc);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPX()
{
	addr_abs = cpuRead(pc) + x;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPY()
{
	addr_abs = cpuRead(pc) + y;
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::REL()
{
	addr_rel = cpuRead(pc);
	pc++;

	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;

	return 0;
}

uint8_t CPU::ABS()
{
	uint16_t lo = cpuRead(pc);
	pc++;
	uint16_t hi = cpuRead(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t CPU::ABX()
{
	uint16_t lo = cpuRead(pc);
	pc++;
	uint16_t hi = cpuRead(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t CPU::ABY()
{
	uint16_t lo = cpuRead(pc);
	pc++;
	uint16_t hi = cpuRead(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t CPU::IND() // Determine the actual address from the address pointed to by the given address
{
	uint16_t ptr_lo = cpuRead(pc);
	pc++;
	uint16_t ptr_hi = cpuRead(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF) //Implement page boudary hardware bug
	{
		addr_abs = (cpuRead(ptr & 0xFF00) << 8) | cpuRead(ptr + 0);
	}
	else
	{
		addr_abs = (cpuRead(ptr + 1) << 8) | cpuRead(ptr + 0);
	}

	return 0;
}

uint8_t CPU::IZX()
{
	uint16_t t = cpuRead(pc);
	pc++;

	uint16_t lo = cpuRead((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = cpuRead((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t CPU::IZY() //This is NOT a y compliment to IZY, it has different behavior
{
	uint16_t t = cpuRead(pc);
	pc++;

	uint16_t lo = cpuRead(t & 0x00FF);
	uint16_t hi = cpuRead((t+1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0x00FF) != (hi << 8))
		return 1;
	else
		return 0;
}

//Instructions
uint8_t CPU::fetch()
{
	if (!(lookup[opcode].addrmode == &CPU::IMP))
		fetched = cpuRead(addr_abs);

	return fetched;
}

uint8_t CPU::ADC() 
{
	fetch();

	temp = a + fetched + GetFlag(C);

	SetFlag(C, temp > 0xFF);
	SetFlag(Z, (temp & 0x00FF) == 0);
	SetFlag(N, temp & 0x80);
	SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ temp)) & 0x0080);
	a = temp & 0x00FF;
	return 1;
}


uint8_t CPU::AND()
{
	fetch();

	a &= fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t CPU::ASL() //arithmetic shift left
{
	fetch();

	temp = (uint16_t)(fetched << 1);


	SetFlag(C, temp > 255); 
	SetFlag(Z, (temp & 0xFF) == 0x00);
	SetFlag(N, temp & 0x80);

	if (lookup[opcode].addrmode == &CPU::IMP)
		a = (uint8_t)(temp & 0x00FF);
	else
		cpuWrite(addr_abs, (uint8_t)(temp & 0x00FF));

	return 0;
}

//branch if something
uint8_t CPU::BCC() //Branch Carry Clear
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BCS() //Branch Carry Set
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BEQ() 
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BIT() //Bit Test - test if one or more bits are set in target location by: a && {addr}, this sets or clears Z. Bits 7 and 6 from {addr} are copied to N and V respectively.
{
	fetch();
	temp = a & fetched;
	SetFlag(Z, (temp & 0x00FF) == 0x00 );
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	return 0;
}

uint8_t CPU::BMI() //Branch if negative
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BNE() //Branch if Not Equal
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BPL() //Branch if Positive 
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BRK()  //Break - Sets B flag to 1
{
	//TODO: need more info - for now, this is just a copy of NMI but with the B flag set instead of cleared
	
	//write the value of the program counter to the stack
	cpuWrite(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	cpuWrite(0x0100 + sp, pc & 0x00FF);
	sp--;

	//write the state to the stack
	SetFlag(B, 1);
	SetFlag(U, 1); //this is not needed, U should ALWAYS be 1 on the NES
	SetFlag(I, 1);
	cpuWrite(0x0100 + sp, status);
	sp--;

	addr_abs = 0xFFFE;
	uint16_t lo = cpuRead(addr_abs + 0);
	uint16_t hi = cpuRead(addr_abs + 1);

	pc = (hi << 8) | lo;

	cycles = 7;

	return 0;
}

uint8_t CPU::BVC() 
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BVS() 
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc * 0xFF00))
			cycles++;

		pc = addr_abs;
	}

	return 0;
}


//Clear a flag
uint8_t CPU::CLC()
{
	SetFlag(C, false);
	return 0;
}

uint8_t CPU::CLD()
{
	SetFlag(D, false);
	return 0;
}

uint8_t CPU::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t CPU::CLV()
{
	SetFlag(V, false);
	return 0;
}

//compare
uint8_t CPU::CMP()
{
	uint8_t mem = fetch();
	uint8_t value = a - mem;

	SetFlag(Z, value == 0x00);
	SetFlag(C, a >= mem);
	SetFlag(N, value & 0x80);
	return 0;
}

uint8_t CPU::CPX() 
{
	uint8_t mem = fetch();
	uint8_t value = x - mem;

	SetFlag(Z, value == 0x00);
	SetFlag(C, x >= mem);
	SetFlag(N, value & 0x80);
	return 0;
}

uint8_t CPU::CPY() 
{
	uint8_t mem = fetch();
	uint8_t value = y - mem;

	SetFlag(Z, value == 0x00);
	SetFlag(C, y >= mem);
	SetFlag(N, value & 0x80);
	return 0;
}


//Decrement
uint8_t CPU::DEC() // Unlike normal logic would lead you to beleive, this decrements a provided memory address and NOT the Accumulator!
{
	uint8_t value = cpuRead(addr_abs);
	value--;

	SetFlag(Z, value == 0x00);
	SetFlag(N, value & 0x80);

	cpuWrite(addr_abs, value);

	return 0;
}

uint8_t CPU::DEX() 
{
	x--;

	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::DEY() 
{
	y--;

	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t CPU::EOR() //eXclusive OR
{
	uint8_t value = cpuRead(pc);

	a ^= value;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 0;
}


//Increment
uint8_t CPU::INC() //opposite of DEC, effects a memory location not the Accumulator!
{
	uint8_t value = cpuRead(addr_abs);
	value++;

	SetFlag(Z, value == 0x00);
	SetFlag(N, value & 0x80);
	cpuWrite(addr_abs, value);

	return 0;
}

uint8_t CPU::INX() 
{
	x++;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::INY() 
{
	y++;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);

	return 0;
}


//Jump commands
uint8_t CPU::JMP() //Everybody JuMP! 
{
	pc = addr_abs;

	return 0;
}

uint8_t CPU::JSR() // Jump to SubRoutine
{
	//store the return address - 1 to the stack
	pc--;
	cpuWrite(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	cpuWrite(0x0100 + sp, pc & 0x00FF);
	sp--;

	//jump
	pc = addr_abs;

	return 0;
}


//Load something to a register
uint8_t CPU::LDA() 
{
	fetch();

	if(addr_abs == 0xFF78 + x && x >= 0x20)
	{
		//DebugBreak();
	}

	a = fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::LDX() 
{
	fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t CPU::LDY() 
{
	fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}


uint8_t CPU::LSR() 
{
	fetch();
	//set carry if old bit 0 is 1
	SetFlag(C, fetched & 0x01);
	//perform right shift
	fetched = fetched >> 1;

	//set Z if 0, and N if result is negative - should always be positive!
	SetFlag(Z, fetched == 0x00);
	SetFlag(N, fetched & 0x80); //if N goes high here, we've got an error!

	if(lookup[opcode].addrmode == &CPU::IMP)
		a = fetched;
	else
		cpuWrite(addr_abs, fetched);

	return 0;
}


// NO oPeration
uint8_t CPU::NOP() 
{
	//this function literally does nothing but burn cycles

	return 0;
}


uint8_t CPU::ORA() 
{
	a |= cpuRead(addr_abs);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::PHA() //Push Accumulator to the stack - stack grows DOWN
{
	cpuWrite(0x0100 + sp, a);
	sp--;
	return 0;
}

uint8_t CPU::PHP() 
{
	cpuWrite(0x0100 + sp, status);
	sp--;
	return 0;
}

uint8_t CPU::PLA() //Pop from stack to Accumulator
{
	sp++;
	a = cpuRead(0x0100 + sp);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::PLP() 
{
	sp++;
	status = cpuRead(0x0100 + sp);
	SetFlag(Z, status == 0x00);
	SetFlag(N, status & 0x80);
	return 0;
}

uint8_t CPU::ROL() 
{
	uint8_t value;

	if(lookup[opcode].addrmode == &CPU::IMP) //accumulator shift
	{
		value = a;

		uint8_t oldC = GetFlag(C);	//we need this for a correct rotation

		SetFlag(C, a & 0x80); //rotating left, we want bit 7 before the shift

		value = (value << 1) | oldC; //shift 1 bit left, tack on Carry to the right most bit
		a = value;
	}
	else // memory location shift
	{
		fetch();
		value = fetched;

		uint8_t oldC = GetFlag(C);

		SetFlag(C, value & 0x80);

		value = (value << 1) | oldC;
		cpuWrite(addr_abs, value);
	}

	SetFlag(Z, value == 0x00);
	SetFlag(N, value & 0x80);

	return 0;
}

uint8_t CPU::ROR() 
{
	uint8_t value;

	if(lookup[opcode].addrmode == &CPU::IMP) //accumulator shift
	{
		value = a;

		bool oldC = GetFlag(C);
		
		value = (value >> 1) | (GetFlag(C) << 7); //shift 1 bit right, tack on Carry to the left most bit
		SetFlag(C, a & 0x01); //set Carry to the old bit 0
		
		a = value;
	}
	else // memory location shift
	{
		fetch();
		value = fetched;
		
		value = (value >> 1) | (GetFlag(C) << 7);
		SetFlag(C, fetched & 0x01);

		cpuWrite(addr_abs, value);
	}

	SetFlag(Z, value == 0x00);
	SetFlag(N, value & 0x80);
	return 0;
}

uint8_t CPU::RTI() //return from interrupt
{
	//Pop the status from the stack
	sp++;
	status = cpuRead(0x0100 + sp);
	//status &= ~B;
	SetFlag(U, 1);

	//pop the previous program counter from the stack
	sp++;
	pc = (uint16_t)cpuRead(0x0100 + sp);
	sp++;
	pc |= (uint16_t)cpuRead(0x0100 + sp) << 8;

	return 0;
}

uint8_t CPU::RTS() //return from subroutine
{
	sp++;
	pc = (uint16_t)cpuRead(0x0100 + sp);
	sp++;
	pc |= (uint16_t)cpuRead(0x0100 + sp) << 8;

	pc++;

	return 0;
}

uint8_t CPU::SBC() // Subtraction
{
	fetch();

	//uint16_t value = ((uint16_t)fetched) ^ 0x00FF;

	temp = (uint16_t)a - fetched - (1 - (uint16_t)GetFlag(C));

	SetFlag(C, temp > 255);
	SetFlag(Z, ((temp & 0x00FF) == 0));
	SetFlag(N, temp & 0x80);
	SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ fetched) & 0x0080);
	a = temp & 0x00FF;
	return 1;
}

uint8_t CPU::SEC() 
{
	SetFlag(C, true);

	return 0;
}

uint8_t CPU::SED() 
{
	SetFlag(D, true);

	return 0;
}

uint8_t CPU::SEI() 
{
	SetFlag(I, true);

	return 0;
}


// Store A, X, or Y to a memory location addr_abs
uint8_t CPU::STA() 
{
	cpuWrite(addr_abs, a);
	return 0;
}

uint8_t CPU::STX()
{
	cpuWrite(addr_abs, x);
	return 0;
}

uint8_t CPU::STY() 
{
	cpuWrite(addr_abs, y);
	return 0;
}

uint8_t CPU::TAX() 
{
	x = a;
	return 0;
}

uint8_t CPU::TAY() 
{
	y = a;
	return 0;
}

uint8_t CPU::TSX() 
{
	x = sp;
	return 0;
}

uint8_t CPU::TXA() // Transfer X to Accumulator - sets Z, N
{
	a = x;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::TXS() 
{
	sp = x;
	return 0;
}

uint8_t CPU::TYA() 
{
	a = y;

	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t CPU::XXX()
{
	return 0;
}

void CPU::reset()
{
	addr_abs = 0xFFFC;
	uint16_t lo = cpuRead(addr_abs + 0);
	uint16_t hi = cpuRead(addr_abs + 1);

	pc = (hi << 8) | lo;
	//pc = 0xC000;

	// The next line is not what happens when reset is called on the NES!
	a = x = y = 0;
	sp = 0xFD;
	status = (0x00 | U) | I;

	

	
	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

void CPU::irq()
{
	if (GetFlag(I) == 0)
	{
		//write the value of the program counter to the stack
		cpuWrite(0x0100 + sp, (pc >> 8) & 0x00FF);
		sp--;
		cpuWrite(0x0100 + sp, pc & 0x00FF);
		sp--;

		//write the state to the stack
		SetFlag(B, 0);
		SetFlag(U, 1); //this is not needed, U should ALWAYS be 1 on the NES
		SetFlag(I, 1);
		cpuWrite(0x0100 + sp, status);
		sp--;

		addr_abs = 0xFFFE;
		uint16_t lo = cpuRead(addr_abs + 0);
		uint16_t hi = cpuRead(addr_abs + 1);

		pc = (hi << 8) | lo;

		cycles = 7;

	}

}

void CPU::nmi()
{
	//write the value of the program counter to the stack
	cpuWrite(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	cpuWrite(0x0100 + sp, pc & 0x00FF);
	sp--;

	//write the state to the stack
	SetFlag(B, 0);
	SetFlag(U, 1); //this is not needed, U should ALWAYS be 1 on the NES
	SetFlag(I, 1);
	cpuWrite(0x0100 + sp, status);
	sp--;

	addr_abs = 0xFFFA;
	uint16_t lo = cpuRead(addr_abs + 0);
	uint16_t hi = cpuRead(addr_abs + 1);

	pc = (hi << 8) | lo;

	cycles = 8;

}

bool CPU::complete()
{
	return cycles == 0;
}

// This is the disassembly function. Its workings are not required for emulation.
// It is merely a convenience function to turn the binary instruction code into
// human readable form. Its included as part of the emulator because it can take
// advantage of many of the CPUs internal operations to do this.
std::map<uint16_t, std::string> CPU::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	// A convenient utility to convert variables into
	// hex strings because "modern C++"'s method with 
	// streams is atrocious
	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	// Starting at the specified address we read an instruction
	// byte, which in turn yields information from the lookup table
	// as to how many additional bytes we need to read and what the
	// addressing mode is. I need this info to assemble human readable
	// syntax, which is different depending upon the addressing mode

	// As the instruction is decoded, a std::string is assembled
	// with the readable output
	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		// Prefix line with instruction address
		std::string sInst = "$" + hex(addr, 4) + ": ";

		// Read instruction, and get its readable name
		uint8_t opcode = bus->cpuRead(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		// Get oprands from desired locations, and form the
		// instruction based upon its addressing mode. These
		// routines mimmick the actual fetch routine of the
		// 6502 in order to get accurate data as part of the
		// instruction
		if (lookup[opcode].addrmode == &CPU::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &CPU::IMM)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZP0)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABS)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IND)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &CPU::REL)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + (int8_t)value, 4) + "] {REL}";
		}

		// Add the formed string to a std::map, using the instruction's
		// address as the key. This makes it convenient to look for later
		// as the instructions are variable in length, so a straight up
		// incremental index is not sufficient.
		mapLines[line_addr] = sInst;
	}

	return mapLines;
}

