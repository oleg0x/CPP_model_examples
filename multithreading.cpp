/*****************************************************************************
 * This model program demonstrates how to create threads, share data, use 
 * mutex, async(), and deal with communicating tasks.
 *****************************************************************************/

#include <iostream>
#include <chrono>
#include <random>
#include <queue>
#include <string>

#include <thread>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

using namespace std; 



double Foo(double d) { cout << "Foo \n"; return d * 10; }

void Bar(const vector<int>& v) { cout << "Bar \n" << v[0] << '\n'; }

struct Str
{
	Str(int i) : data {i} {}
	int operator()(int i) { cout << "Str::operator()" << '\n'; return data += i; }
	int data;
};

void F1()  // Several threads
{
	cout << Foo(2.718) << '\n';
	vector<int> v {1, 2, 3};
	Bar(v);
	Str s(100);
	cout << s(10) << "\n\n";
	
	thread thr1(Foo, 3.14);  // The return value of the function is ignored
	thread thr2(Bar, cref(v));  // Pass by const reference
	thread thr3(s, 20);  // runs on a copy of object 's'
	thread thr4(&Str::operator(), &s, 30);  // runs on object s
	
	thr1.join();  // Blocks until the thread finishes its execution
	thr2.join();
	thr3.join();
	thr4.join();
	
	cout << s.data << "\n\n";
}  // Thread objects are safe to destroy here after join()


//-----------------------------------------------------------------------------


void FillRandom(vector<int>& v, size_t start, size_t count)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distr(-100, 100);
	for ( size_t i = start; i < min(start + count, v.size()); ++i )
		v[i] = distr(gen);
}

void FillRandomAsync(vector<int>& v, uint8_t thread_count)
{
	vector<future<void>> futures(thread_count);  // This vector is needed to postpone dtor of future
	const size_t page = v.size() / thread_count;
	uint8_t k;
	for ( k = 0; k < thread_count - 1; ++k )
		futures.push_back( async(FillRandom, ref(v), k * page, page) );
	futures.push_back( async(FillRandom, ref(v), k * page, v.size() - k * page) );
//	for ( auto& f : futures )  f.get();  // Here this is not necessarily
}

template <typename Container> 
void Print(const Container& c)
{
	for ( auto elem : c )  cout << elem << ' ';
	cout << '\n';
}

void F2()  // async with time measuring
{
	using namespace std::chrono;

	vector<int> v(5'000'000);

	auto t = steady_clock::now();
	FillRandom(v, 0, v.size());
	auto dur = steady_clock::now() - t;
	cout << "FillRandom (1 thread): " 
		 << duration_cast<milliseconds>(dur).count() << " ms\n";

	t = steady_clock::now();
	FillRandomAsync(v, 4);
	dur = steady_clock::now() - t;
	cout << "FillRandom (4 threads): " 
         << duration_cast<milliseconds>(dur).count() << " ms\n";
}


//-----------------------------------------------------------------------------


int shared_data = 5;
mutex shared_data_mutex;

void SomeFunc1(int id) 
{
	for (int i = 0; i < 3; ++i)
	{
		shared_data_mutex.lock();
		shared_data += 5;
		cout << id << ": " << shared_data << '\n';
		shared_data_mutex.unlock();
		this_thread::sleep_for(chrono::milliseconds(200));
    }	
}

void SomeFunc2() 
{
	const lock_guard<mutex> lock(shared_data_mutex);
    shared_data *= 2;
	cout << "Thread #" << this_thread::get_id() 
	     << ": " << shared_data <<'\n';
	// 'shared_data_mutex' is automatically released when 'lock' goes out of scope
}

double shared_data_2 = 123.456;
mutex shared_data_2_mutex;

void SomeFunc3() 
{
	scoped_lock<mutex, mutex> lock(shared_data_mutex, shared_data_2_mutex);
	shared_data *= 2;
	shared_data_2 *= 3.5;
	cout << "Thread #" << this_thread::get_id() 
	     << ": " << shared_data << ", " << shared_data_2 <<'\n';
	// Releases the ownership of all owned mutexes. 
}

