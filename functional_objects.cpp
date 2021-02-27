/*****************************************************************************
 * This model program demonstrates how to create and use a function object,
 * that is an object for which the function call operator () is defined.
 *****************************************************************************/

#include <iostream>
#include <vector>

using std::cout;



class AddTo
{
public:
	AddTo(int n) : n_ {n} {}
	int operator () (int m) { return n_ + m; }

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
	size_t result = 0;
	for ( const auto& x : c )
		if ( predicate(x) )  ++result;
	return result;
}



int main()
{
	AddTo a(2);
	cout << a(3) << ' ' << a(4) << '\n';
	
	LessThan<int> lt(10);
	cout << std::boolalpha << lt(9) << ' ' << lt(11) << '\n';
	
	const std::vector<float> v {-5.5, 3.14, 0.0, 2.7, -10, 1.2};
	cout << CountIf(v, LessThan(2)) << '\n';
}
