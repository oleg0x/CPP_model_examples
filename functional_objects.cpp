/*****************************************************************************
 * This model program demonstrates how to create and use a function object,
 * that is an object for which the function call operator () is defined, 
 * and also how to create an std::function.
 *****************************************************************************/

#include <functional>
#include <iostream>
#include <vector>

using std::cout, std::function;



class AddTo
{
public:
	AddTo(int n) : n_ {n} {}
	int operator () (int m) { return n_ += m; }

private:
	int n_;
};



template <typename T>
class LessThan
{
public:
	LessThan(const T& v) : value_ {v} {}
	bool operator () (const T& x) const { return x < value_; }

private:
	const T value_;
};



template <typename C, typename P>
size_t CountIf(const C& c, P predicate)
{
	size_t res = 0;
	for ( const auto& x : c )
		if ( predicate(x) )  ++res;
	return res;
}



int SomeFunc(double d)
{
    cout << d << '\n';
    return 0;
}



struct SomeStruct
{
    explicit SomeStruct(int num) : num_(num) {}
    void PrintAdd(int i) const { cout << num_+i << '\n'; }    
    int num_;
};



int main()
{
	AddTo a(2);
	cout << a(3) << ' ' << a(100) << '\n';
	
	LessThan<int> lt(10);
	cout << std::boolalpha << lt(9) << ' ' << lt(11) << '\n';
	
	const std::vector<float> v {-5.5, 3.14, 0.0, 2.7, -10, 1.2};
	cout << CountIf(v, LessThan(2)) << "\n\n";
	
	function<int(double)> f1 = SomeFunc;  // Store a free function
	f1(14.134725);
 
	function<void(int n)> f2 = [](int n) { SomeFunc(n); };  // Store a lambda
	f2(1000);
	
	// Store a call to a member function
	function<void(const SomeStruct&, int)> f3 = &SomeStruct::PrintAdd;
	const SomeStruct s(100);
	f3(s, 42);
//	f3(100, 42);  // Compilation error: no match for call to ‘(function<void(const SomeStruct&, int)>) (int, int)’
 
	// Store a call to a data member accessor
	function<int(SomeStruct const &)> f4 = &SomeStruct::num_;
	cout << "num_ = " << f4(s) << '\n';
    
	// Store a call to a function object
	function<int(int)> f5 = AddTo(30);
	cout << f5(20) << '\n';
}
