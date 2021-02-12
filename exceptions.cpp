/*****************************************************************************
 * This model program demonstrates how to throw exceptions and catch them, 
 * and using 'noexcept' specifier, either.
 *****************************************************************************/

#include <iostream>
#include <stdexcept>

using namespace std;

void AnotherFunc(int n);



struct S
{
	S()  { cout << "S constructed\n"; }
	~S() { cout << "S destroyed\n"; }
};



void SomeFunc(int n)  // Catches and rethrows an exception from AnotherFunc
{
	try
	{
		AnotherFunc(n);
	}
	catch ( invalid_argument& ex )
	{
		cout << "Error in AnotherFunc" << '\n';
		throw;  // Rethrows the currently handled exception to the calling function
	}


}



void AnotherFunc(int n)  // A potentially-throwing function
{
	S obj;
	n -= 10;
	if ( n < 0 )
		throw invalid_argument("AnotherFunc: invalid argument!");
	cout << "AnotherFunc: " << n << '\n';
}



// A noexcept function which calls the potentially-throwing function
void NoexceptFunc(int n) noexcept
{
	cout << "NoexceptFunc" << '\n';
	AnotherFunc(n);
}



auto MayThrow = []{};
auto NoThrow = []() noexcept {};



int main()
{
	try
	{
		SomeFunc(100);
		SomeFunc(5);
	}
	catch ( invalid_argument& ex )
	{
		cout << ex.what() << '\n';
	}
	
	NoexceptFunc(100);
	cout << std::boolalpha
		 << "Is SomeFunc noexcept? " << noexcept(SomeFunc(1)) << '\n'
		 << "Is NoexceptFunc noexcept? " << noexcept(NoexceptFunc(1)) << '\n'
		 << "Is lambda '[]{}' noexcept? " << noexcept([]{}) << '\n'
		 << "Is lambda '[]() noexcept {}' noexcept? " << noexcept([]() noexcept {}) << '\n'
		 << "Is MayThrow noexcept? " << noexcept(MayThrow()) << '\n'
		 << "Is NoThrow noexcept? " << noexcept(NoThrow()) << '\n';
	
	NoexceptFunc(5);  //  std::terminate() is called here
	cout << "This string will not printed\n";
}
