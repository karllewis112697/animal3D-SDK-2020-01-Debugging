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

	// managed buffer; output of what you're doing with malloc
	char* buffer = new char[1024];
	// created object on the buffer with placement new
	cDummy* obj3 = new (buffer) cDummy(3);
	// do stuff

	////

	// destroy the object when done with it, dont do anything else
	// Every CONSTRUCTOR must have a DESTRUCTOR call
	obj3->~cDummy();
	// set pointer to 0 to indicate it is no longer in use
	obj3 = 0;
	// then de
	delete[] buffer;

	cNonVoidTest<int> testNonVoid;
	
	cNonVoidTest <void> testVoid;
	//testVoid.someFunc(3);

}