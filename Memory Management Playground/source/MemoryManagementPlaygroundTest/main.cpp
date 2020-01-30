#include "mmp/cPointer.h"

int main()
{
	// default ctor
	cDummy obj;
	
	// copy ctor
	cDummy obj2 = obj;
	
	// assign op
	obj = obj2;
	
	// dtors called automatically

	int val = obj->stuff;

	// managed buffer
	char* buffer = new char[1024];
	// created object on the buffer
	cDummy* obj3 = new (buffer) cDummy(3);
	// do stuff

	////

	// destroy the object when done with it, dont do anything else
	obj3->~cDummy();
	delete[] buffer;

}