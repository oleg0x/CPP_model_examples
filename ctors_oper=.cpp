/*****************************************************************************
 * This model program demonstrates how constructors and operator= work.
 * Default, parameterized, copy, move constructors and also copy and move 
 * assignments are considered.
 *****************************************************************************/ 

#include <cstdint>
#include <iostream>
#include <string>
#include <cstring>
#include <utility>

using namespace std;

using Size = uint32_t ;
using Data = int;



class SomeClass
{
public:
	SomeClass() = delete;							// Default constructor is deleted
	explicit SomeClass(const Size size);			// Explicit parameterized constructor
	SomeClass(const Size size, const string& name);	// Parameterized constructor
	SomeClass(const SomeClass& other);				// Copy constructor
	SomeClass(SomeClass&&  other);					// Move constructor

	virtual ~SomeClass();							// Destructor
	
	const SomeClass& operator =(const SomeClass& other);	// Copy assignment
	const SomeClass& operator =(SomeClass&& other);			// Move assignment
	
	virtual const SomeClass& DoSomething(const Data value);
	friend ostream& operator<<(ostream& out, const SomeClass& sc);

private:
	Size size_ = 0;
	Data* p_data_ = nullptr;
	string name_ = "DefaultName";
};



/* SomeClass::SomeClass()  // Default constructor
{
	cout << "SomeClass :: default constructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
} */



SomeClass::SomeClass(const Size size)  // Parameterized constructor
	: size_ {size}, p_data_ {new Data[size_]}
{
	cout << "Parameterized constructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
}



SomeClass::SomeClass(const Size size, const string& name)  // Parameterized constructor
	: size_ {size}, p_data_ {new Data[size_]}, name_ {name}
{
	cout << "Parameterized constructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
}



SomeClass::SomeClass(const SomeClass& other)  // Copy constructor
	: size_ {other.size_}, p_data_ {new Data[other.size_]}, name_ {other.name_}
{
	memcpy(p_data_, other.p_data_, sizeof(Data) * size_);
	cout << "Copy constructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
}



SomeClass::SomeClass(SomeClass&& other)  // Move constructor
	: size_ {other.size_}, p_data_ {other.p_data_}, name_ {move(other.name_)}
{
	other.size_ = 0;
	other.p_data_ = nullptr;
//	other.name_ = "DefaultName";  // "What you don’t use, you don’t pay for (zero-overhead rule)"
	cout << "Move constructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";

}



SomeClass::~SomeClass()
{
	delete[] p_data_;
	cout << "Destructor,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
}



const SomeClass& SomeClass::operator=(const SomeClass& other)  // Copy assignment
{
	if ( this != &other )
	{
		delete[] p_data_;
		size_ = other.size_;
		p_data_ = new Data[size_];
		name_ = other.name_;
		memcpy(p_data_, other.p_data_, sizeof(Data) * size_);
	}
	cout << "Copy assignment,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
	return *this;
}



const SomeClass& SomeClass::operator=(SomeClass&& other)  // Move assignment
{
	if ( this != &other )
	{
		delete[] p_data_;
		size_ = other.size_;
		p_data_ = other.p_data_;
		name_ = move(other.name_);
		other.size_ = 0;
		other.p_data_ = nullptr;
//		other.name_ = "DefaultName";  // "What you don’t use, you don’t pay for (zero-overhead rule)"
	}
	cout << "Move assignment,  size_ = " << size_ 
		 << ", name = " << name_ << ".\n";
	return *this;
}



const SomeClass& SomeClass::DoSomething(const Data value)
{
	for ( Size i = 0; i < size_; ++i )
		p_data_[i] = value;
	cout << name_ << ": do something.\n";
	return *this;
}



ostream& operator<<(ostream& out, const SomeClass& sc)
{
	out << sc.name_ << ":";
	if ( sc.size_ == 0 )
		out << " empty\n";
	else
	{
		for ( Size i = 0; i < sc.size_; ++i )
			out << ' ' << sc.p_data_[i];
		out << '\n';
	}
	return out;
}



int main()
{
	cout << "\n-----Creating-----\n";
	
//	SomeClass sc0;				// Compilation error: use of deleted function!
	
//	SomeClass sc1 = 100;		// Compilation error: conversion from ‘int’ to non-scalar type
	
	SomeClass sc2(5);
	cout << sc2 << sc2.DoSomething(1);
	
	SomeClass sc3(9, "ObjectName");
	cout << sc3 << sc3.DoSomething(2);
	
	cout << "\n-----Coping-----\n";
	
	SomeClass sc4(sc3);			// Copy constructor is used
	cout << sc4;
	
	SomeClass sc5 = sc3;		// Copy constructor is used
	cout << sc5;
	
	SomeClass sc6 {sc3};		// Copy constructor is used
	cout << sc6 << sc3;

	sc6 = sc2;					// Copy assignment is used	
	cout << sc6 << sc2;
	
	sc6 = sc6;					// Self-assignment is working properly
	cout << sc6;
	
	sc2 = sc3 = sc4.DoSomething(3);
	cout << sc2 << sc3 << sc4;
	
	cout << "\n-----Moving-----\n";
	
	SomeClass sc7(move(sc2));	// Move constructor is used
	cout << sc7 << sc2;
		
	SomeClass sc8 = move(sc3);	// Move constructor is used
	cout << sc8 << sc3;
	
	SomeClass sc9 {move(sc4)};	// Move constructor is used
	cout << sc9 << sc4;
	
	sc9 = move(sc7);			// Move assignment is used
	cout << sc9 << sc7;

	sc9 = move(sc9);			// Self-assignment is working properly
	cout << sc9;
		
	cout << "\n-----Destructing-----\n";
}
