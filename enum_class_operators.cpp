/*****************************************************************************
 * This model program demonstrates the prefix and postfix operator ++ for
 * a enum class
 *****************************************************************************/

#include <iostream>

using std::cout;
using std::ostream;



enum class TrafficLight { red, yellow, green };



ostream& operator <<(ostream& out, const TrafficLight& t)
{
	switch ( t )
	{
		case TrafficLight::red:		out << "red";    break;
		case TrafficLight::yellow:	out << "yellow"; break;
		case TrafficLight::green:	out << "green";  break;
	}
	return out;
}



TrafficLight& operator ++(TrafficLight& t)  // Prefix version
{
	switch ( t )
	{
		case TrafficLight::red:		t = TrafficLight::yellow; break;
		case TrafficLight::yellow:	t = TrafficLight::green;  break;
		case TrafficLight::green:	t = TrafficLight::red;    break;
	}
	return t;
}



TrafficLight operator ++(TrafficLight& t, int)  // Postfix version
{                                      //  ^
	const TrafficLight old_t = t;
	switch ( t )
	{
		case TrafficLight::red:		t = TrafficLight::yellow; break;
		case TrafficLight::yellow:	t = TrafficLight::green;  break;
		case TrafficLight::green:	t = TrafficLight::red;    break;
	}
	return old_t;
}



int main()
{
	TrafficLight tl;
//	tl = 0;  // Compilation error: cannot convert ‘int’ to ‘TrafficLight’
//	tl = TrafficLight::red;  // Correct assignment
	tl = static_cast<TrafficLight>(0);
	cout << tl << ' ' << ++tl << ' ' << ++tl << ' ' << ++tl << '\n';
	cout << tl++ << ' ' << tl++ << ' ' << tl++ << ' ' << tl << '\n';	
}
