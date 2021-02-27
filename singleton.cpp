/*****************************************************************************
 * This model program demonstrates the design pattern Singleton.
 *****************************************************************************/

#include <iostream>

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

protected:
	Singleton() = default;  // Ctor is protected to forbid creation of the object

private:
	static Singleton* instance_;
	int data_;
};

Singleton* Singleton::instance_ = nullptr;



int main()
{
//	Singleton s;  // Compilation error: Singleton() is protected within this context

	Singleton* p = Singleton::Instance();
	p->DoSomething(111);
	p->Print();

	Singleton* another_p = Singleton::Instance();
	another_p->Print();
	
	delete p;
//	delete another_p;
}
