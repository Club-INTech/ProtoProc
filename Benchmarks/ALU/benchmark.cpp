/** \file banchmark.cpp
 * \author Dede
 * \brief Ah, on m'informe qu'en vrai, c'est plutôt ça le coeur du code.
 */

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

	if(strcmp(buffer,"?") == 0)	{	//Nom du prog
		serial_t_::printf("Test_alu");
	} else if (strcmp(buffer, "test") == 0) {	// Test intégral
		alu_test();
	} else if (strcmp(buffer, "in") == 0) {		// Test sur un input spécifique
		serial_t_::read(buffer);
		alu_once(string_to_uint(buffer));
	}
}

void Benchmark::alu_test() { //le test de l'ALU
	unsigned int i;
	for (i = 0; i < 128; i++) {
		alu_once(i);		
	}
}

void Benchmark::alu_logic() {	// Cette méthode fait passer virtuellement le tableau d'input dans un circuit logique émulé, et remplit le tableau des outputs
	
	retenue_in_incr = OR(overflow, ign_overflow);
	retenue_in_decr = NOR(overflow, ign_overflow);
	flag_incr = AND(INC, NAND(retenue_in_incr, NOT));
	flag_not = AND(NOT, retenue_in_incr);
	flag_decr = NOR(INC, flag_not);
	onot = XOR(AND(NOT, ign_overflow), i001);
	incr_logic();
	decr_logic();
	overflow_out = OR(AND(flag_incr, retenue_out_incr), AND(flag_decr, retenue_out_decr));
	zero_out = NOR(OR(i001, i010), i100);
	o001 = 3-OR(AND(flag_incr, incr[0]), AND(flag_decr, decr[0]), AND(flag_not, onot));
	o010 = 3-OR(AND(flag_incr, incr[1]), AND(flag_decr, decr[1]), AND(flag_not, i010));
	o100 = 3-OR(AND(flag_incr, incr[2]), AND(flag_decr, decr[2]), AND(flag_not, i100));
	
}

void Benchmark::incr_logic() { //Cette méthode est le pendant logique du circuit d'incrémentation
	
	incr[0] = XOR(retenue_in_incr, i001);
	incr[1] = XOR(AND(retenue_in_incr, i001), i010);
	incr[2] = XOR(AND(AND(retenue_in_incr, i001), i010), i100);
	retenue_out_incr = AND( AND( AND(retenue_in_incr, i001), i010 ) , i100) ;
	
}

void Benchmark::decr_logic() { //Cette méthode est le pendant logique du circuit d'incrémentation
	
	decr[0] = NO(XOR(retenue_in_decr, i001));
	decr[1] = NO(XOR(OR(retenue_in_decr, i001), i010));
	decr[2] = NO(XOR(OR(OR(retenue_in_decr, i001), i010), i100));
	retenue_out_decr = NOR(OR(retenue_in_decr, i001), OR(i010, i100));
	
}

void Benchmark::alu_once(const unsigned int number) {		// Utilisation pour un input bien précis de l'ALU
	fill_input(number);
	apply_input();
	alu_logic();
	_delay_us(PROCESSOR_DELAY);		//on attend un temps suffisant pour que les outputs de l'ALU correspondent à sa réponse aux inputs mis ci-dessus
	read_output();
	compare_outputs();
}

void Benchmark::fill_input( const unsigned int number) {	//Cette méthode remplit le tableau d'input à partir d'un entier
	overflow = (number % 2);
	ign_overflow = ((number/2) % 2);
	NOT = ((number/4) % 2);
	INC = ((number/8) % 2);
	i001 = ((number/16) % 2);
	i010 = ((number/32) % 2);
	i100 = ((number/64) % 2);
}
void Benchmark::apply_input() {	//Cette méthode configure les pins du port D pour que l'ALU physique reçoive des données
	if (overflow) {D1::high()} else D1::low();
	if (ign_overflow) {D2::high()} else D2::low();
	if (NOT) {D3::high()} else D3::low();
	if (INC) {D4::high()} else D4::low();
	if (i001) {D5::high()} else D5::low();
	if (i010) {D6::high()} else D6::low();
	if (i100) {D7::high()} else D7::low();
}

void Benchmark::read_output() {	//Cette méthode lit les pins du port A pour voir la sortie de l'ALU physique 
	actual_output[0] = A1::read();
	actual_output[1] = A2::read();
	actual_output[2] = A3::read();
	actual_output[3] = A4::read();
	actual_output[4] = A5::read();
}

void Benchmark::compare_outputs() {		//Cette méthode vérifie que les outputs théoriques et pratiques sont bien les mêmes
	for (int i = 0; i < OUTPUT_SIZE ; i++) {
		if (output[i] != actual_output[i]){
			serial_t_::printf("\x1B[31Erreur avec l'input %s Attendu : %s  Lu : %s", get_input(), get_output(), get_actual_output());
			return;
		}
	}
	printf("\x1B[30Input %s : OK", get_input());
}

const char* Benchmark::get_input() {
	char buffer[INPUT_SIZE];
	for (int i = 0; i < INPUT_SIZE; i++){
		buffer[i] = '0' + input[i];
	}
	return buffer;
}

const char* Benchmark::get_output() {
	char buffer[OUTPUT_SIZE]];
	for (int i = 0; i < OUTPUT_SIZE ; i++){
		buffer[i] = '0' + output[i];
	}
	return buffer;
}

const char* Benchmark::get_actual_output() {
	char buffer[OUTPUT_SIZE];
	for (int i = 0; i < OUTPUT_SIZE ; i++){
		buffer[i] = '0' + actual_output[i];
	}
	return buffer;
}

