/*
Memory Management Playground (MMP)
By Daniel S. Buckstein
Copyright 2019-2020
*/
//-----------------------------------------------------------------------------

#include "mmp/mmp_memory.h"

#pragma comment(lib, "MemoryManagementPlayground.lib")


//-----------------------------------------------------------------------------

typedef		byte				chunk_kb[1024];


//-----------------------------------------------------------------------------

#define		decl_argc			ui32 const argc
#define		decl_argv			cstrp const argv[]
typedef		i32(*entry_func)(decl_argc, decl_argv);


//-----------------------------------------------------------------------------

int testMMP(decl_argc, decl_argv);
int testMalloc(decl_argc, decl_argv);


//-----------------------------------------------------------------------------

int main(decl_argc, decl_argv)
{
	return testMMP(argc, argv);
	//return testMalloc(argc, argv);
}


//-----------------------------------------------------------------------------

int testMMP(decl_argc, decl_argv)
{

	// stack-allocate a bunch of data
	chunk_kb chunk[12];
	size count = sizeof(chunk);
	ptr chunk_base = mmp_set_zero(chunk, count);

	// -----------------------------------NEW-------------------------------------//

	// holds pointer to the pool once its been initalized
	addr* memPool;

	// holds pointers to an allocated block
	addr* memBlock;
	addr* memBlock2;



	/* call init, using chunk base as the start of the list
	 chunk base is the start of our memory address list
	 count is how big the start of memory address is
	 chunk is our pool size since its a larger amount of data and we want a pool of mem blocks from it
	*/
	memPool = mmp_pool_init(chunk_base, (size)count, (size)chunk);

	// call reserve, or our version of malloc using our chunk pool
	memBlock = mmp_block_reserve(memPool, (size)count);

	// call reserve, or our version of malloc using our chunk pool
	memBlock2 = mmp_block_reserve(memPool, (size)count *2);

	// call release to free our block after we're finished with it
	mmp_block_release(memBlock, memPool);

	// call release to free our block after we're finished with it
	mmp_block_release(memBlock2, memPool);

	// call reserve, or our version of malloc using our chunk pool
	memBlock = mmp_block_reserve(memPool, (size)count);

	// call term at the end, freeing up our pool after we're done with it
	mmp_pool_term(chunk_base);


	// done, stack-allocated data popped
	printf("\nPress enter to continue....\n");
	getchar();
	return 0;
}


//-----------------------------------------------------------------------------

#include <stdlib.h>

// used for discovering how malloc and free work
int testMalloc(decl_argc, decl_argv)
{
	/*
	// points to some memory address; type unknown
	void* p;
	// points to memory address, but KNOWS HOW BIG IT IS IN MEMORY
	int* pi;
	// points to memory address that you know how long it is, but can't change the VALUE at where its pointing
	// cannot actually modify the object
	int const* kpi; // int const kpi[]
	// points to memory address that you know how long it is, but can't change WHAT YOU'RE POINTING AT
	// cannot modify the pointer but can tell the object what to do
	int* const pki; // int pki[]
	// a const pointer to a constant int; YOU CANNOT CHANGE THE VALUE OR WHAT YOU'RE POINTING AT
	int const** const kpki;// int const kpkspfksp [][][]
	// Point down a chain
	//int const* const* const* const kpkpkpkppk; // int const kpkpkpkpki[][][]
	// 
	int**** ppppppp;
	*/
	// figure out what this data actually means
	// then implement data structure if it was the real thing
	// then in memory.c, add my own structures
	// figure out what is pertinent
	// what does the C standard library used to format data when malloc is used?
	union malloctest
	{
		i32 data[32];
		ptr pdata[32];
		struct
		{
			i32 dummy;
		};

	};
	typedef union malloctest malloctest;
	
	malloctest* test1024 = malloc(1024);
	malloctest* test2048 = malloc(2048);
	malloctest* test4096 = malloc(4096);

	
	*test1024->pdata = malloc(sizeof(int));

	int* intTest = malloc(sizeof (int));
	
	free (intTest);
	free(*test1024->pdata);
	free(test4096);
	free(test2048);
	free(test1024);

	// done
	return 0;
}
