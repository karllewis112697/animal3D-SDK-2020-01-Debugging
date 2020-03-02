// _macros.h
// Daniel S. Buckstein, 2020
// Handy macros and shorthands.

#ifndef __MACROS_H_
#define __MACROS_H_


// token stringify and concatenate
///
#define __token_str(x)				#x
#define __token_cat(x, y)			x##y
#define token_str(x)				__token_str(x)
#define token_cat(x, y)				__token_cat(x, y)


// simple mathematical operations
///
#define minimum(x, y)				((x) <= (y) ? (x) : (y))
#define maximum(x, y)				((x) >= (y) ? (x) : (y))
#define clamp(lower, upper, value)	((value) >= (lower) ? (value) <= (upper) ? (value) : (upper) : (lower))


// simple logical operations
///
#define swap2(x, y, tmp)			tmp=x;x=y;y=tmp
#define swap3(x, y, z, tmp)			tmp=x;x=y;y=z;z=tmp
#define swap4(x, y, z, w, tmp)		tmp=x;x=y;y=z;z=w;w=tmp


#endif	// !__MACROS_H_