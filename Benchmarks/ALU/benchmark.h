#ifndef benchmark_h
#define benchmark_h

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include <libintech/uart.hpp>
#include <libintech/gpio.hpp>
#include <libintech/singleton.hpp>

#define overflow D1
#define ign_overflow D2
#define NOT D3
#define INC D4
#define 001 D5
#define 010 D6
#define 100 D7

#define overflow_out A1
#define zero_out A2
#define 001_out A3
#define 010_out A4
#define 100_out A5

class Benchmark : public Singleton<Benchmark>{
// Par défaut les attributs sont publics dans une struct


private:

    typedef uart0 serial_t_;
    
public:
    
    Benchmark();
    
    //gestion des mesures courantes
 
    void communiquer_pc();

};

#endif
