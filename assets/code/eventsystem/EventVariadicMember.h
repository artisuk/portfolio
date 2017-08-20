#ifndef _EVENTVARIADICMEMBER_H_
#define _EVENTVARIADICMEMBER_H_


////////////////////////////////////////
// includes
#include "EventVariadic.h"


////////////////////////////////////////
// forward declaration
class IEventListener;


template< class ...Args >
class CEventVariadicMember
	: public IEventVariadic
{
private:
	IEventListener* m_pTarget;
	void( IEventListener::*m_pCallback )( Args... );

protected:
	template< class TType>
	void Store( u32 uIndex, TType arg )
	{
		m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
	}

	template< class TType, class ...AType >
	void Store( u32 uIndex, TType arg, AType... args )
	{
		m_aIDs[ uIndex ] = GetGCTypeIDOf( TType );
		Store( ++uIndex, args... );
	}

public:
	CEventVariadicMember( const char* pszName, IEventListener* pTarget, void( IEventListener::*pCallback )( Args... ) );//CBindNonReturn< IEventListener, Args... > bind )

	//template< class ...Args >
	void Run( Args... args );
};

template< class ...Args >
CEventVariadicMember< Args... >::CEventVariadicMember( const char* pszName, IEventListener* pTarget, void( IEventListener::*pCallback )( Args... ) ) : IEventVariadic( pszName, true )
, m_pTarget( pTarget )
, m_pCallback( pCallback )
{
	m_uSize = sizeof...( Args );

	// create array that has enough elements to hold all the gctypes
	m_aIDs = new GCTypeID[ m_uSize ];

	// creates every variadic argument into a param list, these have no use, its just there so all the arguments can be looped though to store their gctypeid
	Store( 0, ( ( Args )0 )... );
}

template< class ...Args >
void CEventVariadicMember< Args... >::Run( Args... args )
{
	// run the stored pointers
	( m_pTarget->*m_pCallback )( args... );
}

#endif // _EVENTVARIADICMEMBER_H_