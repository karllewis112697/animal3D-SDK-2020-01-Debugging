#ifndef _CPOINTER_H_
#define _CPOINTER_H_


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

	// new/delete
	void* operator new (size_t sz)
	{
		return ::operator new (sz);
	}

	void operator delete (void* ptr)
	{
		::operator delete (ptr);
	}

	// placement new
	void* operator new( size_t sz, void* buffer)
	{
		//return ::operator new(sz);
		return buffer;
	}
	// placement delete
	void operator delete (void* buffer, void* ptr)
	{

	}
};

class cPointer
{

};

#include "mmp/_inl/cPointer.inl"
#endif //!_CPOINTER_H
