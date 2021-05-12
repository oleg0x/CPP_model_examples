/*****************************************************************************
 * This model program demonstrates 
 *****************************************************************************/

#include <iostream>

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

#include <stack>
#include <queue>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;



template <typename Cont>
void Print(const Cont& cont)
{
	for ( auto x : cont )  cout << x << ' ';
	cout << '\n';
}



template <typename Cont>
void PrintMap(const Cont& cont)
{
	for ( auto [key, value] : cont )  cout << '(' << key << ", " << value << ") ";
	cout << '\n';
}



int main()
{ 
	cout << boolalpha;
	
	// Sequence containers --------------------------------
	
	array<int, 5> a {1, 2, 3};
	vector<int> v {11, 12, 13};
	deque<int> d {21, 22, 23};
	forward_list <int> fl {31, 32, 33};
	list<int> l {41, 42, 43};
	
	cout << a.empty() << ' '
	     << v.empty() << ' '
	     << d.empty() << ' '
	     << fl.empty() << ' '
	     << l.empty() << ' ' << '\n';
	
	cout << a.size() << ' '
	     << v.size() << ' '
	     << d.size() << ' '
//	     << fl.size() << ' '  // Absent
	     << l.size() << ' ' << '\n';
	
	a[3] = 4;
	v.push_back(14);
	d.push_back(24);
//	fl.push_back(34);  // Absent
	fl.push_front(30);
	l.push_back(44);
	
	Print(a);
	Print(v);
	Print(d);
	Print(fl);
	Print(l);
	
	cout << a.front() << ' '
	     << v.front() << ' '
	     << d.front() << ' '
	     << fl.front() << ' '
	     << l.front() << '\n';
	
	cout << a.back() << ' '
	     << v.back() << ' '
	     << d.back() << ' '
//	     << fl.back() << ' '  // Absent
	     << l.back() << '\n';
	
	cout << a[2] << ' ' 
	     << v[2] << ' ' 
	     << d[2] << ' '
//	     << fl[2] << ' '  // Absent
//	     << l[2] << ' '   // Absent
	     << '\n';
	
//	a.erase();             // Absent
	v.erase(v.begin());
	d.erase(d.begin());
//	fl.erase(fl.begin());  // Absent
	fl.erase_after(fl.before_begin());
	l.erase(l.begin());
	
	Print(a);
	Print(v);
	Print(d);
	Print(fl);
	Print(l);
	
//	a.clear();  // Absent
	v.clear();
	d.clear();
	fl.clear();
	l.clear();
	
	// Container adaptors ---------------------------------
	
	stack<char> st;
	queue<char> q;
	priority_queue<char> pq;
	
	st.push('a');  st.push('b');  st.push('c');
	q.push('A');  q.push('B');  q.push('C');
	pq.push('2');  pq.push('3');  pq.push('1');
	
	cout << st.empty() << ' '
	     << q.empty() << ' '
	     << pq.empty() << ' ' << '\n';
	
	cout << st.size() << ' '
	     << q.size() << ' '
	     << pq.size() << ' ' << '\n';
	
	cout << st.top() << '\n';
	cout << q.front() << ' ' << q.back() << '\n';
	cout << pq.top() << '\n';
	
	st.pop();
	q.pop();
	pq.pop();
	
	cout << st.top() << '\n';
	cout << q.front() << ' ' << q.back() << '\n';
	cout << pq.top() << '\n';
	
//	st.clear();  // Absent
//	q.clear();   // Absent
//	pq.clear();  // Absent
	
	// Associative containers -----------------------------
	
	set<int> s {2, 3, 1};
	multiset<int> ms {2, 3, 1, 3};
	unordered_set<int> us {2, 3, 1};
	unordered_multiset<int> ums {2, 3, 1, 3};
	
	cout << s.empty() << ' '
	     << ms.empty() << ' '
	     << us.empty() << ' '
	     << ums.empty() << '\n';
	
	cout << s.size() << ' '
	     << ms.size() << ' '
	     << us.size() << ' '
	     << ums.size() << '\n';
	
	s.insert(4);
	ms.insert(1);
	us.insert(4);
	ums.insert(4);
	
	s.erase(2);
	ms.erase(2);
	us.erase(2);
	ums.erase(2);
	
	Print(s);
	Print(ms);
	Print(us);
	Print(ums);
	
	s.clear();
	ms.clear();
	us.clear();
	ums.clear();
	
	map<int, char> m {{20, 'B'}, {30, 'C'}, {10, 'A'}};
	multimap<int, char> mm {{20, 'B'}, {30, 'C'}, {10, 'A'}, {30, 'C'}};
	unordered_map<int, char> um {{20, 'B'}, {30, 'C'}, {10, 'A'}};
	unordered_multimap<int, char> umm {{20, 'B'}, {30, 'C'}, {10, 'A'}, {30, 'C'}};
	
	cout << m.empty() << ' '
	     << mm.empty() << ' '
	     << um.empty() << ' '
	     << umm.empty() << '\n';
	
	cout << m.size() << ' '
	     << mm.size() << ' '
	     << um.size() << ' '
	     << umm.size() << '\n';
	
	m.insert({40, 'D'});
	mm.insert({10, 'A'});
	um.insert({40, 'D'});
	umm.insert({10, 'A'});
	
	m.erase(20);
	mm.erase(20);
	um.erase(20);
	umm.erase(20);

	PrintMap(m);
	PrintMap(mm);
	PrintMap(um);
	PrintMap(umm);
	
	m.clear();
	mm.clear();
	um.clear();
	umm.clear();
}
