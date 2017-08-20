#ifndef _BIND_H_
#define _BIND_H_

//#include "Assert.h"

//#include "EventSystems/EventListener.h"

//template< class TTarget, class ...Args >
//class CBindNonReturn
//{
//private:
//	TTarget* m_Target;
//	void( TTarget::*m_pCallback )( Args... );
//
//public:
//	CBindNonReturn( void( TTarget::*pCallback )( Args... ) )
//		: m_Target( nullptr )
//		, m_pCallback( pCallback )
//	{}
//
//	CBindNonReturn< TTarget, Args... > WithTarget( TTarget* target )
//	{
//		m_Target = target;
//		return *this;
//	}
//
//	void Run( Args... args )
//	{
//		ARTIS_ASSERT( m_Target, "i think WithTarget has not been called" );
//
//		( m_Target->*m_pCallback )( args... );
//	}
//};
//
////http://stackoverflow.com/questions/2795023/c-template-typedef
////template< class TTarget, class TNewTarget, class ...Args >
////using TBindCallback = TNewTarget( TTarget::* )( Args... );
//
//template< class TTarget, class ...Args >
//using TBindCallbackStatic = void( TTarget::* )( Args... );
//
//template< class TNewTarget, class ...Args >
//static TBindCallbackStatic< TNewTarget, Args... > ConvertCallbackWithTarget( void( *pCallback )( Args... ) )
//{
//	return ( TBindCallbackStatic< TNewTarget, Args... > )pCallback;
//}
//
//template< class TNewTarget, class ...Args >
//static CBindNonReturn< TNewTarget, Args... > CBindCreate( void( *pCallback )( Args... ) )
////CBind< Target > CBindCreate( Target target, Function pCallback )
//{
//	return CBindNonReturn< Args... >( pCallback ); //ConvertCallbackWithTarget<TNewTarget>( pCallback ) );
//}

//template< class TTargetClass, class TReturn, class TTarget, class ...Args >
//CBindNonReturn< TReturn, Args... > CBindCreateWithTarget( void( TTarget::*pCallback )( Args... ), TTarget tTarget )
////CBind< Target > CBindCreate( Target target, Function pCallback )
//{
//	return CBind< TReturn, Args... >( pCallback ).WithTarget( tTarget );
//}

#endif // _BIND_H_