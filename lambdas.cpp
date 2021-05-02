/*****************************************************************************
 * This model program demonstrates how to work with lambdas.
 *****************************************************************************/

#include <iostream>
#include <vector>

using std::cout;



// Syntax:  [captures] <tparams> (params) specifiers { body }
// '&' implicitly capture the used automatic variables by reference,
// '=' implicitly capture the used automatic variables by copy.
// Specifiers:  mutable, constexpr, consteval.



struct SomeStruct
{
	double value;
	explicit SomeStruct(double d)
	{
		value = d;
		cout << "SomeStruct(), " << value << '\n';
	}
	SomeStruct(const SomeStruct& other)
	{
		value = other.value;
		cout << "SomeStruct(const SomeStruct&), " << value << '\n';
	}
};



int main()
{
	const char ch = '*';
	int n = 100;
	std::vector<int16_t> v {5, 1, 3, 8, 7};
	SomeStruct ss(14.134725);
	
	auto l1 = []() {};  // The simplest lambda
	l1();               // Call the lambda
	
	auto l2 = []() { cout << "Simple lambda\n"; };
	l2();
	[]() { cout << "Another simple lambda\n"; }();  // Definition and call

	auto l3 = [](int i)->int { return 2 * i + 3; };  // Return 'int'
	cout << l3(10) << '\n';
	
	[]() { cout << ch << '\n'; }();  // Const integral type initialized with a constant expression
//	[]() { cout << n << '\n'; }();   // Compilation error: ‘n’ is not captured
	
	[n]() { cout << n << '\n'; }();  // By-copy const capture
//	[n]() { n += 5; cout << n; }();  // Compilation error: assignment of read-only variable ‘n’
	[n]() mutable { n += 5; cout << n << '\n'; }();
	cout << "n = " << n << '\n';  // 'n' has not been changed
	
	[&n]() { n += 5; cout << n << '\n'; }();  // By-reference capture
	cout << "n = " << n << '\n';  // 'n' has been changed
	
	auto l4 = [n, &v, ss](int i)  // Copy ctor of 'ss' is called
	{
		cout << n << ' ' << (v[0] += i) << ' ' <<  ss.value << '\n';
	};
	l4(10);
	
	// Capture the used automatic variables by copy
	[=]() { cout << n << ' ' << v[2] << ' ' <<  ss.value << '\n'; }();
	
	// Capture the used automatic variables by reference
	[&]() { cout << ++n << ' ' << ++v[2] << ' ' <<  ++ss.value << '\n'; }();
}
