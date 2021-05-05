/*****************************************************************************
 * This model program demonstrates different alignments in filds of structs,
 * bit fields and '#pragma pack' directive.
 * clang++ alignment_padding.cpp -std=c++20 -Wpadded -Xclang -fdump-record-layouts-simple -o zzz
 *****************************************************************************/



#include <iostream>

using std::cout;



#define SIZEOF(T) ( \
	cout << #T << ": sizeof = " << sizeof(T) << ", " \
		 << "alignof = " << alignof(T) << '\n' )



struct CarPlate1
{
	char c1;     // 1 byte, padding here
	int number;  // 4 bytes
	char c2;     // 1 byte
	char c3;     // 1 byte, padding here
	int region;  // 4 bytes
};         // Sum: 11 bytes; Actually: 16 bytes

#pragma pack(push, 1)  // Control the maximum alignment for the next class
struct CarPlate2  // Slower operations with this atruct
{
	uint16_t number;  // 2 bytes
	char c1;          // 1 byte
	char c2 = 'A';    // 1 byte, equal-initializer
	char c3 {'B'};    // 1 byte, brace-initializer
	uint16_t region;  // 2 bytes
};               // Sum: 7 bytes; Actually: 7 bytes
#pragma pack(pop)

struct CarPlate3  // Bit-field struct; slower operations
{
	uint32_t number : 10;
	uint32_t c1     : 4;
	uint32_t c2     : 4;
	uint32_t c3     : 4;
	uint32_t region : 10;
};            // Sum: 32 bits; Actually: 4 bytes



struct Base1
{
	int i;
	char ch;
};

struct Base2
{
	int16_t n;
	double d;
};

// The same alignment in memory as Derived
struct Aggregator
{
	Base1 b1;
	Base2 b2;
	int8_t n;
};

// The same alignment in memory as Aggregator
struct Derived : public Base1, public Base2
{
	int8_t n;
};



int main()
{
	SIZEOF(CarPlate1);
	cout << offsetof(CarPlate1, c1) << ' ' << offsetof(CarPlate1, number) << ' '
	     << offsetof(CarPlate1, c2) << ' ' << offsetof(CarPlate1, c3) << ' '
		 << offsetof(CarPlate1, region) << '\n';
	
	SIZEOF(CarPlate2);
	cout << offsetof(CarPlate2, c1) << ' ' << offsetof(CarPlate2, number) << ' '
	     << offsetof(CarPlate2, c2) << ' ' << offsetof(CarPlate2, c3) << ' '
		 << offsetof(CarPlate2, region) << '\n';
	CarPlate2 plate2;
	cout << plate2.c1 << ' ' << plate2.c2 << ' ' << plate2.c3 << '\n';

	SIZEOF(CarPlate3);
	static_assert(sizeof(CarPlate3) == 4, "Wrong size of CarPlate3");
	CarPlate3 plate3;
//	&plate3.number;         // Compilation error: attempt to take address of bit-field
//	sizeof(plate3.number);  // Compilation error: invalid application of ‘sizeof’ to a bit-field
		
	Aggregator a;
	a.b1.i = 100;
	Derived d;
	d.i = 200;
	cout << d.i << ' ' << a.b1.i << '\n';
}
