#include "EventManager.h"
#include "Assert.h"
#include "TestObject.h"

#include <iostream>

using namespace std;

// main sources that guided me towards the right answer
//http://stackoverflow.com/questions/15501322/iterating-over-variadic-templates-type-parameters
//http://eli.thegreenplace.net/2014/variadic-templates-in-c/

//////////////////////////////////////////////////////////////////////////
// Things to add for homework:
// 
// 1) separate into different .cpp and .h files, clean this up, make it robust, add comments 
// 
// 2) this uses local (stack) variables you should ensure your code
//	  which in no way guarantees that the events will be 'alive' when sent
//    consider how to make this work outside of main()? 
//    * interface? 
//    * memory management?
//    * don't forget to deallocate anything you allocate!!
// 
// 3) must be able to handle listener registering to listen to events 
//    that aren't yet registered
// 
// 4) would be nice to have some sort of type safety in the sending of data
//    (see 'sample complex event' for use of typeId etc.)
//
// 5) add unregister and unlisten functionality
// 
// 6) your code must demonstrate use of all features you add to show you 
//    have tested them
//    
// 7) suggestion: discrete startup, update, and shutdown functions will 
//    probably help you show this all works
//    
// 8) consider using cout to print what you're doing to the command line
//    as you do it if you feel it helps you show what you're doing
//    
//////////////////////////////////////////////////////////////////////////
int main( void )
{
	CEventManager::CreateEventManager();

	CTestObject testObject = CTestObject();

	CEventManager::GetEventManger()->CallEventVariadic( "Callback test", 100 );
	CEventManager::GetEventManger()->CallEventVariadic( "Callback test", 100, 1.1 );
	CEventManager::GetEventManger()->CallEventVariadic( "Callback test", 100, 103.1231f, 2.1 );
	CEventManager::GetEventManger()->CallEventVariadic( "Callback test", 100, false, 102.12f, 2.3 );

	CEventManager::DeleteEventManager();

	cin.get();

	return 0;
}