/*****************************************************************************
 * This model program demonstrates the usage of const with member functions.
 *****************************************************************************/

#include <iostream>

using std::cout;



class SomeClass
{
public:
//	int& Func() const		// 'const' is not allowed here
	int& Func()				// OK without 'const'
	{
		return data_;
	}
	void Print() const
	{
		cout << data_ << '\n';
//		Func();				// Non-const method is not allowed here
	}

private:
	int data_ = 123;
};



int main()
{
	SomeClass sc;
	sc.Print();
	int& x = sc.Func();
	x = 42;
	sc.Print();
}
