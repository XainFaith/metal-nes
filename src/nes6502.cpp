#include <nes6502.hpp>
#include <nesbus.hpp>

Nes6502::Nes6502()
{
    
    using NES = Nes6502;
	this->lookup = new INSTRUCTION[0xFF];
    this->add_ins({ "BRK", &NES::BRK, &NES::IMM, 7 });
    this->add_ins({ "ORA", &NES::ORA, &NES::IZX, 6 }); 
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 3 });
    this->add_ins({ "ORA", &NES::ORA, &NES::ZP0, 3 });
    this->add_ins({ "ASL", &NES::ASL, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "PHP", &NES::PHP, &NES::IMP, 3 });
    this->add_ins({ "ORA", &NES::ORA, &NES::IMM, 2 });
    this->add_ins({ "ASL", &NES::ASL, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "ORA", &NES::ORA, &NES::ABS, 4 });
    this->add_ins({ "ASL", &NES::ASL, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BPL", &NES::BPL, &NES::REL, 2 });
    this->add_ins({ "ORA", &NES::ORA, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "ORA", &NES::ORA, &NES::ZPX, 4 });
    this->add_ins({ "ASL", &NES::ASL, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "CLC", &NES::CLC, &NES::IMP, 2 });
    this->add_ins({ "ORA", &NES::ORA, &NES::ABY, 4 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "ORA", &NES::ORA, &NES::ABX, 4 });
    this->add_ins({ "ASL", &NES::ASL, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "JSR", &NES::JSR, &NES::ABS, 6 });
    this->add_ins({ "AND", &NES::AND, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "BIT", &NES::BIT, &NES::ZP0, 3 });
    this->add_ins({ "AND", &NES::AND, &NES::ZP0, 3 });
    this->add_ins({ "ROL", &NES::ROL, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "PLP", &NES::PLP, &NES::IMP, 4 });
    this->add_ins({ "AND", &NES::AND, &NES::IMM, 2 });
    this->add_ins({ "ROL", &NES::ROL, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "BIT", &NES::BIT, &NES::ABS, 4 });
    this->add_ins({ "AND", &NES::AND, &NES::ABS, 4 });
    this->add_ins({ "ROL", &NES::ROL, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BMI", &NES::BMI, &NES::REL, 2 });
    this->add_ins({ "AND", &NES::AND, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "AND", &NES::AND, &NES::ZPX, 4 });
    this->add_ins({ "ROL", &NES::ROL, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "SEC", &NES::SEC, &NES::IMP, 2 });
    this->add_ins({ "AND", &NES::AND, &NES::ABY, 4 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "AND", &NES::AND, &NES::ABX, 4 });
    this->add_ins({ "ROL", &NES::ROL, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "RTI", &NES::RTI, &NES::IMP, 6 });
    this->add_ins({ "EOR", &NES::EOR, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 3 });
    this->add_ins({ "EOR", &NES::EOR, &NES::ZP0, 3 });
    this->add_ins({ "LSR", &NES::LSR, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "PHA", &NES::PHA, &NES::IMP, 3 });
    this->add_ins({ "EOR", &NES::EOR, &NES::IMM, 2 });
    this->add_ins({ "LSR", &NES::LSR, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "JMP", &NES::JMP, &NES::ABS, 3 });
    this->add_ins({ "EOR", &NES::EOR, &NES::ABS, 4 });
    this->add_ins({ "LSR", &NES::LSR, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BVC", &NES::BVC, &NES::REL, 2 });
    this->add_ins({ "EOR", &NES::EOR, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "EOR", &NES::EOR, &NES::ZPX, 4 });
    this->add_ins({ "LSR", &NES::LSR, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "CLI", &NES::CLI, &NES::IMP, 2 });
    this->add_ins({ "EOR", &NES::EOR, &NES::ABY, 4 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "EOR", &NES::EOR, &NES::ABX, 4 });
    this->add_ins({ "LSR", &NES::LSR, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "RTS", &NES::RTS, &NES::IMP, 6 });
    this->add_ins({ "ADC", &NES::ADC, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 3 });
    this->add_ins({ "ADC", &NES::ADC, &NES::ZP0, 3 });
    this->add_ins({ "ROR", &NES::ROR, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "PLA", &NES::PLA, &NES::IMP, 4 });
    this->add_ins({ "ADC", &NES::ADC, &NES::IMM, 2 });
    this->add_ins({ "ROR", &NES::ROR, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "JMP", &NES::JMP, &NES::IND, 5 });
    this->add_ins({ "ADC", &NES::ADC, &NES::ABS, 4 });
    this->add_ins({ "ROR", &NES::ROR, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BVS", &NES::BVS, &NES::REL, 2 });
    this->add_ins({ "ADC", &NES::ADC, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "ADC", &NES::ADC, &NES::ZPX, 4 });
    this->add_ins({ "ROR", &NES::ROR, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "SEI", &NES::SEI, &NES::IMP, 2 });
    this->add_ins({ "ADC", &NES::ADC, &NES::ABY, 4 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "ADC", &NES::ADC, &NES::ABX, 4 });
    this->add_ins({ "ROR", &NES::ROR, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "STA", &NES::STA, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "STY", &NES::STY, &NES::ZP0, 3 });
    this->add_ins({ "STA", &NES::STA, &NES::ZP0, 3 });
    this->add_ins({ "STX", &NES::STX, &NES::ZP0, 3 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 3 });
    this->add_ins({ "DEY", &NES::DEY, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "TXA", &NES::TXA, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "STY", &NES::STY, &NES::ABS, 4 });
    this->add_ins({ "STA", &NES::STA, &NES::ABS, 4 });
    this->add_ins({ "STX", &NES::STX, &NES::ABS, 4 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "BCC", &NES::BCC, &NES::REL, 2 });
    this->add_ins({ "STA", &NES::STA, &NES::IZY, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "STY", &NES::STY, &NES::ZPX, 4 });
    this->add_ins({ "STA", &NES::STA, &NES::ZPX, 4 });
    this->add_ins({ "STX", &NES::STX, &NES::ZPY, 4 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "TYA", &NES::TYA, &NES::IMP, 2 });
    this->add_ins({ "STA", &NES::STA, &NES::ABY, 5 });
    this->add_ins({ "TXS", &NES::TXS, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 5 });
    this->add_ins({ "STA", &NES::STA, &NES::ABX, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "LDY", &NES::LDY, &NES::IMM, 2 });
    this->add_ins({ "LDA", &NES::LDA, &NES::IZX, 6 });
    this->add_ins({ "LDX", &NES::LDX, &NES::IMM, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "LDY", &NES::LDY, &NES::ZP0, 3 });
    this->add_ins({ "LDA", &NES::LDA, &NES::ZP0, 3 });
    this->add_ins({ "LDX", &NES::LDX, &NES::ZP0, 3 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 3 });
    this->add_ins({ "TAY", &NES::TAY, &NES::IMP, 2 });
    this->add_ins({ "LDA", &NES::LDA, &NES::IMM, 2 });
    this->add_ins({ "TAX", &NES::TAX, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "LDY", &NES::LDY, &NES::ABS, 4 });
    this->add_ins({ "LDA", &NES::LDA, &NES::ABS, 4 });
    this->add_ins({ "LDX", &NES::LDX, &NES::ABS, 4 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "BCS", &NES::BCS, &NES::REL, 2 });
    this->add_ins({ "LDA", &NES::LDA, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "LDY", &NES::LDY, &NES::ZPX, 4 });
    this->add_ins({ "LDA", &NES::LDA, &NES::ZPX, 4 });
    this->add_ins({ "LDX", &NES::LDX, &NES::ZPY, 4 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "CLV", &NES::CLV, &NES::IMP, 2 });
    this->add_ins({ "LDA", &NES::LDA, &NES::ABY, 4 });
    this->add_ins({ "TSX", &NES::TSX, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "LDY", &NES::LDY, &NES::ABX, 4 });
    this->add_ins({ "LDA", &NES::LDA, &NES::ABX, 4 });
    this->add_ins({ "LDX", &NES::LDX, &NES::ABY, 4 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 4 });
    this->add_ins({ "CPY", &NES::CPY, &NES::IMM, 2 });
    this->add_ins({ "CMP", &NES::CMP, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "CPY", &NES::CPY, &NES::ZP0, 3 });
    this->add_ins({ "CMP", &NES::CMP, &NES::ZP0, 3 });
    this->add_ins({ "DEC", &NES::DEC, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "INY", &NES::INY, &NES::IMP, 2 });
    this->add_ins({ "CMP", &NES::CMP, &NES::IMM, 2 });
    this->add_ins({ "DEX", &NES::DEX, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "CPY", &NES::CPY, &NES::ABS, 4 });
    this->add_ins({ "CMP", &NES::CMP, &NES::ABS, 4 });
    this->add_ins({ "DEC", &NES::DEC, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BNE", &NES::BNE, &NES::REL, 2 });
    this->add_ins({ "CMP", &NES::CMP, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "CMP", &NES::CMP, &NES::ZPX, 4 });
    this->add_ins({ "DEC", &NES::DEC, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "CLD", &NES::CLD, &NES::IMP, 2 });
    this->add_ins({ "CMP", &NES::CMP, &NES::ABY, 4 });
    this->add_ins({ "NOP", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "CMP", &NES::CMP, &NES::ABX, 4 });
    this->add_ins({ "DEC", &NES::DEC, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "CPX", &NES::CPX, &NES::IMM, 2 });
    this->add_ins({ "SBC", &NES::SBC, &NES::IZX, 6 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "CPX", &NES::CPX, &NES::ZP0, 3 });
    this->add_ins({ "SBC", &NES::SBC, &NES::ZP0, 3 });
    this->add_ins({ "INC", &NES::INC, &NES::ZP0, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 5 });
    this->add_ins({ "INX", &NES::INX, &NES::IMP, 2 });
    this->add_ins({ "SBC", &NES::SBC, &NES::IMM, 2 });
    this->add_ins({ "NOP", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::SBC, &NES::IMP, 2 });
    this->add_ins({ "CPX", &NES::CPX, &NES::ABS, 4 });
    this->add_ins({ "SBC", &NES::SBC, &NES::ABS, 4 });
    this->add_ins({ "INC", &NES::INC, &NES::ABS, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "BEQ", &NES::BEQ, &NES::REL, 2 });
    this->add_ins({ "SBC", &NES::SBC, &NES::IZY, 5 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 8 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "SBC", &NES::SBC, &NES::ZPX, 4 });
    this->add_ins({ "INC", &NES::INC, &NES::ZPX, 6 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 6 });
    this->add_ins({ "SED", &NES::SED, &NES::IMP, 2 });
    this->add_ins({ "SBC", &NES::SBC, &NES::ABY, 4 });
    this->add_ins({ "NOP", &NES::NOP, &NES::IMP, 2 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
    this->add_ins({ "UDF", &NES::NOP, &NES::IMP, 4 });
    this->add_ins({ "SBC", &NES::SBC, &NES::ABX, 4 });
    this->add_ins({ "INC", &NES::INC, &NES::ABX, 7 });
    this->add_ins({ "UDF", &NES::UDF, &NES::IMP, 7 });
}

void Nes6502::add_ins(INSTRUCTION ins)
{
    this->lookup[this->temp] = ins;
    this-temp++;
}

void Nes6502::clock()
{

    if(this->cycles == 0)
    {
        //Read the next instruction
        this->opcode = read(this->PC);

        // Always set the unused status flag bit to 1
		this->SetFlag(U, true);
		
		// Increment program counter, we read the opcode byte
		this->PC++;

		// Get Starting number of cycles
		this->cycles = this->lookup[opcode].cycles;

		// Perform fetch of intermmediate data using the
		// required addressing mode
		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();

		// Perform operation
		uint8_t additional_cycle2 = (this->*lookup[opcode].operation)();

		// The addressmode and opcode may have altered the number
		// of cycles this instruction requires before its completed
		this->cycles += (additional_cycle1 & additional_cycle2);

		// Always set the unused status flag bit to 1
		this->SetFlag(U, true);

    }


	// Decrement the number of cycles remaining for this instruction
	this->cycles--;
}

//Nes Cpu Reset
void Nes6502::reset()
{
    // Get address to set program counter to
	this->addr_abs = 0xFFFC;
	uint16_t lo = read(this->addr_abs + 0);
	uint16_t hi = read(this->addr_abs + 1);

	// Set it
	this->PC = (hi << 8) | lo;

	// Reset internal registers
	this->A = 0;
	this->X = 0;
	this->Y = 0;
	this->SP = 0xFD;
	this->P = 0x00 | U;

	// Clear internal helper variables
	this->addr_rel = 0x0000;
	this->addr_abs = 0x0000;
	this->fetched = 0x00;

	// Reset takes time
	this->cycles = 8;
}

//Interrupt Request
void Nes6502::irq()
{
    //If irq bit is not set meaning irq is not disabled
    if(this->GetFlag(I) == 0)
    {
        // Push the program counter to the stack. It's 16-bits dont
		// forget so that takes two pushes
		this->write(this->stackBase + this->SP, (this->PC >> 8) & 0x00FF);
		this->SP--;
		write(this->stackBase + this->SP, this->PC & 0x00FF);
		this->SP--;

		// Then Push the status register to the stack
		this->SetFlag(B, 0);
		this->SetFlag(U, 1);
		this->SetFlag(I, 1);
		this->write(this->stackBase + this->SP, this->P);
		this->SP--;

		// Read new program counter location from fixed address
		this->addr_abs = 0xFFFE;
		uint16_t lo = this->read(this->addr_abs + 0);
		uint16_t hi = this->read(this->addr_abs + 1);
		this->PC = (hi << 8) | lo;

		// IRQs take time
		cycles = 7;
    }
}

//Non Maskable IRQ
void Nes6502::nmirq()
{
    this->write(this->stackBase + this->SP, (this->PC >> 8) & 0x00FF);
	this->SP--;
	this->write(this->stackBase + this->SP, this->PC & 0x00FF);
	this->SP--;

	this->SetFlag(B, 0);
	this->SetFlag(U, 1);
	this->SetFlag(I, 1);
	this->write(this->stackBase + this->SP, this->P);
	this->SP--;

	this->addr_abs = 0xFFFA;
	uint16_t lo = this->read(this->addr_abs + 0);
	uint16_t hi = this->read(this->addr_abs + 1);
	this->PC = (hi << 8) | lo;

	cycles = 8;
}

void Nes6502::connect_bus(NesBus* bus)
{
    this->nes_bus = bus;
}

bool Nes6502::ins_complete()
{
    return this->cycles == 0;
}

void Nes6502::SetFlag(PFlags flag, bool clear)
{
    if(clear)
    {
        this->P = this->P |= flag;
    }
    else
    {
        this->P = this->P &= flag;
    }
    
}

bool Nes6502::GetFlag(PFlags flag)
{
    uint8_t flagVal = this->P & flag;
    if(flagVal & 0xFF)
    {
        return true;
    }

    return false;;
}

void Nes6502::write(uint16_t addr, uint8_t data)
{
    this->nes_bus->write(addr,data);
}

uint8_t Nes6502::read(uint16_t addr)
{
    return this->nes_bus->read(addr, false);
}

uint8_t Nes6502::fetch()
{
    if(!(this->lookup[this->opcode].addrmode == &Nes6502::IMP))
    {
        this->fetched = this->read(addr_abs);
    }
    
    return fetched;
}


//Addresing Mode Implemntations

//Addressing Mode Implied
uint8_t Nes6502::IMP()
{
    this->fetched = A;
    return 0;
}

//Addressing Mode Immediate
//This addressing mode expects the next byte to be a value, so we set the read address to the point where the next byte is in the program
uint8_t Nes6502::IMM()
{
    this->addr_abs = this->PC++;
    return 0;
}

//Addressing Mode Zero Page
//Zero page addressing is used to save space for program bytes as such it only uses the fist Bytes of an address range
uint8_t Nes6502::ZP0()
{
    //Read the bytes at the current PC
    this->addr_abs = read(this->PC);
    //Increment the program counter
    this->PC++;
    //Mask off the bits needed
    this->addr_abs &= 0x00FF;
}

//Addressing Mode Zero Page with offset X
uint8_t Nes6502::ZPX()
{
    this->addr_abs = this->read(this->PC + this->X);
    this->PC++;
    this->addr_abs &= 0xFF;
}

//Addressing Mode Zero Page with offset Y
uint8_t Nes6502::ZPY()
{
    this->addr_abs = this->read(this->PC + this->Y);
    this->PC++;
    this->addr_abs &= 0xFF;
}

//Addressing Mode Relative
//Used only for branching instructions, 
uint8_t Nes6502::REL()
{
    this->addr_rel = this->read(this->PC);
    this->PC++;

    if(this->addr_rel & 0x80)
    {
        this->addr_rel |= 0xFF00; //Set signed bit
    }

    return 0;
}

//Addressing mode Absolute, uses a full 16 bits for the address
uint8_t Nes6502::ABS()
{
    uint16_t loaddr = this->read(this->PC);
    this->PC++;
    uint16_t hiaddr = this->read(this->PC);
    this->PC++;

    this->addr_abs = ((hiaddr << 8) | loaddr);

    return 0;
}

//Addressing Mode Absolute plus X offset
uint8_t Nes6502::ABX()
{

    uint16_t loaddr = this->read(this->PC);
    this->PC++;
    uint16_t hiaddr = this->read(this->PC);
    this->PC++;

    this->addr_abs = ((hiaddr << 8) | loaddr);
    this->addr_abs += this->X;
    
    if ((addr_abs & 0xFF00) != (hiaddr << 8))
		return 1; //Additional clock cycle if the the page boundary is cross
	else
		return 0;	
}

//Addressing Mode Absolute plus Y offset
uint8_t Nes6502::ABY()
{

    uint16_t loaddr = this->read(this->PC);
    this->PC++;
    uint16_t hiaddr = this->read(this->PC);
    this->PC++;

    this->addr_abs = ((hiaddr << 8) | loaddr);
    this->addr_abs += this->Y;
    
    if ((addr_abs & 0xFF00) != (hiaddr << 8))
		return 1; //Additional clock cycle if the the page boundary is cross
	else
		return 0;	
}

//Addressing Mode Indirect
uint8_t Nes6502::IND()
{
    uint16_t lo = this->read(this->PC);
    this->PC++;
    uint16_t hi = this->read(this->PC);
    this->PC++;

    uint16_t ptr = (hi << 8) | lo;

    if (lo == 0x00FF) //Simulates page boundary hardware bug
	{
		this->addr_abs = (this->read(ptr & 0xFF00) << 8) | this->read(ptr + 0);
	}
	else // Behave normally
	{
		this->addr_abs = (this->read(ptr + 1) << 8) | this->read(ptr + 0);
	}

    return 0;
}

uint8_t Nes6502::IZX()
{
    uint16_t val = this->read(this->PC);
    this->PC++;

    uint16_t lo = this->read((uint16_t)(val + (uint16_t)this->X) & 0x00FF);
    uint16_t hi = this->read((uint16_t)(val + (uint16_t)this->X + 1) * 0x00FF);

    this->addr_abs = (hi << 8) | lo;

    return 0;
}

//Addressing Mode Inderct X
uint8_t Nes6502::IZY()
{
    uint16_t val = this->read(this->PC);
    this->PC++;

    uint16_t lo = this->read(val & 0x00FF);
    uint16_t hi = this->read(val + 1 & 0x00FF);

    addr_abs = (hi << 8) | lo;
    addr_abs += this->Y;

    if((this->addr_abs & 0xFF00) != (hi << 8))
    {
        return 1; //Add an extra cycle for crossing a page boundary
    }
    else
    {
        return 0;
    }
    
}

//Instruction Implmentations

//Break Instruction, Soft IRQ
uint8_t Nes6502::BRK()
{
    this->PC++;
    this->SetFlag(PFlags::I, true);
    //Push the current PC onto the nes stack, this is done with 2 writes because the PC is 16 bits wide
    this->write(this->stackBase + this->SP, ((this->PC >> 8) & 0x00FF));
    this->SP--;
    this->write(this->stackBase + this->SP, this->PC & 0x00FF);
    this->SP--;

    //Set the break Flag
    this->SetFlag(PFlags::B, true);
    //Write the status registers onto the stack
    this->write(this->stackBase + this->SP, this->P);
    this->SP--;

    //Clear the break flag
    this->SetFlag(PFlags::B, false);

    //Set the PC to the jump address located at 0xFFFE and 0xFFFF
    this->PC = (uint16_t)this->read(0xFFFE) | ((uint16_t)this->read(0xFFFF) << 8);
    
    //Return zero as no additional cpu cycles are required for the operation
    return 0;
}


//Add with carry bit
uint8_t Nes6502::ADC()
{

    this->fetch();

    uint16_t val = (uint16_t)this->A + (uint16_t)this->fetched + (uint16_t)this->GetFlag(C);
    
    this->SetFlag(C, val > 255); //Update Carry Flag
    this->SetFlag(Z, val = 0x00); //Update Zero flag

    //Update over flow flag V = ~(A^M) & (A^R) Thanks to One Lone Coder for this one
    this->SetFlag(V, (~(uint16_t)this->A ^ (uint16_t)this->fetched & ((uint16_t)this->A ^ val)) & 0x0080);

    this->SetFlag(N, val & 0x80); //Update Negative Flag

    this->A = val & 0x00FF;

    return 1; //TODO Figure out when this needs to have an extra cycle and when it does not
}


//Subtrace with borrow bit
uint8_t Nes6502::SBC()
{

    this->fetch();

    //Get the fetched data and invert the value with an XOR operation
    uint16_t val = ((uint16_t)this->fetched) ^ 0x00FF;
    uint16_t temp = (uint16_t)this->A + val + (uint16_t)this->GetFlag(C);
    this->SetFlag(C, temp & 0xFF00);
    this->SetFlag(Z, (temp & 0x00FF) == 0x0);
    this->SetFlag(V, (temp ^ (uint16_t)this->A) & (temp ^ val) & 0x0080);
    this->SetFlag(N, temp & 0x80);
    this->A = temp * 0x0FF;

    return 1;   //TODO Figure out when this does and does not need an additional cycle
}

//Bitwise an Operation
uint8_t Nes6502::AND()
{
    fetch();
    this->A = this->A & this->fetched;
    this->SetFlag(Z, this->A == 0x00);
    this->SetFlag(N, this->A & 0x80);

    //TODO Figure out how to determine exactly how many cycles are and are not needed since not all AND instructions require additional cycles
    return 1;
}

//Bitewise Arthimitc shift left
uint8_t Nes6502::ASL()
{
    this->fetch();

    uint16_t val = (uint16_t)this->fetched << 1;
    this->SetFlag(Z, (val & 0xFF) == 0x0 );
    this->SetFlag(N, val & 0x80);
    this->SetFlag(C, (val & 0xFF00) > 0);

    if(this->lookup[this->opcode].addrmode == &Nes6502::IMP)
    {
        this->A = temp & 0xFF;
    }
    else
    {
        this->write(this->addr_abs, val & 0xFF);
    }
    
    return 0;
}


//Branch on Carry Clear
uint8_t Nes6502::BCC()
{
    if(this->GetFlag(C) == 0x0)
    {
        cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }

        this->PC = addr_abs;
    }

    return 0;
}

//Branch on Carry SET
uint8_t Nes6502::BCS()
{
    if(this->GetFlag(C))
    {
        cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }

        this->PC = addr_abs;
    }

    return 0;
}

//Branch if Equal
uint8_t Nes6502::BEQ()
{
    if(this->GetFlag(Z))
    {
       cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Branch if Negative
uint8_t Nes6502::BMI()
{
    if(this->GetFlag(N))
    {
       cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Branch if NOT equal
uint8_t Nes6502::BNE()
{
    if(this->GetFlag(Z) == 0)
    {
       cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Branch on Positive
uint8_t Nes6502::BPL()
{
    if(this->GetFlag(N) == 0)
    {
     cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Branch on overflow clear
uint8_t Nes6502::BVC()
{
    if(this->GetFlag(V) == 0)
    {
        cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Branch on overflow set
uint8_t Nes6502::BVS()
{
    if(this->GetFlag(V))
    {
        cycles++;
        this->addr_abs = this->PC + this->addr_rel;

        //If the address crosses a page boundary add an extra cycle
        if((this->addr_abs & 0xFF00) != (this->PC & 0xFF00))
        {
            cycles++;
        }
        this->PC = addr_abs;
    }

    return 0;
}

//Clear Carry Flag
uint8_t Nes6502::CLC()
{
    this->SetFlag(C, false);
    return 0;
}

//Clear Decimal Flag
uint8_t Nes6502::CLD()
{
    this->SetFlag(D, false);
    return 0;
}

//Clear Irq Disable Bit
uint8_t Nes6502::CLI()
{
    this->SetFlag(I, false);
    return 0;
}

//Clear overflow Flag
uint8_t Nes6502::CLV()
{
    this->SetFlag(V, false);
    return 0;
}

//Compare Accumulator with Memory
uint8_t Nes6502::CMP()
{
    this->fetch();

    uint16_t val = (uint16_t)this->A - (uint16_t)this->fetched;
    this->SetFlag(C, this->A >= this->fetched);
	this->SetFlag(Z, (val & 0xFF) == 0x0);
	this->SetFlag(N, val & 0x80);

	return 1;
}

//Compare X Index with Memory
uint8_t Nes6502::CPX()
{
    this->fetch();

    uint16_t val = (uint16_t)this->X - (uint16_t)this->fetched;
    this->SetFlag(C, this->X >= this->fetched);
	this->SetFlag(Z, (val & 0xFF) == 0x0);
	this->SetFlag(N, val & 0x80);

	return 1;
}

//Compare Y Index with Memory
uint8_t Nes6502::CPY()
{
    this->fetch();

    uint16_t val = (uint16_t)this->Y - (uint16_t)this->fetched;
    this->SetFlag(C, this->Y >= this->fetched);
	this->SetFlag(Z, (val & 0xFF) == 0x0);
	this->SetFlag(N, val & 0x80);

	return 1;
}

//Decrement Memory
uint8_t Nes6502::DEC()
{
    this->fetch();

    uint16_t val = (uint16_t)this->fetched - 1;
    this->write(this->addr_abs, val & 0x00FF);
    this->SetFlag(Z, (val & 0x00FF) == 0x0);
    this->SetFlag(N, val & 0x80);

    return 0;
}


//Decrement X
uint8_t Nes6502::DEX()
{
    this->X--;
    this->SetFlag(N, this->X & 0x80);
    this->SetFlag(Z, (this->X & 0xFF) == 0x0);

    return 0;
}

//Decrement Y
uint8_t Nes6502::DEY()
{
    this->Y--;
    this->SetFlag(N, this->Y & 0x80);
    this->SetFlag(Z, (this->Y & 0xFF) == 0x0);

    return 0;
}

//Bitwise Exclusive Or of memory with Accumulator
uint8_t Nes6502::EOR()
{
    this->fetch();

    uint16_t val = this->fetched ^ this->A;
    this->SetFlag(Z, val == 0x0);
    this->SetFlag(N, val & 0x80);

    return 1;
}

//Increment Memory by one
uint8_t Nes6502::INC()
{
    this->fetch();
    uint16_t val = this->fetched + 1;
	this->write(this->addr_abs, val & 0xFF);
	this->SetFlag(Z, (val & 0xFF) == 0x0);
	this->SetFlag(N, val & 0x80);

	return 0;
}

//Increment X by one
uint8_t Nes6502::INX()
{
    this->fetch();
    this->X++;
	this->SetFlag(Z, (this->X & 0xFF) == 0x0);
	this->SetFlag(N, this->X & 0x80);

	return 0;
}

//Increment Y by one
uint8_t Nes6502::INY()
{
    this->fetch();
    this->Y++;
	this->SetFlag(Z, (this->Y & 0xFF) == 0x0);
	this->SetFlag(N, this->Y & 0x80);

	return 0;
}

//Jump to Address
uint8_t Nes6502::JMP()
{
    this->PC = this->addr_abs;
    return 0;
}

//Jump to sub routine
uint8_t Nes6502::JSR()
{
    this->PC--;

    //Save the return address first the hi half
    this->write(this->stackBase + this->SP, (this->PC >> 8) &  0xFF);
    this->SP--;
    this->write(this->stackBase + this->SP, this->PC & 0xFF);
    this->SP--;

    this->PC = this->addr_abs;
    return 0;
}

//Load to Accumulator
uint8_t Nes6502::LDA()
{
    this->fetch();
    this->A = this->fetched;
    this->SetFlag(Z, this->A == 0x0);
    this->SetFlag(N, this->A & 0x80);
    return 1;
}	

//Load to X Register
uint8_t Nes6502::LDX()
{
    this->fetch();
    this->X = this->fetched;
    this->SetFlag(Z, this->X == 0x0);
    this->SetFlag(N, this->X & 0x80);
    return 1;
}	

//Load to Y Register
uint8_t Nes6502::LDY()
{
    this->fetch();
    this->Y = this->fetched;
    this->SetFlag(Z, this->Y == 0x0);
    this->SetFlag(N, this->Y & 0x80);
    return 1;
}

//Bit shift Right
uint8_t Nes6502::LSR()
{
    this->fetch();
	this->SetFlag(C, this->fetched & 0x0001);
	uint16_t temp = this->fetched >> 1;	
	this->SetFlag(Z, (temp & 0x00FF) == 0x0000);
	this->SetFlag(N, temp & 0x0080);
	if (this->lookup[opcode].addrmode == &Nes6502::IMP)
    {
		this->A = temp & 0x00FF;
    }
	else
    {
		this->write(this->addr_abs, temp & 0x00FF);
    }

	return 0;
}	

//No operation Ins = Pulled from One Lone Coder source
uint8_t Nes6502::NOP()
{
// Sadly not all NOPs are equal, Ive added a few here
	// based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
	// and will add more based on game compatibility, and ultimately
	// I'd like to cover all illegal opcodes too
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}	

//Bitwise OR of Accumulator with value
uint8_t Nes6502::ORA()
{
    this->fetch();
    this->A = this->A | this->fetched;
    this->SetFlag(Z, this->A == 0x0);
    this->SetFlag(N, this->A & 0x80);
    return 1;
}	

//Push Accumulator to stack
uint8_t Nes6502::PHA()
{
    this->write(this->stackBase + this->SP, this->A);
    this->SP--;
    return 0;
}

//Push CPU Status onto Stack
uint8_t Nes6502::PHP()
{
    this->write(this->stackBase + this->SP, this->P);
    this->SP--;
    this->SetFlag(B, 0);
    this->SetFlag(U, 0);
    return 0;
}	

//Pull Accumulator from Stack
uint8_t Nes6502::PLA()
{
    this->SP++;
    this->A = this->read(this->stackBase + this->SP);
    this->SetFlag(Z, this->A == 0x0);
    this->SetFlag(N, this->A & 0x80);
    return 0;
}

//Pull Cpu Status from Stack
uint8_t Nes6502::PLP()
{
    this->SP++;
    this->P = this->read(this->stackBase + this->SP);
    this->SetFlag(U, 1);
    return 0;
}	

//Rotate one bit left
uint8_t Nes6502::ROL()
{
	this->fetch();
	uint16_t temp = (uint16_t)(this->fetched << 1) | this->GetFlag(C);
	this->SetFlag(C, temp & 0xFF00);
	this->SetFlag(Z, (temp & 0x00FF) == 0x0000);
	this->SetFlag(N, temp & 0x0080);
	if (this->lookup[opcode].addrmode == &Nes6502::IMP)
    {
		this->A = temp & 0x00FF;
    }
	else
    {
		this->write(this->addr_abs, temp & 0x00FF);
    }

	return 0;
}

//Rotate one bit right
uint8_t Nes6502::ROR()
{
    this->fetch();
	uint16_t temp = (uint16_t)(this->GetFlag(C) << 7) | (this->fetched >> 1);
	this->SetFlag(C, this->fetched & 0x01);
	this->SetFlag(Z, (temp & 0x00FF) == 0x00);
	this->SetFlag(N, temp & 0x0080);
	if (this->lookup[opcode].addrmode == &Nes6502::IMP)
    {
		this->A = temp & 0x00FF;
    }
	else
    {
		write(addr_abs, temp & 0x00FF);
    }

	return 0;
}	

//Return from IRQ
uint8_t Nes6502::RTI()
{
    this->SP++;
    this->P = this->read(this->stackBase + this->SP);

    this->SetFlag(B, ~B);
    this->SetFlag(U, ~U);

    this->SP++;
    this->PC = (uint16_t)this->read(this->stackBase + this->SP);
    this->SP++;
    this->PC |= (uint16_t)this->read(this->stackBase + this->SP) << 8;
    return 0;
}	

//Return from Sub Routine
//pull PC, PC+1 -> PC 
uint8_t Nes6502::RTS()
{
    this->SP++;
    this->PC = this->read(this->stackBase + this->SP);
    this->SP++;
    this->PC |= this->read(this->stackBase + this->SP) << 8;
    this->PC++;

    return 0;
}	

//Set Carry Flag
uint8_t Nes6502::SEC()
{
    this->SetFlag(C, 1);
    return 0;
}	

//Set Decimal Flag
uint8_t Nes6502::SED()
{
    this->SetFlag(D, 1);
    return 0;
}	

//Set IRQ Disable Flag
uint8_t Nes6502::SEI()
{
    this->SetFlag(I,1);
    return 0;
}	

//Store Accumulator in memory
uint8_t Nes6502::STA()
{
    this->write(this->addr_abs, this->A);
    return 0;
}

//Store X in memory
uint8_t Nes6502::STX()
{
    this->write(this->addr_abs, this->X);
    return 0;
}	

//Store Y in memory
uint8_t Nes6502::STY()
{
    this->write(this->addr_abs, this->Y);
    return 0;
}	

//Transfer Accumulator to X index
uint8_t Nes6502::TAX()
{
    this->X = this->A;
    this->SetFlag(N, this->X == 0x0);
    this->SetFlag(Z, this->X & 0x80);

    return 0;
}	

//Transfer Accumulator to Y index
uint8_t Nes6502::TAY()
{
    this->Y = this->A;
    this->SetFlag(Z, this->Y == 0x0);
    this->SetFlag(N, this->Y & 0x80);

    return 0;
}

//Transfer Stack Pointer to X
uint8_t Nes6502::TSX()
{
    this->X = this->SP;
    this->SetFlag(Z, this->X == 0x0);
    this->SetFlag(N, this->X & 0x80);

    return 0;
}	

//Transfer X register to accumulator
uint8_t Nes6502::TXA()
{
    this->A = this->X;
    this->SetFlag(Z, this->A == 0x0);
    this->SetFlag(N, this->A & 0x80);

    return 0;
}	

//Transfer X Register to stack register
uint8_t Nes6502::TXS()
{
    this->SP = this->X;
    return 0;
}	

//Transfer Y Register to Accumulator
uint8_t Nes6502::TYA()
{
    this->A = this->Y;
    this->SetFlag(Z, this->A == 0x0);
    this->SetFlag(N, this->A & 0x80);

    return 0;
}

//Bit Tst 
uint8_t Nes6502::BIT()
{
    this->fetch();

    uint8_t val = this->A & this->fetched;
    this->SetFlag(Z, (val == 0));
    this->SetFlag(N, (this->fetched & ( 1 << 7)));
    this->SetFlag(V, (this->fetched & ( 1 << 6)));

    return 0;
}
