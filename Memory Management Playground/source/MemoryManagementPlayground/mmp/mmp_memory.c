/*
Memory Management Playground (MMP)
By Daniel S. Buckstein
Copyright 2019-2020
*/
//-----------------------------------------------------------------------------

#include "mmp/mmp_memory.h"

#include "mmp/mmp_file.h"



//-----------------------------------------------------------------------------
// Memory block struct. Stores data about memory blocks for malloc to use
struct memBlock 
{
	// Used to track if this memory block is free for malloc to use; 1 if free, otherwise 0; 
	i8 free;
	// The size of this block. Equal to the passed in size from the malloc call
	size size;
	// Pointer to the next block of memory for malloc to use once this block is allocated
	struct memBlock* next;
}; 
typedef struct memBlock memBlock;


//-----------------------------------------------------------------------------
// internal utilities

static inline cstrp mmp_get_cstr_end(cstrp cstr)
{
	uindex i = 0;
	while (*cstr != 0 && i++ < szcstr)
		++cstr;
	return cstr;
}


static inline byte* mmp_set_byte(byte* block, byte const* const end, byte const value)
{
	while (block < end)
		*(block++) = value;
	return block;
}

static inline dword* mmp_set_dword(dword* block, dword const* const end, dword const value)
{
	while (block < end)
		*(block++) = value;
	return block;
}

static inline cstrp mmp_set_cstr(cstr cstr, dword const value)
{
	return (cstrp)mmp_set_dword((dword*)(cstr), (dword*)(cstr + szcstr), value);
}


static inline byte* mmp_copy_byte(byte* block_dst, byte const* block_src, byte const* const end_dst)
{
	while (block_dst < end_dst)
		*(block_dst++) = *(block_src++);
	return block_dst;
}

static inline dword* mmp_copy_dword(dword* block_dst, dword const* block_src, dword const* const end_dst)
{
	while (block_dst < end_dst)
		*(block_dst++) = *(block_src++);
	return block_dst;
}

static inline cstrp mmp_copy_cstr(cstr cstr_dst, cstrp const cstr_src)
{
	return (cstrp)mmp_copy_dword((dword*)(cstr_dst), (dword*)(cstr_src), (dword*)(cstr_dst + szcstr));
}


static inline byte const* mmp_compare_byte(byte const* block_0, byte const* block_1, byte const* const end_0)
{
	while (block_0 < block_0)
		if (*(block_0) == *(block_1++))
			++block_0;
		else
			break;
	return block_0;
}

static inline dword const* mmp_compare_dword(dword const* block_0, dword const* block_1, dword const* const end_0)
{
	while (block_0 < end_0)
		if (*(block_0) == *(block_1++))
			++block_0;
		else
			break;
	return block_0;
}

static inline cstrp mmp_compare_cstr(cstrp const cstr_0, cstrp const cstr_1)
{
	return (cstrp)mmp_compare_dword((dword*)(cstr_0), (dword*)(cstr_1), (dword*)(cstr_0 + szcstr));
}


//-----------------------------------------------------------------------------
// general memory utilities

addr mmp_set(addr const block, size const size_bytes, byte const value)
{
	if (block && size_bytes > 0)
	{
		byte const value2dword[szdword] = { value, value, value, value };
		dword const value_as_dword = *((dword*)value2dword);
		dword* const base = (dword*)block;
		byte const* const basebp = (byte*)block;
		size const dword_ct = size_bytes / szdword;

		// write integers until the last integer can fit
		dword const* itr = mmp_set_dword(base, (dword_ct + base), value_as_dword);

		// write the remaining bytes
		byte const* itrbp = mmp_set_byte((byte*)itr, (size_bytes + basebp), value);

		// done
		return block;
	}
	return 0;
}


addr mmp_copy(addr const block_dst, kaddr const block_src, size const size_bytes)
{
	if (block_dst && block_src && block_dst != block_src && size_bytes > 0)
	{
		dword* const base_dst = (dword*)block_dst;
		dword const* const base_src = (dword*)block_src;
		byte const* const basebp_dst = (byte*)block_dst;
		size const dword_ct = size_bytes / szdword;
		
		// copy and write integers until the last integer can fit
		dword* itr_dst = mmp_copy_dword(base_dst, base_src, (dword_ct + base_dst));

		// copy and write the remaining bytes
		byte* itrbp_dst = mmp_copy_byte((byte*)itr_dst, ((byte const*)(dword_ct + base_src)), (size_bytes + basebp_dst));
	
		// done
		return block_dst;
	}
	return 0;
}


size mmp_compare(kaddr const block_0, kaddr const block_1, size const size_bytes)
{
	if (block_0 && block_1 && block_0 != block_1 && size_bytes > 0)
	{
		dword const* const base_0 = (dword*)block_0;
		dword const* const base_1 = (dword*)block_1;
		byte const* const basebp_0 = (byte*)block_0;
		size dword_ct = size_bytes / szdword;

		// compare integers until the last integer can fit
		dword const* itr_0 = mmp_compare_dword(base_0, base_1, (dword_ct + base_0));

		// compare the remaining bytes
		byte const* itrbp_0 = mmp_compare_byte((byte*)itr_0, ((byte const*)(itr_0 - base_0 + base_1)), (size_bytes + basebp_0));

		// done
		return (itrbp_0 - basebp_0);
	}
	return 0;
}


//-----------------------------------------------------------------------------
// pool utilities

addr mmp_pool_init(addr const block_base, size const block_base_size, size const pool_size_bytes)
{
	if (block_base && block_base_size && pool_size_bytes)
	{
		// create a pool of memory to read through and 
		// point it to our stack allocated data which represents beginning of memory
		// setting it to a void pointer so it works with any data
		struct memBlock* memoryPool = (void*)pool_size_bytes;

		// initialize the size of the pool to the provided base size
		
		memoryPool->size = block_base_size;

		// initalize the first entry in the pool to free so it can be allocated to with malloc
		memoryPool->free = 1;

		// set the next block in the pool to equal the block base since we're at the start still
		memoryPool->next = block_base;

		return memoryPool;
	}
	return 0;
}


size mmp_pool_term(addr const pool)
{
	if (pool)
	{
	
	}
	return 0;
}


//-----------------------------------------------------------------------------
// block utilities

addr mmp_block_reserve(addr const pool, size const block_size_bytes)
{
	if (pool && block_size_bytes)
	{
		// memory block pointers used to go through pool 
		struct memBlock* current;
		struct memBlock* previous;

		// initialize our current pointer to the start of the pool
		current = pool;
		current->size = block_size_bytes;

		// checks if checked pool can have something allocated from it and checks ecah block at a time
		while ((((current->size) < block_size_bytes) && ((current->free) == 0)) && (current->next != NULL))
		{
			// set previous to the current element in the pool
			previous = current;
			// set current to its next pointer
			current = current->next;
		
		}
		// checks if a checked pool fits the specified reserve size and allocates it
		if ((current->size == block_size_bytes))
		{
			// Our current block is no longer free and has been allocated
			current->free = 0;
			printf("We have a new block allocated with size %I64u\n ", current->size);
			return current;
		}
		else
		{

			return 0;

		}
	}
	return 0;
}


size mmp_block_release(addr const block, addr const pool)
{
	if (block && pool)
	{
		// current block to copy our passed in block to
		struct memBlock* current = block;

		// set the block to be free again so it can be used again 
		current->free = 1;

		printf("Memory at pool %p with size %I64u freed back into pool\n ", pool, current->size);
		
	}
	return 0;
}


//-----------------------------------------------------------------------------
