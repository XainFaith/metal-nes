#ifndef NES_6502_HPP
#define NES_6502_HPP

#include <stdint.h>

class NesBus;

class Nes6502
{
public:

Nes6502();

enum PFlags
{
    C = ( 1 << 0),
    Z = ( 1 << 1),
    I = ( 1 << 2),
    D = ( 1 << 3),
    B = ( 1 << 4),
    U = ( 1 << 5),
    V = ( 1 << 6),
    N = ( 1 << 7)
};

//6502 Registers
uint8_t A, X, Y, P, SP;
//6502 Program Counter
uint16_t PC;

uint8_t stackBase;

void SetFlag(PFlags flag, bool v);
bool GetFlag(PFlags flag);


void clock();

void reset();

void irq();

void nmirq();

void connect_bus(NesBus* bus);

bool ins_complete();

private:

//Connection to the Main Bus
NesBus * nes_bus;

void write(uint16_t addr, uint8_t data);
uint8_t read(uint16_t addr);
uint8_t fetch();


// Assisstive variables to facilitate emulation
uint8_t  fetched     = 0x00;   // Represents the working input value to the ALU
uint16_t temp        = 0x0000; // A convenience variable used everywhere
uint16_t addr_abs    = 0x0000; // All used memory addresses end up in here
uint16_t addr_rel    = 0x00;   // Represents absolute address following a branch
uint8_t  opcode      = 0x00;   // Is the instruction byte
uint8_t  cycles      = 0;	   // Counts how many cycles the instruction has remaining
uint32_t clock_count = 0;	   // A global accumulation of the number of clocks

//Instruction Set and Addressing Mode stuff below
struct INSTRUCTION
{
    char * name;
    uint8_t (Nes6502::*operation)(void) = nullptr;
    uint8_t (Nes6502::*addrmode)(void) = nullptr;
    uint8_t cycles= 0;
};

INSTRUCTION * lookup;

void add_ins(INSTRUCTION ins);

//Instruction Definitions
uint8_t UDF(); //Undefined instruction catch all

uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

//Addressing Mode Definitions
uint8_t IMP();	uint8_t IMM();	
uint8_t ZP0();	uint8_t ZPX();	
uint8_t ZPY();	uint8_t REL();
uint8_t ABS();	uint8_t ABX();	
uint8_t ABY();	uint8_t IND();	
uint8_t IZX();	uint8_t IZY();

};

#endif
