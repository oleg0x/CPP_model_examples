/*****************************************************************************
 * This model program demonstrates how to throw exceptions and catch them, 
 * and using 'noexcept' specifier, either.
 *****************************************************************************/

#include <iostream>
#include <stdexcept>

using namespace std;

void AnotherFunc(int n);



struct Foo
{
	Foo()  { cout << "Foo constructed\n"; }
	~Foo() { cout << "Foo destroyed\n"; }
};



struct Bar
{
	Bar()
	{
		cout << "Bar is constructing...\n";
		throw runtime_error("Some exception!");
	}
	~Bar() { cout << "Bar destroyed\n"; }  // Dtor will not be called
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
	Foo obj;
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
		SomeFunc(30);
		SomeFunc(5);
	}
	catch ( invalid_argument& ex )
	{
		cout << ex.what() << '\n';
	}
	catch (...)
	{
		cout << "Unknown exception!" << '\n';
	}
	
	NoexceptFunc(100);
	cout << std::boolalpha
		 << "Is SomeFunc noexcept? " << noexcept(SomeFunc(1)) << '\n'
		 << "Is NoexceptFunc noexcept? " << noexcept(NoexceptFunc(1)) << '\n'
		 << "Is lambda '[]{}' noexcept? " << noexcept([]{}) << '\n'
		 << "Is lambda '[]() noexcept {}' noexcept? " << 
			noexcept([]() noexcept {}) << '\n'
		 << "Is MayThrow noexcept? " << noexcept(MayThrow()) << '\n'
		 << "Is NoThrow noexcept? " << noexcept(NoThrow()) << '\n';

	Bar b;  // Dtor of 'b' will not be called

	NoexceptFunc(5);

	cout << "This string will not be printed\n";

}