unsigned int Benchmark::twopow(unsigned int pow) {
	if (pow) {
		return 2 * twopow (pow-1);
	} else {
		return 1;
	}
}

unsigned int Benchmark::string_to_uint(const char* buffer) {
	if (strlen(buffer) <= 3) 					// Si l'utilisateur rentre directement le uint désiré
		return (unsigned int)std::atoi(buffer);
	if (strlen(buffer) != INPUT_SIZE) {			// Si la saisie ne correspond à rien
		printf("Configuration incorrecte");
		return 0;
	}
	int ret = 0;
	for (int i = 0; i<INPUT_SIZE ; i++ ) {		//Si l'utilisateur a entré sa configuration d'input en binaire
		if ((buffer[i] - '0')) {			//Si on ne lit pas un '0'
		ret += twopow(i);					
	}
	return ret;
}


//
//void Benchmark::test_incr_1001(){
//	serial_t_::printf("Test_incr_1001");
//	overflow::high();
//	ign_overflow::low();
//	NOT::low();
//	INC::high();
//	for (int i = 0; i < 8; i++) {
//		if (i%2) 001::high() else 001::low();
//		if ((i/2)%2) 010::high() else 010::low();
//		if ((i/4)%2) 100::high() else 100::low();
//		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
//		if((o001::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
//			serial_t_::printf("\x1B[31Probleme : incrementation avec input = %d, et config = 1001",i);
//		} else if ((overflow_out::read()) != (i == INPUT_SIZE)) {
//			serial_t_::printf("\x1B[31Probleme : flag overflow à 0 avec input = 7, et config = 1001");
//		} else {
//			serial_t_::printf("\x1B[30Incrementation avec input %d, et config = 1001			OK", i);
//		}
//	}
//}
//
//void Benchmark::test_incr_0101(){
//	serial_t_::printf("Test_incr_0101");
//	overflow::low();
//	ign_overflow::high();
//	NOT::low();
//	INC::high();
//	for (int i = 0; i < 8; i++) {
//		if (i%2) 001::high() else 001::low();
//		if ((i/2)%2) 010::high() else 010::low();
//		if ((i/4)%2) 100::high() else 100::low();
//		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
//		if((o001::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
//			serial_t_::printf("\x1B[31Probleme : incrementation avec input = %d, et config = 0101",i);
//		} else if ((overflow_out::read()) != (i == INPUT_SIZE)) {
//			serial_t_::printf("\x1B[31Probleme : flag overflow à 0 avec input = 7, et config = 0101");
//		} else {
//			serial_t_::printf("\x1B[30Incrementation avec input %d, et config = 0101			OK", i);
//		}
//	}
//}
//
//void Benchmark::test_incr_1101(){
//	serial_t_::printf("Test_incr_1101");
//	overflow::high();
//	ign_overflow::high();
//	NOT::low();
//	INC::high();
//	for (int i = 0; i < 8; i++) {
//		if (i%2) 001::high() else 001::low();
//		if ((i/2)%2) 010::high() else 010::low();
//		if ((i/4)%2) 100::high() else 100::low();
//		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
//		if((o001::read()) + ((010_out::read())*2) + ((100_out::read())*4) != ((i+1)%8))) {
//			serial_t_::printf("\x1B[31Probleme : incrementation avec input = %d, et config = 1101",i);
//		} else if ((overflow_out::read()) != (i == INPUT_SIZE)) {
//			serial_t_::printf("\x1B[31Probleme : flag overflow à 0 avec input = %d, et config = 1101", i);
//		} else {
//			serial_t_::printf("\x1B[30Incrementation avec input %d, et config = 1101			OK", i);
//		}
//	}
//}
//
//void Benchmark::test_rien_0001(){
//	serial_t_::printf("Test_rien_1001");
//	overflow::low();
//	ign_overflow::low();
//	NOT::low();
//	INC::high();
//	for (int i = 0; i < 8; i++) {
//		if (i%2) 001::high() else 001::low();
//		if ((i/2)%2) 010::high() else 010::low();
//		if ((i/4)%2) 100::high() else 100::low();
//		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
//		if((o001::read()) + ((010_out::read())*2) + ((100_out::read())*4) != i) {
//			serial_t_::printf("\x1B[31Probleme : rien avec input = %d, et config = 0001",i);
//		} else if (overflow_out::read()) {
//			serial_t_::printf("\x1B[31Probleme : flag overflow à 1 avec config = 0001");
//		} else {
//			serial_t_::printf("\x1B[30Rien avec input %d, et config = 0001			OK", i);
//		}
//	}
//}
//void Benchmark::test_zero(){
//	serial_t_::printf("Test_zero_flag");
//	001::low();
//	010::low();
//	100::low();
//	for (int i = 0; i < 16; i++) {
//		if (i%2) overflow::high() else overflow::low();
//		if ((i/2)%2) ign_overflow::high() else ign_overflow::low();
//		if ((i/4)%2) NOT::high() else NOT::low();
//		if ((i/8)%2) INC::high() else INC::low()
//		_delay_us(5000);		// on attend 5 ms, delai à changer en fonction du temps de reponse de l'alu
//		if( zero_out::read() != 1 ) {
//			serial_t_::printf("\x1B[31Probleme : zero flag à 0 avec input = 0 et config = %d", i); //convertisseur en binaire à faire, mais là flemme
//		} else {
//			serial_t_::printf("\x1B[30Zero flag                                                OK"); //convertisseur en binaire à faire, mais là flemme
//		}
//	}
//}
