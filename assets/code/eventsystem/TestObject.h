#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "EventListener.h"

class CTestObject
	: public IEventListener
{
public:
	CTestObject( void );

	//////////////////////////////////////////////////////////////////////////
	// callback methods - simple method
	void CB_CallbackSimpleMember( void );
	static void CB_CallbackSimpleStatic( void );

	//////////////////////////////////////////////////////////////////////////
	// callback methods - simple method 
	static void CB_CallbackComplexStatic( int iValue, double dValue );

	//////////////////////////////////////////////////////////////////////////
	// callback methods - variadic method
	static void CB_CallbackVariadicStatic1( int iCount );
	static void CB_CallbackVariadicStatic2( int iCount, double dValue );
	void CB_CallbackVariadicMember1( int iCount );
	void CB_CallbackVariadicMember2( int iCount, double dValue );
};

#endif // _TESTOBJECT_H_