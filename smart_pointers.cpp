/*****************************************************************************
 * This model program demonstrates how to use smart pointers unique_ptr,
 * shared_ptr and weak_ptr and showes runtime polymorphism.
 *****************************************************************************/ 

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;



struct Base
{
	int data;
	Base(int i) : data {i} { cout << "Base::Base()\n"; }
	virtual ~Base() { cout << "Base::~Base()\n"; }
	virtual void DoSomething() { cout << "Base::DoSomething() " << data << '\n'; }
};



struct Derived : public Base
{
	Derived(int i) : Base(i) { cout << "Derived::Derived()\n"; }
	~Derived() { cout << "Derived::~Derived()\n"; }
	void DoSomething() override { cout << "Derived::DoSomething() " << data << '\n'; }
};



void Foo(unique_ptr<Base> p1, shared_ptr<Base> p2)
{
	cout << "Foo:\n";
	p1->DoSomething();
	p2->DoSomething();
}



void Bar(Base* p, Base& b)
{
	cout << "Bar:\n";
	p->DoSomething();
	b.DoSomething();
}



int main()
{
	// Different ways to create a unique_ptr
	{
		unique_ptr<Base> p1 = unique_ptr<Base>(new Base(1));
		p1 = nullptr;  // The object managed by p1 is destroyed here
		unique_ptr<Base> p2(new Base(2));
		unique_ptr<Base> p3 {new Base(3)};
		unique_ptr<Base> p4 = make_unique<Base>(4);
		auto p5 = make_unique<Base>(5);
	}
	
	{
		cout << '\n';
		unique_ptr<Base> u_p {new Base(1)};
		u_p->DoSomething();
		u_p.reset(new Derived(2));  // The object of Base is destroyed here
		u_p->DoSomething();
	}  // The object of Derived is destroyed here
	
	{
		cout << '\n';
		unique_ptr<Base> p1 = make_unique<Base>(10);  // unique_ptr to Base
		p1->DoSomething();
		auto p2 = make_unique<Base>(20);  // unique_ptr to Base
		p2->DoSomething();
//		p1 = p2;  // Compilation error: use of deleted function 'operator='
		p1 = move(p2);  // The object managed by p2 is destroyed here
//		p2 = move(p1);  // Also OK
		p1->DoSomething();
//		p2->DoSomething();  // Runtime error: segmentation fault
	}

	{
		cout << '\n';
		shared_ptr<Base> p1 {new Derived(100)};  // shared_ptr to Base
		p1->DoSomething();
		auto p2 = make_shared<Derived>(200);  // shared_ptr to Derived
		p2->DoSomething();
		p1 = p2;
//		p2 = p1;  // Compilation error: no match for ‘operator=’ (operand types are ‘shared_ptr<Derived>’ and ‘shared_ptr<Base>’)
		cout << "use_count == " << p1.use_count() << '\n';
		p1->DoSomething();
		p2->DoSomething();  // Also OK
	}
	
	{
		cout << '\n';
		unique_ptr<Base> p1 = make_unique<Derived>(1000);  // unique_ptr to Base
		shared_ptr<Base> p2 = make_shared<Derived>(2000);  // shared_ptr to Derived
//		Foo(p1, p2);  // Compilation error: use of deleted unique_ptr ctor
		Foo(move(p1), p2);
//		Bar(p2, *p2);  // Compilation error: cannot convert ‘shared_ptr<Base>’ to ‘Base*’
		Bar(p2.get(), *p2);
	}
	
	// weak_ptr is a smart pointer that holds a non-owning ("weak") reference 
	// to an object that is managed by shared_ptr.
	{
		cout << '\n';
		weak_ptr<int> w_p;
		{
			auto sh_p = make_shared<int>(777);
			w_p = sh_p;
			cout << "use_count == " << w_p.use_count() << ": ";
			// Has to be copied into a shared_ptr before usage
			if ( auto spt = w_p.lock() )  cout << *spt << "\n";
		}
		
		if ( !w_p.lock() )
			cout << "use_count == " << w_p.use_count() << ": gw is expired\n";
	}
	
	{
		cout << '\n';
		shared_ptr<Base> sp1( new Base(1), 
			[](auto p)
			{
				cout << "Custom deleter in lambda\n";
				delete p;
			} );
		
		struct Deleter
		{ 
			void operator () (Base* p) const
			{
				cout << "Custom deleter in function object\n";
				delete p;
			}
		};
		shared_ptr<Base> sp2(new Base(2), Deleter());
	}
}
