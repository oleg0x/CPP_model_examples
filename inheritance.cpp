/*****************************************************************************
 * This model program demonstrates inheritance of classes and peculiarities 
 * of working with corresponding objects via variables and pointers. It also 
 * demonstrates calls of virtual functions from constructors.
 *****************************************************************************/ 

#include <iostream>

using namespace std;

using Type1 = double;
using Type2 = int;



class Foo
{
public:
	explicit Foo(Type2 data) : data_ {data}
	{
		cout << "\nFoo constructor    ";
	}
	virtual ~Foo()
	{
		cout << "Foo destructor\n";
	}
	void DoSomethingBase() const  // This function is not virtual
	{
		cout << "Foo: " << data_ << '\n';
	}
	virtual void DoSomethingPolymorph()
	{
		cout << var_ << " Foo\n";
	}

protected:
	Type1 var_ = 2.71828;

private:
	Type2 data_;
};



class Bar : public Foo
{
public:
	explicit Bar(Type2 data) : Foo(data)
	{
		cout << "Bar constructor    ";
	}
	~Bar()
	{
		cout << "Bar destructor    ";
	}
	void DoSomethingPolymorph() override
	{
		var_ *= 2;
//		data_ += 10;  // Compilation error: Aaa::data_ is private within this context
		cout << var_ << " Bar\n";		
	}
};



class Baz : public Bar
{
public:
	explicit Baz(Type2 data) : Bar(data)
	{
		cout << "Baz constructor    ";
	}
	~Baz()
	{
		cout << "Baz destructor    ";
	}
	void DoSomethingBase() const  // Non-virtual function with the same name
	{
		cout << "Baz: " << ch_ << '\n';
	}
	// Member function DoSomethingPolymorph() is not overridden in this class

private:
	char ch_ = '#';
};



void PrintVptr(void* p)
{
	auto p2 = reinterpret_cast<size_t*>(p);
	cout << "Vpointer: " << p2 << ' ' << *p2 << '\n';
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
		
		Foo a(100);
		cout << '\n';
		a.DoSomethingBase();
		a.DoSomethingPolymorph();
		
		Bar b(101);
		cout << '\n';
		b.DoSomethingBase();
		b.DoSomethingPolymorph();
		
		Baz c(102);
		cout << '\n';
		c.DoSomethingBase();       // Baz::DoSomethingBase() is called
		c.DoSomethingPolymorph();  // Bar::DoSomethingPolymorph() is called
		
		cout << '\n';
		// Here these objects are destroyed in reverse order
	}
	
	{
		cout << "\nThrough pointers to objects:\n";
	
		Foo* p_a = new Foo(100);  // Pointer to the base class
		cout << '\n';
		p_a->DoSomethingBase();
		p_a->DoSomethingPolymorph();
	
		Foo* p_b = new Bar(101);  // Pointer to the base class
		cout << '\n';
		p_b->DoSomethingBase();
		p_b->DoSomethingPolymorph();
	
		Foo* p_c = new Baz(102);  // Pointer to the base class
		cout << '\n';
		p_c->DoSomethingBase();   // Foo::DoSomethingBase() is called
		dynamic_cast<Baz*>(p_c)->DoSomethingBase();  // Baz::DoSomethingBase() is called
		p_c->DoSomethingPolymorph();  // Bar::DoSomethingPolymorph() is called
	
		cout << '\n';
		delete p_a;
		delete p_b;  // Destructors are called in reverse order: Bar, Foo.
		delete p_c;  // Destructors are called in reverse order: Baz, Bar, Foo.
	}
	
	{
		Baz c1(1);
		Baz c2(2);
		cout << '\n';
		PrintVptr(&c1);  // The same vtable as for 'c2'
		PrintVptr(&c2);  // The same vtable as for 'c1'
	}
	
	{
		cout << '\n';
//		Base b;  // Compilation error: cannot declare variable ‘b’ to be of abstract type
		Base* p = new Derived;
		delete p;
	}
}
