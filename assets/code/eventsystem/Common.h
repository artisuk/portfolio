#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <assert.h>

// simple assert that stops the application if expression is false
#define ARTIS_ASSERT(expression, message) assert(expression) 

// the stringify turns anything provided, e.g. a variable, ands turns it into a string
#define STRINGIFY2(str) #str
#define STRINGIFY(str) STRINGIFY2(str)

// used for the macros, .e.g __funcstig__(?), to be used directly into a construction of a char pointer/array
#define STRINGER(str) str

// prints a message out with a 
template< class ...Args >
inline void PrintOut( const char* pszFormat, Args... args )
{
	char achText[ 128 ];
	sprintf_s( achText, pszFormat, ( args )... );
	std::cout << achText << std::endl;
}

// safely deletes a pointer and sets it to null
template< class TType>
inline void SafeDelete( TType* pPointer )
{
	if( pPointer )
	{
		delete pPointer;
		pPointer = nullptr;
	}
}

// safely deletes an array and sets the pointer to null
template< class TType>
inline void SafeDeleteArray( TType* pPointer )
{
	if( pPointer )
	{
		delete[] pPointer;
		pPointer = nullptr;
	}
}

#endif // _COMMON_H_