#ifndef _EVENTMANAGERVARIADIC_H_
#define _EVENTMANAGERVARIADIC_H_

#include <vector>
#include "EventVariadic.h"
#include "EventVariadicStatic.h"
#include "EventVariadicMember.h"
#include "EventListener.h"
#include "Common.h"


//////////////////////////////////////////////////////////////////////////
// type defs
//http://stackoverflow.com/questions/2795023/c-template-typedef
template< class TTarget, class ...Args >
using TBindCallbackVariadic = void( TTarget::* )( Args... );

// called to convert any function from an object that was inherited by the IEventListener
template< class TTarget, class ...Args >
TBindCallbackVariadic< IEventListener, Args... > ConvertCallbackWithTarget( void( TTarget::*pCallback )( Args... ) )
{
	return ( TBindCallbackVariadic< IEventListener, Args... > )pCallback;
}

//////////////////////////////////////////////////////////////////////////
// macros
#define MEMBER_VARIADIC_SELECTOR(ptr) ( ConvertCallbackWithTarget( &ptr ) )

class CEventManagerVariadic
{
private:
	std::vector<IEventVariadic*> m_apEvents;

public:
	template< class ...Args >
	CEventVariadicStatic< Args... >* RegisterEventStaticVariadic( const char* pszEventName, void( *pCallback )( Args... ) );

	template< class ...Args >
	CEventVariadicMember< Args... >* RegisterEventMemberVariadic( const char* pszEventName, IEventListener* pTarget, void( IEventListener::*pCallback )( Args... ) );

	template< class ...Args >
	void CallEventVariadic( const char* pszEventName, Args... args );

	//////////////////////////////////////////////////////////////////////////
	// normal functions
	void UnregisterEvent( IEventVariadic* pEvent );

	//////////////////////////////////////////////////////////////////////////
	// virtual functions
	virtual void Destroy( void );
};

template< class ...Args >
CEventVariadicStatic< Args... >* CEventManagerVariadic::RegisterEventStaticVariadic( const char* pszEventName, void( *pCallback )( Args... ) )
{
	CEventVariadicStatic< Args... >* pEvent = new CEventVariadicStatic< Args...>( pszEventName, pCallback );
	m_apEvents.push_back( pEvent );
	return pEvent;
}

template< class ...Args >
CEventVariadicMember< Args... >* CEventManagerVariadic::RegisterEventMemberVariadic( const char* pszEventName, IEventListener* pTarget, void( IEventListener::*pCallback )( Args... ) )
{
	CEventVariadicMember< Args... >* pEvent = new CEventVariadicMember< Args... >( pszEventName, pTarget, pCallback );// bind );
	m_apEvents.push_back( pEvent );
	return pEvent;
}

template< class ...Args >void CEventManagerVariadic::CallEventVariadic( const char* pszEventName, Args... args )
{
	u32 uCountCalled = 0;
	u32 uArgCount = sizeof... ( args );

	for( std::vector<IEventVariadic*>::iterator it = m_apEvents.begin(); it != m_apEvents.end(); ++it )
	{
		IEventVariadic* pEvent = *it;

		// if the event has the same number of args and the same name

		bool bArgCount = uArgCount == pEvent->GetNumberOfParameters();
		bool bNameComp = strcmp( pszEventName, pEvent->GetName() ) == 0;

		if( bArgCount && bNameComp )
		{
			if( pEvent->IsSameArgs( args... ) )
			{
				++uCountCalled;

				// casts the object to a particular class so the run method would be correct
				if( pEvent->IsMemberFunction() )
				{
					( ( CEventVariadicMember< Args... >* )pEvent )->Run( args... );
				}
				else
				{
					( ( CEventVariadicStatic< Args... >* )pEvent )->Run( args... );
				}
			}
		}
	}

	PrintOut( "CEventManagerVariadic::CallEventVariadic --> While calling for '%s' event, there were %i that responded", pszEventName, uCountCalled );
}

#endif // _EVENTMANAGERVARIADIC_H_