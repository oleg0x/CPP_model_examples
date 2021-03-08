/*****************************************************************************
 * This model program demonstrates some math routine including complex numbers 
 * and valarray.
 *****************************************************************************/ 

#include <cmath>
#include <complex>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numbers>
#include <numeric>
#include <valarray>
#include <vector>

using namespace std;



template <typename T> void Print(const T& c)
{
	for ( auto item : c )  cout << item << ' ';
	cout << '\n';
}



int main()
{
	cout << exp(3) << ' ' << log(20.0855) << '\n';
	cout << pow(123.45, 2.38) << ' ' << sqrt(500.8) << ' ' << cbrt(1000) << '\n';
	cout << sin(0.8) << ' ' << cos(0.8) << ' ' << tan(0.8) << '\n';
	cout << sinh(0.8) << ' ' << cosh(0.8) << ' ' << tanh(0.8) << '\n';
	
	errno = 0;
	cout << "sqrt(-1) = " << sqrt(-1) << '\n';
	if ( errno == EDOM )
		cout << "errno = EDOM (" << strerror(errno) << ")\n";
	
	errno = 0;
    cout <<  "log(0) = " << log(0) << '\n';
	if ( errno == ERANGE )
		cout << "errno = ERANGE (" << strerror(errno) << ")\n";
	
	cout << ceil(2.7)  << ' ' << floor(2.7) << ' ' 
	     << trunc(2.7) << ' ' << round(2.7) << '\n';
	
	float iptr;
	cout << modf(3.14, &iptr) << ' ' << iptr << '\n';
	
	cout << beta(3, 3) << ' ' << tgamma(5) << '\n';
	cout << cyl_bessel_j(2, 1.23) << ' ' << hermite(3, 4) 
	     << laguerre(2, 0.5) << ' ' << legendre(3, 0.25) << '\n';
	cout << "ζ(-1) = "  << riemann_zeta(-1)  << ",    "
	     << "ζ(0) = "   << riemann_zeta(0)   << ",\n"
	     << "ζ(1) = "   << riemann_zeta(1)   << ",    "
         << "ζ(0.5) = " << riemann_zeta(0.5) << ",\n"
         << "ζ(2) = "   << riemann_zeta(2)   << ' '
         << "(π²/6 = "  << pow(acos(-1),2)/6 << ").\n";
	
	cout << fixed << setprecision(10);
	cout << std::numbers::sqrt2 << ' ' << std::numbers::sqrt3 << ' '
	     << std::numbers::pi << ' ' << std::numbers::inv_pi << ' '
	     << std::numbers::e << '\n';

	cout << fixed << setprecision(2) << '\n';
	
	complex<double> z1;
	cout << z1 << ' ' << z1.real() << ' ' << z1.imag() << '\n';
	z1 = -3.25 + 1.4i;
	cout << z1 << ' ' << conj(z1) << ' ' << z1.real() << ' ' << z1.imag() << '\n';
	complex<double> z2(2.5, 4.8);
	cout << z2 << ' ' << z2.real() << ' ' << z2.imag() << '\n';
	complex<float> z3 = 3.7f + 2.3if;
	cout << z3 << ' ' << z3.real() << ' ' << z3.imag() << '\n';
	
	z3 = 1.f + 1.if;
	cout << z3 << ' ' << abs(z3) << ' ' << arg(z3) << '\n';
	
	cout << "Square root of -4 is "	<< sqrt(complex<double>(-4, 0)) << '\n'
	     << "Square root of (-4,-0), the other side of the cut, is "
	     << sqrt(complex<double>(-4, -0.0)) << '\n';

	complex<double> z4 = 1. + 2i;
	complex<double> z5 = conj(z4);
	cout << "(1+2i)*(1-2i) = " << z4 * z5 << '\n';
    
	complex<double> z6 = exp(1i * numbers::pi);  // Euler's formula
	cout << "exp(pi * i) = " << z6 << '\n';

	cout << '\n';
	vector<int> v;
	v.resize(6);
	iota(v.begin(), v.end(), 5);
	Print(v);
	int sum = accumulate(v.begin(), v.end(), 0);
    int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());
	cout << "sum = " << sum << ", product = " << product << '\n';
	
	vector<int> a {0, 1, 2, 3, 4};
	vector<int> b {5, 4, 2, 3, 1};
	int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
	cout << "Inner product of a and b: " << r1 << '\n';
	int r2 = inner_product(a.begin(), a.end(), b.begin(), 0, plus<>(), equal_to<>());
	cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';
	partial_sum(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';
    
    cout << '\n';
    valarray<int> va {1, 4, 2, 9, 5, 3};
	Print(va);
	cout << va.size() << ' ' << va.min() << ' ' << va.max() << ' ' 
	     << va.sum() << '\n';
	
	valarray<int> va2 = va + 10;
	Print(va2);
	va *= 2;
	Print(va);
	
	const valarray<int> bases     { 1, 2, 3, 4, 5, 6, 7 };
	const valarray<int> exponents { 0, 1, 2, 3, 4, 5, 6 };
	const valarray<int> powers = pow(bases, exponents);
	Print(powers);
	
	valarray<double> v1 = {0, 0.25, 0.5, 0.75, 1};
	valarray<double> v2 = sin(v1 * numbers::pi);
	Print(v2);
	
	sort(begin(va), end(va));
	Print(va);
	
	cout << '\n';
	cout << HUGE_VALF << ' ' << HUGE_VAL << ' ' << HUGE_VALL << '\n';
	cout << numeric_limits<bool>::min() << ' ' 
	     << numeric_limits<bool>::max() << '\n';
	cout << numeric_limits<uint16_t>::min() << ' ' 
	     << numeric_limits<uint16_t>::max() << '\n';
	cout << numeric_limits<int>::min() << ' ' 
	     << numeric_limits<int>::max() << '\n';
	cout << numeric_limits<float>::min() << ' ' 
	     << numeric_limits<float>::max() << '\n';
}
