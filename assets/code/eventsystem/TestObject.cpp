#include "TestObject.h"

#include "Common.h"
#include "EventListener.h" 
#include "EventManager.h"
#include "EventManagerVariadic.h"


CTestObject::CTestObject( void )
{
	// variadic member
	auto pEventVariadicMember1 = CEventManager::GetEventManger()->RegisterEventMemberVariadic( "Callback test"
																							   , this
																							   , MEMBER_VARIADIC_SELECTOR( CTestObject::CB_CallbackVariadicMember1 ) );
	auto pEventVariadicMember2 = CEventManager::GetEventManger()->RegisterEventMemberVariadic( "Callback test"
																							   , this
																							   , MEMBER_VARIADIC_SELECTOR( CTestObject::CB_CallbackVariadicMember2 ) );
}

//////////////////////////////////////////////////////////////////////////
// simple
void CTestObject::CB_CallbackSimpleMember( void )
{
	PrintOut( "The event has been received by CTestObject::CB_Callback" );
}

void CTestObject::CB_CallbackSimpleStatic( void )
{
	PrintOut( "The event has been received by CTestObject::CB_CallbackStatic" );
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// complex
void CTestObject::CB_CallbackComplexStatic( int iValue, double dValue )
{
	PrintOut( "The event has been received by CTestObject::CB_CallbackComplexStatic ( %i, %f )", iValue, ( float )dValue );
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// variadic
void CTestObject::CB_CallbackVariadicStatic1( int iCount )
{
	PrintOut( "The event has been received ( %i ) " STRINGER( __FUNCSIG__ )
			  , iCount );
}

void CTestObject::CB_CallbackVariadicStatic2( int iCount, double dValue )
{
	PrintOut( "The event has been received ( %i, %f ) " STRINGER( __FUNCSIG__ )
			  , iCount
			  , dValue );
}

void CTestObject::CB_CallbackVariadicMember1( int iCount )
{
	PrintOut( "The event has been received ( %i ) " STRINGER( __FUNCSIG__ )
			  , iCount );
}

void CTestObject::CB_CallbackVariadicMember2( int iCount, double dValue )
{
	PrintOut( "The event has been received ( %i, %f ) " STRINGER( __FUNCSIG__ )
			  , iCount
			  , dValue );
}
//////////////////////////////////////////////////////////////////////////