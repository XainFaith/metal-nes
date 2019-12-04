#include <pl181.hpp>
#include <stdio.h>

//Bit wise shift operators for clarity
#define EXE (1 << 10)
#define RESP (1 << 6)
#define LRESP (RESP & ( 1 << 7 ))

#define HCS (1 << 30)

Pl181 pl181;

void Pl181::Initalize(uint32_t baseAddr)
{
    this->registers = (volatile Registers*)baseAddr;
    this->dataFIFO = (DataFIFO*)(baseAddr + 0x080);

    printf("Initalizing PL181\n");
    //TODO Figure out how to properly initalize the pl181 on real hardware since qemu does a half job emulating it

    this->registers->Clock = 0x1C6;
    this->registers->Power = 0x86;
    
    this->init_sd();
}

bool Pl181::init_sd()
{

    printf("Initalizing SD Card\n");

    //Send cmd 0 to set all cards into idle state
    this->send_cmd(0 | EXE | RESP);

    this->registers->Arg = 0x1AA;
    this->send_cmd(8 | EXE | RESP);

    printf("cmd 8 resp: 0x%h \n", this->registers->Response[0]);
    this->clear_flags();

    this->send_cmd(55 | EXE | RESP);
    printf("cmd 55 resp: 0x%h \n", this->registers->Response[0]);
    this->clear_flags();
   
    return true;
}

void Pl181::clear_flags()
{
    this->registers->Clear = 0x5FF;
}

void Pl181::send_cmd(volatile uint32_t arg)
{
    //Wait until the cmd line is not active
    while((this->registers->Status & (1 << 11) != (1 << 11)))
    {}

    this->registers->Cmd = arg;

    while(this->registers->Status & ( 1 << 11)){}

    if(arg & RESP)
    {
        //If the command requested a response wait for a response
        while((this->registers->Status & 0x40) != 0x40 || this->registers->Status & ( 1 << 11))
        {
            if(this->registers->Status & (1 << 2))
            {
                printf("Status of post cmd sent: 0x%h \n", this->registers->Status);
                return;
            }
        }

        
    }
    else 
    {
        while((this->registers->Status & (1 << 7)) != (1 << 7))
        {
        }
    }    

    printf("Status of post cmd sent: 0x%h \n", this->registers->Status);
}

bool Pl181::send_app_cmd(uint32_t arg)
{
    uint32_t count = 0;
    while(count != 65000)
    {
        this->send_cmd(55 | EXE | RESP);
        if(this->registers->Response[0] == 0x0)
        {
            printf("App cmd Sent \n");
            this->send_cmd(arg);
            return true;
        }
        count++;
    }

    printf("Failed to send app command \n");

    return false;
}

void Pl181::set_arg(uint32_t arg)
{
    this->registers->Arg = arg;
}

int Pl181::read_block(void * buffer, uint32_t addr)
{
    return 0;
}

int Pl181::write_block(void * buffer, uint32_t addr)
{
    return 0;
}

uint32_t Pl181::get_blk_count()
{
    return 0;
}

void Pl181::clear_resp_registers()
{
    this->registers->Response[0] = 0;
    this->registers->Response[1] = 0;
    this->registers->Response[2] = 0;
    this->registers->Response[3] = 0;
}
