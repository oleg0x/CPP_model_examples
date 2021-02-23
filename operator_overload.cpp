/*****************************************************************************
 * This model program demonstrates operator overloading for a class of
 * rational numbers.
 *****************************************************************************/

#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;



int Euclid(int a, int b)
{
	while ( a % b )
	{
		int temp = a;
		a = b;
		b = temp % b;
	}
	return abs(b);
}



class Rational
{
public:
	Rational(int p, int q)
	{
		const int gcd = Euclid(p, q);
		p_ = p / gcd;
		q_ = q / gcd;
		if ( q_ < 0 ) {	p_ = -p; q = -q; }
	}

private:
	int p_;
	int q_;
	
	friend bool operator ==(const Rational& lhs, const Rational& rhs);
	friend Rational operator +(const Rational& lhs, const Rational& rhs);
	friend Rational operator -(const Rational& lhs, const Rational& rhs);
	friend Rational operator *(const Rational& lhs, const Rational& rhs);
	friend Rational operator /(const Rational& lhs, const Rational& rhs);
	friend ostream& operator <<(ostream& os, const Rational& r);
	friend bool operator <(const Rational& lhs, const Rational& rhs);
};



bool operator ==(const Rational& lhs, const Rational& rhs)
{
	return lhs.p_ == rhs.p_ && lhs.q_ == rhs.q_;
}



Rational operator +(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_ + rhs.p_ * lhs.q_, lhs.q_ * rhs.q_);
//	return { lhs.p_ * rhs.q_ + rhs.p_ * lhs.q_, lhs.q_ * rhs.q_ };  // The same
}



Rational operator -(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_ - rhs.p_ * lhs.q_, lhs.q_ * rhs.q_);
}



Rational operator *(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.p_, lhs.q_ * rhs.q_);
}



Rational operator /(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_, lhs.q_ * rhs.p_);
}



bool operator <(const Rational& lhs, const Rational& rhs)  // For sets and maps
{
	return lhs.p_ * rhs.q_ - rhs.p_ * lhs.q_ < 0;
}



istream& operator >>(istream& is, Rational& r)
{
	int n, d;
	char ch;
	if ( is )
	{
		is >> n >> ch >> d;
		if ( is )
		{
			if ( ch == '/' )  r = Rational(n, d);
			else  is.setstate(ios_base::failbit);
		}
	}
	return is;
}



ostream& operator <<(ostream& os, const Rational& r)
{
	return os << r.p_ << '/' << r.q_;
}



int main() 
{
	Rational r1(3, 10), r2(1, 10);
	cout << r1 + r2 << ' ' << r1 - r2 << ' ' << r1 * r2 << ' ' << r1 / r2 << '\n';
    
	const set<Rational> rs = {{1, 2}, {2, 4}, {50, 100}, {1500, 3000}};
	for ( auto r : rs )  cout << r << '\n';
	if ( rs.size() == 1 ) cout << "1/2 == 2/4 == 50/100 == 1500/3000 \n";

	map<Rational, int> m;
	++m[{1, 3}];
	++m[{2, 5}];
	++m[{3, 9}];
	++m[{10, 25}];
	for ( auto [r, i] : m )  cout << r << ' ' << i << '\n';
}
