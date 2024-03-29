/*****************************************************************************
 * This model program demonstrates the design pattern Singleton.
 *****************************************************************************/

#include <iostream>
#include <memory>

using std::cout;



class Singleton
{
public:
//	Singleton() = delete;  // This ctor is needed in 'instance_ = new Singleton'
	~Singleton() { cout << "Singleton()::~Singleton()\n"; }
	static Singleton* Instance()
	{
		if ( !instance_ )  instance_ = new Singleton;
		return instance_;
	}
	void DoSomething(int d) { data_ = d; }
	void Print() const { cout << "Singleton::data_ = " << data_ << '\n'; }

private:
	Singleton() { cout << "Singleton()::Singleton()\n"; }  // Ctor is private to forbid creation of the object
	static Singleton* instance_;
	int data_ = 0;
};

Singleton* Singleton::instance_ = nullptr;



int main()
{
//	Singleton s;  // Compilation error: Singleton() is private within this context

	Singleton* p = Singleton::Instance();
	p->DoSomething(111);
	p->Print();

	auto another_p = std::unique_ptr<Singleton>(Singleton::Instance());
	another_p->Print();
	
//	delete p;  // Runtime error: double free
}
