/*****************************************************************************
 * This model program demonstrates operator overloading for a class of
 * rational numbers.
 *****************************************************************************/

#include <cassert>
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
	Rational(int p, int q);
	Rational& operator =(const Rational& other);
	Rational& operator +=(const Rational& other);
	Rational& operator -=(const Rational& other);
	Rational& operator *=(const Rational& other);
	Rational& operator /=(const Rational& other);
	
private:
	int p_;
	int q_;
	void Reduce();
	
	friend bool operator ==(const Rational& lhs, const Rational& rhs);
	friend bool operator <(const Rational& lhs, const Rational& rhs);
	friend const Rational operator +(const Rational& lhs, const Rational& rhs);
	friend const Rational operator -(const Rational& lhs, const Rational& rhs);
	friend const Rational operator *(const Rational& lhs, const Rational& rhs);
	friend const Rational operator /(const Rational& lhs, const Rational& rhs);
	friend ostream& operator <<(ostream& os, const Rational& r);
};



void Rational::Reduce()
{
	const int k = Euclid(p_, q_);  // std::gcd(p_, q_);
	p_ /= k;
	q_ /= k;
}



Rational::Rational(int p, int q) : p_ {p}, q_ {q}
{
	if ( q_ < 0 ) { p_ = -p; q = -q; }
	Reduce();
}



Rational& Rational::operator=(const Rational& other)
{
//	if ( this == &right )  return *this;
	p_ = other.p_;
	q_ = other.q_;
	return *this;
}



Rational& Rational::operator+=(const Rational& other)
{
	p_ = p_ * other.q_ + other.p_ * q_;
	q_ *= other.q_;
	Reduce();
	return *this;
}



Rational& Rational::operator*=(const Rational& other)
{
	p_ *= other.p_;
	q_ *= other.q_;
	Reduce();
	return *this;
}



bool operator ==(const Rational& lhs, const Rational& rhs)
{
	return lhs.p_ == rhs.p_ && lhs.q_ == rhs.q_;
}



bool operator <(const Rational& lhs, const Rational& rhs)  // For sets and maps
{
	return lhs.p_ * rhs.q_ - rhs.p_ * lhs.q_ < 0;
}



const Rational operator +(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_ + rhs.p_ * lhs.q_, lhs.q_ * rhs.q_);
//	return { lhs.p_ * rhs.q_ + rhs.p_ * lhs.q_, lhs.q_ * rhs.q_ };  // The same
}



const Rational operator -(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_ - rhs.p_ * lhs.q_, lhs.q_ * rhs.q_);
}



const Rational operator *(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.p_, lhs.q_ * rhs.q_);
}



const Rational operator /(const Rational& lhs, const Rational& rhs)
{
	return Rational(lhs.p_ * rhs.q_, lhs.q_ * rhs.p_);
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
	assert( r1 + r2 == Rational(2, 5) );
	assert( r1 - r2 == Rational(1, 5) );
	assert( r1 * r2 == Rational(3, 100) );
	assert( r1 / r2 == Rational(3, 1) );
	
	r1 += r2;
	r2 *= r1;
	cout << r1 << ' ' << r2 << '\n';
	assert( r1 == Rational(2, 5) );
	assert( r2 == Rational(1, 25) );
	
	cout << (r1 = r2) << '\n';
	assert( r1 == r2 && r1 == Rational(1, 25) );
	    
	const set<Rational> rs = {{1, 2}, {2, 4}, {50, 100}, {1500, 3000}};
	for ( const auto& r : rs )  cout << r << '\n';
	if ( rs.size() == 1 ) cout << "1/2 == 2/4 == 50/100 == 1500/3000 \n";
	assert( rs.size() == 1 );
	assert( rs == (set<Rational> {{2, 4}}) );

	map<Rational, int> m;
	++m[{1, 3}];
	++m[{2, 5}];
	++m[{3, 9}];
	++m[{10, 25}];
	for ( auto [r, i] : m )  cout << r << ' ' << i << '\n';
	assert( m == (map<Rational, int> { {{1, 3}, 2}, {{2, 5}, 2} }) );
}
