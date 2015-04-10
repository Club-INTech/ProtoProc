/** \file main.cpp
 * \author Dede
 * \brief Le fichier le plus important de tous, contenant le coeur du code de test.
 */

#include "benchmark.h"

int main()
{
    Benchmark & benchmark = Benchmark::Instance();
	while(1)
	{
 		benchmark.communiquer_pc();
	}
	return 0;
}