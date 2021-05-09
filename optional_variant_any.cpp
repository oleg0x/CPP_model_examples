/*****************************************************************************
 * This model program demonstrates how to use std::variant, std::optional and 
 * std::any to express alternatives.
 *****************************************************************************/ 

#include <any>
#include <iostream>
#include <optional>		
#include <string>
#include <variant>
#include <vector>

using namespace std;



variant<string, int> Func1(int16_t n)
{
	bool no_problems = (n > 0);
	if ( no_problems )
	{
		string str("Func1: some_string");
		return str;
	}
	else
	{
		int error_code = -1;
		return error_code;
	}
}



optional<string> Func2(int16_t n)
{
	bool no_problems = (n > 0);
	if ( no_problems )
	{
		string str("Func2: some_string");
		return str;
	}
//	return nullopt;
	return {};  // The same
}



any Func3(int16_t n)
{
	bool no_problems = (n > 0);
	if ( no_problems )  return string("Func3: some_string");
	return -1;
}



template <typename ... T>
struct overloaded : T...
{
	using T::operator()...;
};

template <typename ... T>
overloaded(T...) -> overloaded<T...>;  // Explicit deduction guide

struct Expression { char ch; };
struct Statement  { int i; };

using Node = variant<Expression, Statement/*, Declaration, Type*/>;

void Check(Node* p)
{
	visit( overloaded {
		[](Expression& e) { cout << "Expression " << e.ch << '\n'; },
		[](Statement& s)  { cout << "Statement "  << s.i <<'\n'; },
		// Declaration, Type
	}, *p );
}



int main()
{
	for ( int16_t i : {1, -1} )
		if ( auto s = Func1(i); holds_alternative<string>(s) )
		{
			string str = get<string>(s);
			str = get<0>(s);  // 0-based index of the alternative
			cout << str << '\n';
		}
		else
		{
			int code = get<int>(s);
			code = get<1>(s);  // 0-based index of the alternative
			cout << "Error code: " << code << '\n';
		}

	cout << '\n';
	for ( int16_t i : {1, -1} )
//		if ( auto s = Func2(i); s.has_value() )
		if ( auto s = Func2(i) )  // The same, but shorter
		{
			string str = *s;
			str = s.value();
			cout << str << '\n';
		}
		else  cout << "Object of std::optional is empty\n";
	cout << Func2(-10).value_or("Optional is empty\n");
	
	cout << '\n';
	cout << any_cast<string>(Func3(1)) << '\n';
	cout << any_cast<int>(Func3(-1)) << '\n';
	
	any a;
	if ( !a.has_value() )  cout << "Object of std::any is empty\n";
	a = 3.14;
	cout << any_cast<double>(a) << ' ' << a.type().name() << '\n';
	a = "ABCDE"s;
	cout << any_cast<string>(a) << ' ' << a.type().name() << '\n';
	
	cout << '\n';
	Node* p = new Node(Expression {'@'});
	Check(p);
	*p = Statement {100};
	Check(p);	
}
