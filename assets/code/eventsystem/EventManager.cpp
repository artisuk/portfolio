#include "EventManager.h" 
#include "Common.h"

CEventManager* CEventManager::sm_pEventManager = nullptr;

CEventManager::CEventManager( void )
{}

CEventManager::~CEventManager( void )
{}

void CEventManager::Destroy( void )
{
	CEventManagerVariadic::Destroy();
}

CEventManager* CEventManager::CreateEventManager( void )
{
	ARTIS_ASSERT( !sm_pEventManager, "This should be null before making a new instance of event manager" );

	sm_pEventManager = new CEventManager;
	return sm_pEventManager;
}

void CEventManager::DeleteEventManager( void )
{
	sm_pEventManager->Destroy();
	SafeDelete( sm_pEventManager );
}