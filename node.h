#ifndef NODE_H
#define NODE_H

const int MIN_LEASE = 10;
const int MAX_LEASE = 30;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 50;
const int MEMORY_SIZE = 1000;
                     
int newLease() {
	return MIN_LEASE + rand() % ( MAX_LEASE - MIN_LEASE);
}
int newSize() {
	return MIN_SIZE+ rand() % ( MAX_SIZE- MIN_SIZE);
}

class range {
protected:
	int start;
	int size;
	enum {MAXSIZE = 1000};
public:
	range(int st=0,int si = MAXSIZE ) : start(st),size(si) {}
	friend ostream & operator<< ( ostream &o, const range&val);
	int getSize(void) const { return size;}
	int getStart(void) const { return start; }
};


class allocnode : public range {
private:
	int lease;
public:
	allocnode() : range(), lease(0) {}
	allocnode(range r,int l) : range(r), lease(l) {}
	allocnode(int start, int size ,int l) : range(start,size), lease(l) {}
	friend bool operator< (const allocnode &a,const  allocnode &b);
	friend bool operator== (const allocnode &a,const  allocnode  &b);
	friend bool operator== (const allocnode &a,const  int b);
	friend ostream & operator<< ( ostream &o, const allocnode &val);
};

class freenode : public range {
public:
	freenode() : range() {}
	freenode( range r) : range(r) {}
	freenode( int start, int size) : range(start,size) {}
	friend bool operator< (const freenode &a,const freenode &b);
	friend ostream & operator<< ( ostream &o, const freenode&val);
	friend bool operator== (const freenode  &a,const  freenode   &b);
	friend bool operator==( const freenode &a, const int b); 
	friend bool firstfit( const freenode a, int b) ;
};

bool firstfit( const freenode a, int b) {
	return ( a.size >=  b);
}

bool operator<( const freenode &a, const freenode &b) 
{
	return ( a.start < b.start);
}
ostream & operator<<( ostream &o, const freenode &n)
{
	return ( o << "start:" << n.start<< " size: " << n.size << endl );
}

bool operator<( const allocnode &a, const allocnode &b) 
{
	return ( a.lease < b.lease);
}

bool operator==( const allocnode &a, const allocnode  &b) 
{
	return ( a.lease == b.lease);
}

ostream &operator<<( ostream &o, const allocnode &n)
{
	return ( o << "start:" << n.start<< " size: " << n.size 
	                                        << " lease : " << n.lease << endl );
}

ostream &operator<<( ostream &o, const range &n)
{
	return ( o << "start:" << n.start<< " size: " << n.size << endl );
}

bool operator==( const freenode &a, const freenode  &b) 
{
	return ( a.start  == b.start) && (a.size == b.size);
}

bool operator==( const freenode &a, const int b) 
{
	return ( a.size  == b) ;
}

typedef multiset<freenode, less<freenode> > freeList_t;
typedef multiset< allocnode , less<allocnode> > allocList_t;


#endif
