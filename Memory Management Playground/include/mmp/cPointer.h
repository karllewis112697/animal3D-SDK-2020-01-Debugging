#ifndef _CPOINTER_H_
#define _CPOINTER_H_

template <bool, typename t = void>
struct TYPEDEF {};
template <typename t>
struct TYPEDEF<true, t> { typedef t TYPE; };

#define TYPE(T)			TYPEDEF<T != void>::TYPE
#define NONVOID (T)		template <typename t = TYPE (T)>

template <typename T>
class cNonVoidTest
{
public: 
	NONVOID(T) t someFunc(int value) {}
};


struct blah
{
	int stuff;
};

class cDummy
{
	blah* data;
	size_t size;
public:
	// def ctor
	cDummy();
	// copy ctor
	cDummy(cDummy const& copy);
	// move ctor
	cDummy(cDummy&& rhs);
	// def dtor
	~cDummy();

	// param ctor
	cDummy(size_t newSize);

	// copy assignment operator
	cDummy& operator =(cDummy const& rhs);
	// move assignment operator
	cDummy& operator =(cDummy&& rhs);

	// accessor operator
	blah* operator->() const
	{
		return data;
	}

};

class cPointer
{

};

// new/delete
void* operator new (size_t sz);
void* operator new[] (size_t sz);
void operator delete (void* ptr);
void operator delete[] (void* ptr);
// placement new
void* operator new(size_t sz, void* buffer);
// placement new array
void* operator new[](size_t sz, void* buffer);
// placement delete
void operator delete (void* buffer, void* ptr);
// placement delete array
void operator delete[] (void* buffer, void* ptr);

#include "mmp/_inl/cPointer.inl"
#endif //!_CPOINTER_H
