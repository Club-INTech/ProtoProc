/** \file benchmark.h
 *  \author Dede
 *  \brief l'include correspondant au vrai code
 * 
 */

#ifndef benchmark_h
#define benchmark_h

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <libintech/uart.hpp>
#include <libintech/gpio.hpp>
#include <libintech/singleton.hpp>

#define INPUT_SIZE 7
#define OUTPUT_SIZE 5
#define POSSIBLE_INPUTS 128
#define PROCESSOR_DELAY 10000	//le délai entre deux utilisations de l'ALU, en microsecondes

#define overflow input[0]
#define ign_overflow input[1]
#define NOT input[2]
#define INC input[3]
#define i001 input[4]
#define i010 input[5]
#define i100 input[6]

#define overflow_out output[0]
#define zero_out output[1]
#define o001 output[2]
#define o010 output[3]
#define o100 output[4]

#define AND(X,Y) ((X && Y) ? 1 : 0)
#define OR(X,Y) ((X || Y) ? 1 : 0)
#define NAND(X,Y) (AND(X,Y)? 0 : 1)
#define NOR(X,Y) (OR(X,Y)? 0 : 1)
#define XOR(X,Y) (X != Y)
#define NO(X) (X ? 0 : 1)
#define 3-OR(X,Y,Z) (OR(X,OR(Y,Z)))

class Benchmark : public Singleton<Benchmark>{
// Par dÃ©faut les attributs sont publics dans une struct


private:
	
    typedef uart0 serial_t_;
    uint8_t input[INPUT_SIZE];
    uint8_t output[OUTPUT_SIZE];
    uint8_t actual_output[OUTPUT_SIZE]; 
    uint8_t incr[3];
    uint8_t decr[3];
    uint8_t retenue_in_incr;
    uint8_t retenue_in_decr;
    uint8_t retenue_out_incr;
    uint8_t retenue_out_decr;
    uint8_t flag_incr;
    uint8_t flag_decr;
    uint8_t flag_not;
    uint8_t onot;
    
    void alu_test();
    void alu_logic();
    void incr_logic();
    void decr_logic();
    void alu_once(const unsigned int number);
    void fill_input(const unsigned int number);
    void apply_input();
    void read_output();
    void compare_outputs();
    const char* get_input();
    const char* get_output();
    const char* get_actual_output();
    unsigned int twopow(unsigned int pow);
    unsigned int string_to_uint(const char* buffer);
    
public:
    
    Benchmark();
    
    //gestion des mesures courantes
 
    void communiquer_pc();

};

#endif
