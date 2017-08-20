#ifndef _EVENTVARIADIC_H_
#define _EVENTVARIADIC_H_


////////////////////////////////////////
// includes
#include "Types.h"


class IEventVariadic
{
private:
	// holds the name of the event
	char m_pszName[ 32 ];

	// is this a member event or static
	bool m_bMember;

protected:
	// the amount of arguments this one is using
	u32 m_uSize;

	// the list of ids that this event is listening to
	GCTypeID* m_aIDs;

	// cant be directly created, a subclass must create an instance of this
	IEventVariadic( const char* pszName, bool bMember );

	//////////////////////////////////////////////////////////////////////////
	// template functions
	template< class Arg, class ...Args >
	bool IsSame( u32 uIndex, Arg arg, Args... args );

	template< class Arg >
	bool IsSame( u32 uIndex, Arg arg );

public:
	virtual ~IEventVariadic( void );

	//////////////////////////////////////////////////////////////////////////
	// inline functions
	inline u32 GetNumberOfParameters( void );
	inline const char* GetName( void );
	inline bool IsMemberFunction( void );

	//////////////////////////////////////////////////////////////////////////
	// template functions 
	// called by a manager, it will loop through all the arguments and compare them to the internal array
	template< class ...Args >
	bool IsSameArgs( Args... args );
};

template< class ...Args >
bool IEventVariadic::IsSameArgs( Args... args )
{
	return IsSame( 0, args... );
}

template< class Arg, class ...Args >
bool IEventVariadic::IsSame( u32 uIndex, Arg arg, Args... args )
{
	if( m_aIDs[ uIndex ] == GetGCTypeIDOf( Arg ) )
	{
		return IsSame( ++uIndex, args... );
	}

	return false;
}

template< class Arg >
bool IEventVariadic::IsSame( u32 uIndex, Arg arg )
{
	return m_aIDs[ uIndex ] == GetGCTypeIDOf( Arg );
}

//////////////////////////////////////////////////////////////////////////
// inline functions
inline u32 IEventVariadic::GetNumberOfParameters( void )
{
	return m_uSize;
}

inline const char* IEventVariadic::GetName( void )
{
	return m_pszName;
}

inline bool IEventVariadic::IsMemberFunction( void )
{
	return m_bMember;
}

#endif // _EVENTVARIADIC_H_