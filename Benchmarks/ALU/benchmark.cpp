#include "benchmark.h"
// Constructeur avec assignation des attributs
Benchmark::Benchmark()
{

	serial_t_::init();
	D1::output();
	D2::output();
	D3::output();
	D4::output();
	D5::output();
	D6::output();
	D7::output();
	
	A1::input();
	A2::input();
	A3::input();
	A4::input();
	A5::input();
}


////////////////////////////// PROTOCOLE SERIE ///////////////////////////////////

void Benchmark::communiquer_pc(){
	char buffer[17];
	serial_t_::read(buffer);

	//ping
	if(strcmp(buffer,"?") == 0)
	{
		serial_t_::printf("Test_alu");
	}
	
	
}

void Benchmark::test_incr_1001(){
	serial_t_::printf("Test_incr_1001");
	overflow::high();
	ign_overflow::low();
	NOT::low();
	INC::high();
	for (int i = 0; i < 8; i++) {
		if (i%2) 001::high() else 001::low();
		if ((i/2)%2) 010::high() else 010::low();
		if ((i/4)%2) 100::high() else 100::low();
		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
		if((001_out::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
			serial_t_::printf("\033[31Probleme : incrementation avec input = %d, et config = 1001",i);
		} else if ((overflow_out::read()) != (i == 7)) {
			serial_t_::printf("\033[31Probleme : flag overflow à 0 avec input = 7, et config = 1001");
		} else {
			serial_t_::printf("\033[30Incrementation avec input %d, et config = 1001			OK", i);
		}
	}
}

void Benchmark::test_incr_0101(){
	serial_t_::printf("Test_incr_0101");
	overflow::low();
	ign_overflow::high();
	NOT::low();
	INC::high();
	for (int i = 0; i < 8; i++) {
		if (i%2) 001::high() else 001::low();
		if ((i/2)%2) 010::high() else 010::low();
		if ((i/4)%2) 100::high() else 100::low();
		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
		if((001_out::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
			serial_t_::printf("\033[31Probleme : incrementation avec input = %d, et config = 0101",i);
		} else if ((overflow_out::read()) != (i == 7)) {
			serial_t_::printf("\033[31Probleme : flag overflow à 0 avec input = 7, et config = 0101");
		} else {
			serial_t_::printf("\033[30Incrementation avec input %d, et config = 0101			OK", i);
		}
	}
}

void Benchmark::test_incr_1101(){
	serial_t_::printf("Test_incr_1101");
	overflow::high();
	ign_overflow::high();
	NOT::low();
	INC::high();
	for (int i = 0; i < 8; i++) {
		if (i%2) 001::high() else 001::low();
		if ((i/2)%2) 010::high() else 010::low();
		if ((i/4)%2) 100::high() else 100::low();
		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
		if((001_out::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
			serial_t_::printf("\033[31Probleme : incrementation avec input = %d, et config = 1101",i);
		} else if ((overflow_out::read()) != (i == 7)) {
			serial_t_::printf("\033[31Probleme : flag overflow à 0 avec input = %d, et config = 1101", i);
		} else {
			serial_t_::printf("\033[30Incrementation avec input %d, et config = 1101			OK", i);
		}
	}
}

void Benchmark::test_rien_0001(){
	serial_t_::printf("Test_rien_1001");
	overflow::low();
	ign_overflow::low();
	NOT::low();
	INC::high();
	for (int i = 0; i < 8; i++) {
		if (i%2) 001::high() else 001::low();
		if ((i/2)%2) 010::high() else 010::low();
		if ((i/4)%2) 100::high() else 100::low();
		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
		if((001_out::read()) + ((010_out::read())*2) + ((100_out::read())*4) != i) {
			serial_t_::printf("\033[31Probleme : rien avec input = %d, et config = 0001",i);
		} else if (overflow_out::read()) {
			serial_t_::printf("\033[31Probleme : flag overflow à 1 avec config = 0001");
		} else {
			serial_t_::printf("\033[30Rien avec input %d, et config = 0001			OK", i);
		}
	}
}
void Benchmark::test_zero(){
	serial_t_::printf("Test_zero_flag");
	001::low();
	010::low();
	100::low();
	for (int i = 0; i < 16; i++) {
		if (i%2) overflow::high() else overflow::low();
		if ((i/2)%2) ign_overflow::high() else ign_overflow::low();
		if ((i/4)%2) NOT::high() else NOT::low();
		if ((i/8)%2) INC::high() else INC::low()
		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
		if( zero_out::read() != 1 ) {
			serial_t_::printf("\033[31Probleme : zero flag à 0 avec input = 0 et config = %d", i); //convertisseur en binaire à faire, mais là flemme
		} else {
			serial_t_::printf("\033[30Zero flag                                                OK"); //convertisseur en binaire à faire, mais là flemme
		}
	}
}
