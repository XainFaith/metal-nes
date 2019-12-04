#ifndef PL181_HPP
#define PL181_HPP

#include <stdint.h>
#include <blockdevice.hpp>

class Pl181 : public BlockDevice
{
    public:
    void Initalize(uint32_t baseAddr);
    int read_block(void * buffer, uint32_t addr);
    int write_block(void * buffer, uint32_t addr);
    uint32_t get_blk_count();

    private:

    bool init_sd();
    void clear_flags();
    void send_cmd(volatile uint32_t arg);
    bool send_app_cmd(volatile uint32_t arg);
    void set_arg(uint32_t arg);
    uint32_t read_response(uint32_t targ); 
    int push_data(void * buffer);
    int pop_data(void * buffer);

    void clear_resp_registers();

    struct Registers
    {
        uint32_t Power;
        uint32_t Clock;
        uint32_t Arg;
        uint32_t Cmd;
        uint32_t RespCmd;
        uint32_t Response[4];
        uint32_t DataTimer;
        uint32_t DataLength;
        uint32_t DataCtrl;
        uint32_t DataCnt;
        uint32_t Status;
        uint32_t Clear;
        uint32_t IntMask[2];
        uint32_t IntSelect;
        uint32_t FifoCnt;
    };

    struct DataFIFO
    {
        uint32_t Register[3];
    };

    volatile Registers * registers;
    DataFIFO * dataFIFO;

};

extern Pl181 pl181;

#endif
