#ifndef _EVENTVARIADICSTATIC_H_
#define _EVENTVARIADICSTATIC_H_

#include "EventVariadic.h"

template< class ...Args >
class CEventVariadicStatic
	: public IEventVariadic
{
private:
	void( *m_pCallback )( Args... );

protected:
	template< class TType>
	void Store( u32 uIndex, TType arg )
	{
		m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
	}

	template< class TType, class ...Argss >
	void Store( u32 uIndex, TType arg, Argss... args )
	{
		m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
		Store( ++uIndex, args... );
	}

public:

	CEventVariadicStatic( const char* pszName, void( *pCallback )( Args... ) );

	//template< class ...Args >
	void Run( Args... args );
};

template< class ...Args >
CEventVariadicStatic< Args... >::CEventVariadicStatic( const char* pszName, void( *pCallback )( Args... ) ) : IEventVariadic( pszName, false )
, m_pCallback( pCallback )
{
	m_uSize = sizeof...( Args );

	m_aIDs = new GCTypeID[ m_uSize ];

	// creates every variadic argument into a param list, these have use, its just there so all the arguments can be looped though to store their gctypeid
	Store( 0, ( ( Args )0 )... );
}

template< class ...Args >
void CEventVariadicStatic< Args... >::Run( Args... args )
{
	// run a run command
	m_pCallback( args... );
}

#endif // _EVENTVARIADICSTATIC_H_