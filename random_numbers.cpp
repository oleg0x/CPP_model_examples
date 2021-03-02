/*****************************************************************************
 * This model program demonstrates how to generate random numbers (both
 * integral and real) with uniform distribution on a given segment.
 *****************************************************************************/

#include <iostream>
#include <map>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;



inline int GetRandom(int min, int max)
{
	// min + rand() % 6 would be biased
	return min + rand() / ((RAND_MAX + 1u) / (max - min + 1));
}



int main()
{
	{   // C-style simple random numbers from stdlib.h
		srand(time(NULL));  // use current time as seed for random generator
		int random_var = rand();
		cout << "Random value on [0, " << RAND_MAX << "]: "  << random_var << '\n';
		cout << "Random value on [-3, 5]: " << GetRandom(-3, 5) << '\n';
		for ( auto i = 0; i < 20; ++i )  cout << GetRandom(-3, 5) << ' ';
		cout << '\n';
	}
	
	{   // Integral random numbers
		random_device rd;   // Is used to obtain a seed for the random number engine
		mt19937 gen(rd());  // Predefined generator of mersenne_twister_engine
		uniform_int_distribution<int16_t> distr(1, 6);
	
		// operator() generates random numbers distributed according to the probability function.
		int16_t random_var = distr(gen);
		cout << random_var << '\n';
		for ( uint8_t n = 0; n < 20; ++n )  cout << distr(gen) << ' ';
		cout << '\n';
    
		distr.param(uniform_int_distribution<int16_t>::param_type(0, 9));  // Change the parameter set
		map<int16_t, uint16_t> hist;
		for ( uint16_t i = 0; i < 20000; ++i )  ++hist[distr(gen)];
		// Plot a histogram for these numbers
		for ( auto p : hist )
			cout << p.first << " : " << string(p.second/100, '*') << '\n';
	}
	
	{   // Real random numbers
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<float> dis(-1.0, 1.0);
		for ( uint8_t i = 0; i < 5; ++i )  cout << dis(gen) << ' ';
		cout << '\n';
	}
}
