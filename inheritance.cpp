/*****************************************************************************
 * This model program demonstrates inheritance of classes and peculiarities 
 * of working with corresponding objects via variables and pointers, 
 * including dynamic_cast conversion
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
	/*virtual*/ void DoSomethingBase() const  // This function is not virtual
	{
		cout << "Base: " << data_ << '\n';
	}
	virtual void DoSomethingPolymorph()
	{
		cout << var_ << " aaaaa\n";
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
		cout << var_ << " bbbbb\n";		
	}
};



class Ccc : public Bbb
{
public:
	explicit Ccc(Type2 data)  : Bbb(data)
	{
		cout << "Ccc constructor    ";
	}
	~Ccc() { cout << "Ccc destructor    "; }
	void DoSomethingBase() const  // Non-virtual function with the same name
	{
		cout << "Derived: " << ch_ << '\n';
	}
	// Member function DoSomething() is not overrided in this class

private:
	char ch_ = '*';
};



void PrintVptr(void* p)
{
	auto p2 = reinterpret_cast<size_t*>(p);
	cout << "Vpointer: " << *p2 << '\n';
}



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
		c.DoSomethingBase();  // Ccc::DoSomethingBase() is called
		c.DoSomethingPolymorph();
		
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
		p_c->DoSomethingPolymorph();
	
		delete p_a;
		delete p_b;  // Destructors are called in reverse order: Bbb, Aaa.
		delete p_c;  // Destructors are called in reverse order: Ccc, Bbb, Aaa.
	}
	
	{
		Ccc c1(1), c2(2);
		cout << '\n';
		PrintVptr(&c1);  // The same vtable as for 'c2'
		PrintVptr(&c2);  // The same vtable as for 'c1'
	}
}
