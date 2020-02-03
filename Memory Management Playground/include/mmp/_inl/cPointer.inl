#ifdef _CPOINTER_H_
#ifndef _CPOINTER_INL_
#define _CPOINTER_INL_

// pass-thru custom placement new/delete
template <typename bufferType>
inline void* operator new (size_t sz, bufferType* buffer)
{
	// Only allowed to use placement new from now on
	// do whatever management buffer does
	//void* ret = buffer->alloc(sz);
	//return ret;
	void* p = 0;
	return p;
}

template <typename bufferType>
inline void* operator delete (void* p, bufferType* buffer)
{
	// Only allowed to use placement new from now on
	// do whatever management buffer does
//	buffer->dealloc(p);
}

template <typename bufferType>
inline void* operator new[] (size_t sz, bufferType* buffer)
{
	//return operator::new<bufferType>(sz, buffer);
	return 0;
}

template <typename bufferType>
inline void* operator delete[] (void* p, bufferType* buffer)
{
	//operator::operator delete<bufferType>(p, buffer);
}

#endif // !_CPOINTER_INL_

#endif // _CPOINTER_H_

