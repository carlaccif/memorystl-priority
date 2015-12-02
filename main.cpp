// a commnet
#include <iostream>
#include <set>
#include <iterator>
#include <functional>
#include <algorithm>
using namespace std;

#include "node.h"

template <class T>
void print(const T  &r) {
	cout << r << " " ;
}

allocList_t allocL;
freeList_t freeL;

int main() {
	srand((unsigned int) time(NULL));
	
	freenode f(0,1000);
	freeL.insert(f);
	
	int  clock = 0;
	do {
		cout << "Time " << clock << " *** ";
//
//	generate  a memory request
//
		int size = newSize();
		freeList_t::iterator j = find_if(freeL.begin(),freeL.end(),
	                        	bind2nd(ptr_fun(firstfit),size));
		
                if ( j != freeL.end()) {
			cout << size << " found --->";
			cout << *j << endl;	
			allocnode a(j->getStart(),size,clock+newLease());
			allocL.insert(a);
			freenode  f(j->getStart()+size,j->getSize()-size);
	                freeL.erase(j);
			freeL.insert(f);
		} else cout << size << " not found \n";
//
// remove node from alloclist
//
		allocnode clockn(0,0,clock);
		allocList_t::iterator i = find(allocL.begin(), allocL.end(),clockn);
		while ( i != allocL.end()) {
                        freenode f;
			f = *i;  
			freeL.insert(f);
			cout << "expired block : " << *i << endl;	
			allocL.erase(i);
			i = find(allocL.begin(),allocL.end(),clockn);
		} 
		
	} while  ( ++clock <  TIME_LIMIT);

		
	cout << "Dumping Allocated Memory Blocks\n\n";
	for_each(allocL.begin(),allocL.end(),print<allocnode>);

	cout << endl << "Dumping Free Memory Blocks\n\n";
	for_each(freeL.begin(),freeL.end(),print<freenode>);
	cout <<endl;
	return 0;
}	
