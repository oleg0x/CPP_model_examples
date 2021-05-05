/*****************************************************************************
 * This model program demonstrates how to use stream iterators with algorithms
 * from standard library
 *****************************************************************************/

#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

using namespace std;



// Reads from cin, sorts the words read, eliminates duplicate words, 
// and writes the result to cout.
void Func1()
{
	istream_iterator<string> ii {cin};
	istream_iterator<string> eos {};  // Read until Ctrl+D (linux)
	vector<string> v {ii, eos};
	sort(v.begin(), v.end());
	
	ostream_iterator<string> oi {cout, ", "};  // with delimiter ", "
	unique_copy(v.begin(), v.end(), oi);
}



void Func2()  // The same as Func1(), but shorter
{
	set<string> s { istream_iterator<string> {cin},
	                istream_iterator<string> {} };
	unique_copy( s.begin(), s.end(), ostream_iterator<string> {cout, ", "} );
}



int main()
{
	{
		ostream_iterator<string> oi {cout};
		*oi = "Hello, ";   // meaning cout << "Hello, "
		*oi = "world!\n";  // meaning cout << "world!\n"
	}
	
//	Func1();
	Func2();  // The same
	cout << '\n';
}
