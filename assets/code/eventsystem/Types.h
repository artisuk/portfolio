#ifndef _TYPES_H_
#define _TYPES_H_


// generic types
// integer types
typedef		char			i8;
typedef		unsigned char	u8;
typedef		short			i16;
typedef		unsigned short	u16;
typedef		int				i32;
typedef		unsigned int	u32;
typedef		long			i64;
typedef		unsigned long	u64;

// floating point types 
typedef		float			f32;
typedef		double			f64;


// gctypeid stuff

//////////////////////////////////////////////////////////////////////////
// typedef for our typeID value
typedef unsigned int GCTypeID;


//////////////////////////////////////////////////////////////////////////
// type specialised templated TypeID class
//
// This generates a typeid using the address of a static variable.
//
// Since 2 variables can't occupy the same memory address they will be unique.
//
template< typename T >
class TGCTypeIDGenerator
{
public:
	// this generates a typeID for each class that instantiates the template
	static GCTypeID GetTypeID( void )
	{
		static char s_chTheAdressOfThisIsTheClassID;
		return reinterpret_cast< GCTypeID >( &s_chTheAdressOfThisIsTheClassID );
	}

	// no instance of this class can be created.
private:
	TGCTypeIDGenerator( void )
	{}
};

// macro for getting hold of a type's ID
#define GetGCTypeIDOf( TYPENAME )		( TGCTypeIDGenerator< TYPENAME >::GetTypeID() )

// since all GCTypeIDs are essentially valid memory addresses the only safe thing to 
// use for the invalid ID is the system invalid pointer default: NULL - i.e. 0
#define GCTYPEID_INVALID	0


//////////////////////////////////////////////////////////////////////////
// template function that resolves to the correct form of 
// CReflectionData< T >::GetTypeID() based on the input type
template< typename T >
GCTypeID GetTypeIDOfVariable( T instance )
{
	return TGCTypeIDGenerator< T >::GetTypeID();
}


#endif // _TYPES_H_