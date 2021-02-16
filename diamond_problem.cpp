/*****************************************************************************
 * This model program demonstrates the so called diamond inheritance problem
 * and its possible solutions with scope resolution and virtual inheritance.
 *****************************************************************************/

#include <iostream> 

using std::cout;



struct Base
{
	explicit Base(int i) : data(i) { cout << "Base::Base  " << data << '\n'; }
	void NonVirtFoo() { cout << "Base::NonVirtFunc " << data << '\n'; }
	virtual void VirtBar() { cout << "Base::VirtFunc " << data << '\n'; }
	int data;
};

//---------------------------------------------------------

struct Left : public Base  // Non-virtual inheritance
{
	Left(int i) : Base(-i) { cout << "Left::Left  " << data << '\n'; }
};



struct Right : public Base  // Non-virtual inheritance
{
	Right(int i) : Base(i) { cout << "Right::Right  " << data << '\n'; }
};



class Diamond : public Left, public Right
{
public:
	Diamond(int i) : Left(i), Right(i + 1)
	{
		cout << "Diamond::Diamond  ";
//		cout << data << '\n';  // Compilation error: reference to ‘data’ is ambiguous
		Left::data *= 2;   // Fild 'data' is available from both parent structs
		Right::data *= 3;  // Fild 'data' is available from both parent structs
		cout << Left::data << "  " << Right::data << '\n';
	}
};

//---------------------------------------------------------

struct VLeft : public virtual Base  // Virtual inheritance
{
	VLeft(int i) : Base(-i) { cout << "Left::Left  " << data << '\n'; }
};



struct VRight : virtual public Base  // Virtual inheritance
{
	VRight(int i) : Base(i) { cout << "Right::Right  " << data << '\n'; }
};



class VDiamond : public VLeft, public VRight
{
public:
	VDiamond(int i) : Base(i), VLeft(i + 1), VRight(i + 2)
	{
		cout << "VDiamond::VDiamond  " << data << "  " 
		     << VLeft::data << "  " << VRight::data << '\n';  // All values are the same
	}
};

//---------------------------------------------------------

int main()
{
	Diamond d(5);
//	d.NonVirtFoo();  // Compilation error: equest for member ‘NonVirtFoo’ is ambiguous
//	d.VirtBar();     // Compilation error: equest for member ‘VirtBar’ is ambiguous
	static_cast<Left>(d).NonVirtFoo();
	static_cast<Right>(d).VirtBar();
	
	cout << '\n';
	
	VDiamond vd(100);
	vd.NonVirtFoo();
	vd.VirtBar();

}
