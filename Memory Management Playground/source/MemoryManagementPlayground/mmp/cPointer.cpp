#include "mmp/cPointer.h"

cDummy::cDummy()
{
	data = 0;
	size = 0;
}
// copy ctor
cDummy::cDummy(cDummy const& rhs)
	: cDummy(rhs.size)
{
	// copy data in actual array
	if (data)
	{
		size = rhs.size;
		data = new blah[size];
	}
}
// move ctor
cDummy::cDummy(cDummy&& rhs)
{
	size = rhs.size;
	data = rhs.data;
	rhs.data = 0;
}

cDummy::~cDummy()
{
	if (data)
	{
		delete[]data;
	}
}
// param ctor
cDummy::cDummy(size_t newSize)
{
	if (newSize > 0)
	{
		size = newSize;
		data = new blah[size];
	}
	else
	{
		size = 0;
		data = 0;
	}
}

// copy assign
cDummy& cDummy::operator=(cDummy const& rhs)
{
	if (data)
	{
		size = 0;
		delete[]data;
	}
	if (rhs.data)
	{
		size = rhs.size;
		data = new blah[size];
		// copy data
	}

	return *this;
	
}
// move assign
cDummy& cDummy::operator=(cDummy&& rhs)
{
	if (data)
	{
		size = 0;
		delete[]data;
	}
	size = rhs.size;
	data = rhs.data;
	rhs.data = 0;

	return *this;
}
