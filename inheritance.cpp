/*****************************************************************************
 * This model program demonstrates inheritance of classes and peculiarities 
 * of working with corresponding objects via variables and pointers. It also 
 * demonstrates calls of virtual functions from constructors.
 *****************************************************************************/ 

#include <iostream>

using namespace std;

using Type1 = double;
using Type2 = int;



class Aaa
{
public:
	explicit Aaa(Type2 data) : data_ {data}
	{
		cout << "\nAaa constructor    ";
	}
	virtual ~Aaa()
	{
		cout << "Aaa destructor\n";
	}
	void DoSomethingBase() const  // This function is not virtual
	{
		cout << "Aaa: " << data_ << '\n';
	}
	virtual void DoSomethingPolymorph()
	{
		cout << var_ << " Aaa\n";
	}

protected:
	Type1 var_ = 2.71828;

private:
	Type2 data_;
};



class Bbb : public Aaa
{
public:
	explicit Bbb(Type2 data) : Aaa(data)
	{
		cout << "Bbb constructor    ";
	}
	~Bbb()
	{
		cout << "Bbb destructor    ";
	}
	virtual void DoSomethingPolymorph() override
	{
		var_ *= 2;
//		data_ += 10;  // Compilation error: Aaa::data_ is private within this context
		cout << var_ << " Bbb\n";		
	}
};



class Ccc : public Bbb
{
public:
	explicit Ccc(Type2 data) : Bbb(data)
	{
		cout << "Ccc constructor    ";
	}
	~Ccc()
	{
		cout << "Ccc destructor    ";
	}
	void DoSomethingBase() const  // Non-virtual function with the same name
	{
		cout << "Ccc: " << ch_ << '\n';
	}
	// Member function DoSomethingPolymorph() is not overrided in this class

private:
	char ch_ = '#';
};



void PrintVptr(void* p)
{
	auto p2 = reinterpret_cast<size_t*>(p);
	cout << "Vpointer: " << *p2 << '\n';
}



class Base
{
public:
	Base()
	{
		cout << "Base::Base(), ";
		PrintVptr(this);
		VirtFunc();  // Always called Base::VirtFunc(), though it's virtual
//		AnotherVirtFunc();  // Warning: call to pure virtual function has undefined behavior;
	}                       // overrides in subclasses are not available here
	virtual ~Base()
	{
		cout << "Base::~Base(), ";
		PrintVptr(this);
	}
	virtual void VirtFunc() { cout << "Base::VirtFunc()" << '\n'; }
	virtual void AnotherVirtFunc() = 0;  // Pure virtual function
};



class Derived : public Base
{
public:
	Derived()
	{
		cout << "Derived::Derived(), ";
		PrintVptr(this);
		AnotherVirtFunc();
	}
	~Derived()
	{
		cout << "Derived::~Derived(), ";
		PrintVptr(this);
	}
	void VirtFunc() override { cout << "Derived::VirtFunc" << '\n'; }
	void AnotherVirtFunc() override { cout << "Derived::AnotherVirtFunc" << '\n'; }
};



int main ()
{
	{
		cout << "Through local variables:\n";
		
		Aaa a(100);
		cout << '\n';
		a.DoSomethingBase();
		a.DoSomethingPolymorph();
		
		Bbb b(101);
		cout << '\n';
		b.DoSomethingBase();
		b.DoSomethingPolymorph();
		
		Ccc c(102);
		cout << '\n';
		c.DoSomethingBase();       // Ccc::DoSomethingBase() is called
		c.DoSomethingPolymorph();  // Bbb::DoSomethingPolymorph() is called
		
		cout << '\n';
		// Here these objects are destroyed in reverse order.
	}
	
	{
		cout << "\nThrough pointers to objects:\n";
	
		Aaa* p_a = new Aaa(100);  // Pointer to the base class
		cout << '\n';
		p_a->DoSomethingBase();
		p_a->DoSomethingPolymorph();
	
		Aaa* p_b = new Bbb(101);  // Pointer to the base class
		cout << '\n';
		p_b->DoSomethingBase();
		p_b->DoSomethingPolymorph();
	
		Aaa* p_c = new Ccc(102);  // Pointer to the base class
		cout << '\n';
		p_c->DoSomethingBase();   // Aaa::DoSomethingBase() is called
		dynamic_cast<Ccc*>(p_c)->DoSomethingBase();  // Ccc::DoSomethingBase() is called
		p_c->DoSomethingPolymorph();  // Bbb::DoSomethingPolymorph() is called
	
		delete p_a;
		delete p_b;  // Destructors are called in reverse order: Bbb, Aaa.
		delete p_c;  // Destructors are called in reverse order: Ccc, Bbb, Aaa.
	}
	
	{
		Ccc c1(1);
		Ccc c2(2);
		cout << '\n';
		PrintVptr(&c1);  // The same vtable as for 'c2'
		PrintVptr(&c2);  // The same vtable as for 'c1'
	}
	
	{
//		Base b;  // Compilation error: cannot declare variable ‘b’ to be of abstract type
		cout << '\n';
		Base* p = new Derived;
		delete p;
	}
}
