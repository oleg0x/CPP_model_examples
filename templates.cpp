/*****************************************************************************
 * This model program demonstrates how to use function templates (including 
 * variadic templates), class templates and variable templates
******************************************************************************/

#include <iostream>
#include <array>
#include <list>
#include <vector>

using namespace std;



//template <class T>   // Older version
template <typename T>  // Newer version
T Sqr(T t)             // Simple function template
{
//	int T;  // Compilation error: this declaration shadows template parameter
	return t * t;
}



template <typename T, int N>
class SomeClass  // Class template
{
public:
	using value_type = T;
	SomeClass() 
	{
		for ( auto i = 0; i < N; ++i )  buf[i] = 0;
	}
	constexpr int Size() { return N; }
	SomeClass DoSomething()
	{
		for ( auto i = 0; i < N; ++i )  buf[i] = 2 * i + 100;
		return *this;
	}
	void Print() const
	{
		for ( auto i = 0; i < N; ++i )  cout << buf[i] << ' ';
		cout << '\n';
	}
private:
	T buf[N];
};



template <typename Cont, typename  Oper>
void ForAll(Cont& c, Oper op)
{
	for ( auto& x : c )  op(x);
}



template <typename T>
constexpr T some_const = 1.234;  // Variable template

template <typename T>
constexpr array<T, 3> some_const_arr {1.11, 2.22, 3.33};  // Variable template



template <typename T, typename ... Tail>  // Variadic template
void Print(const T& head, const Tail&... tail)
{
	cout << head << ' ';
	if  constexpr( sizeof...(tail) > 0 )  Print(tail...);
}



template <typename ... T>  // Variadic template
void Print2(T&& ... args)  // Forwarding references
{
//	std::forward<T>(t)
	(cout << ... << args) << '\n';  // Fold expression
}



template <typename ... Args>  // Variadic template
void Clear(Args& ... args)
{
	(args.clear(), ...);
}


template <class T1,                         // Parameter-type
          typename T2,                      // Parameter-type
          uint16_t N,
          T2 DefaultValue,
          typename Character = char>        // Default parameter
struct SomeStruct
{
	T1 t1_[N];
	T2 t2_;
	Character ch_;
	
	template <typename T> T DoSomething(T t);  // Function template in class template
};

template <class T1, typename T2, uint16_t N, T2 DefaultValue, typename Character>
template <typename T> 
T SomeStruct<T1, T2, N, DefaultValue, Character>::DoSomething(T t)
{
	return t;
}



int main()
{
	{
		cout << Sqr<uint16_t>(5) << ' ' << Sqr<float>(3.14) << '\n';
		cout << Sqr(5) << ' ' << Sqr(3.14) << '\n';  // Implicit argument deduction
	
		SomeClass<int16_t, 10> buffer;  // Instantiation
		buffer.Print();
		cout << buffer.Size() << ": ";
		buffer.DoSomething().Print();
	}
	
	{
		vector<int> v {10, 15, 20, 25, 30};
		ForAll( v, [](auto& x){ x = x * 2 + 1; cout << x << ' '; } );
		cout << endl;
		list<float> l {10.5, 20.3, 30.8, 40,7};
		ForAll( l, [](auto& x){ x /= 3; cout << x << ' '; } );
		cout << endl;
	}
	
	{
		cout << some_const<float> << ' ' << some_const<double> << '\n';
		cout << some_const_arr<float>[0] << ' ' << some_const_arr<float>[1]
			 << ' ' << some_const_arr<float>[2];
		cout << endl;
	}
	
	{
		Print(true, 5, 10.75, "abcd");
		cout << '\n';
		Print2(4, ' ', 12.67, ' ', "Hello");
		
		vector v {1, 2, 3, 4, 5};
		string s {"Some string"};
		Clear(v, s);
		cout << v.size() << ' ' << s.size() << '\n';
	}
	
	{
		SomeStruct<int, char, 3, 'a'> obj;  // Instantiation
		obj.t1_[0] = 100;  obj.t1_[1] = 101;
		cout << obj.DoSomething<double>(14.134725) << '\n';
	}
}