void F3()
{
	{
		cout << '\n';
		thread thr1(SomeFunc1, 1);
		thread thr2(SomeFunc1, 2);
		thr1.join();
		thr2.join();
	}
	{
		cout << '\n' << shared_data << '\n';
		thread thr1(SomeFunc2);
		thread thr2(SomeFunc2);
		thr1.join();
		thr2.join();
		cout << shared_data << '\n';
	}
	{
		cout << '\n' << shared_data << ", " << shared_data_2 << '\n';
		thread thr1(SomeFunc3);
		thread thr2(SomeFunc3);
		thr1.join();
		thr2.join();
		cout << shared_data << ", " << shared_data_2 << '\n';
	}
}	


//-----------------------------------------------------------------------------


// Many readers and a single writer.

shared_mutex mx; // a mutex that can be shared 

void Reader()  // Many readers
{
	shared_lock lck {mx}; // Other readers can access also
	// read
}

void Writer()  // The only one writer
{
	unique_lock lck {mx}; // Exclusive (unique) access for the writer
	// write
}


//-----------------------------------------------------------------------------


struct Message
{
	explicit Message(const string& s) : str {s} {}
	string str;
};

queue<Message> msg_queue;
condition_variable msg_cond;
mutex msg_cond_mutex;

void Produce()
{
	for ( int i = 1; i <= 3; ++i )
	{
		Message msg("Message #"s + to_string(i));
		this_thread::sleep_for(chrono::milliseconds(400));
		cout << "Produce(): " << msg.str << '\n';
		lock_guard<mutex> lock(msg_cond_mutex);
		msg_queue.push(msg);
		msg_cond.notify_one();  // Unblocks the waiting thread
	}  // release lock
}

void Consume()
{
	for ( int i = 1; i <= 3; ++i )
	{
		unique_lock lock(msg_cond_mutex);
		msg_cond.wait( lock, [](){ return !msg_queue.empty(); } );
		Message msg = msg_queue.front();
		msg_queue.pop();
		lock.unlock();
		cout << "Consume(): " << msg.str << '\n';
	}
}

void F4()  // Classical example of two threads communicating by passing messages through a queue
{
	cout << '\n';
	thread thr1(Produce);
	thread thr2(Consume);
	thr1.join();
	thr2.join();
}


//-----------------------------------------------------------------------------


void DoSomething(promise<double>& pr)
{
	try {
		double result;
		result = 14.134725;  // Compute a value for 'result'
		pr.set_value(result);
	}
	catch ( ... )  // Couldn't compute 'result'
	{
		pr.set_exception(current_exception());
	}
		
}

void F5()  // promise and future
{  
	promise<double> pr;
	future<double> fut = pr.get_future();  // A future referring to the shared state of *this
	thread thr(DoSomething, ref(pr));
	try {
		double d = fut.get();  // If necessary, wait for the value to get computed
		cout << '\n' << d << '\n';
	}
	catch ( ... ) 
	{
		cerr << "Could not compute d \n";
	}
	thr.join();  // Wait for thread completion
}


//-----------------------------------------------------------------------------


int Func(int a, int b)
{
	if ( a == 0 )
		throw invalid_argument("Func(): first argument equals to zero.");
	return 100 / a + b;
}

void F6()
{  // packaged_task
	packaged_task<int(int, int)> task(Func);
	future<int> fut = task.get_future();
	thread thr(move(task), 0, 10);
	thr.join();
	try {
		cout << '\n' << fut.get() << '\n';
	}
	catch ( invalid_argument& ex )
	{
		cerr <<  ex.what() << '\n';
	}
}


//-----------------------------------------------------------------------------


int main()
{
	cout << "Number of concurrent threads supported: " 
	     << thread::hardware_concurrency() << '\n';
	F1();
	F2();
	F3();
	F4();
	F5();
	F6();
}
