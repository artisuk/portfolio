#include "EventManagerVariadic.h" 
#include "Common.h" 

void CEventManagerVariadic::Destroy( void )
{
	for( std::vector<IEventVariadic*>::iterator it = m_apEvents.begin(); it != m_apEvents.end(); ++it )
	{
		IEventVariadic* pEvent = *it;

		SafeDelete( pEvent );
	}

	m_apEvents.clear();
}

void CEventManagerVariadic::UnregisterEvent( IEventVariadic* pEvent )
{
	for( std::vector<IEventVariadic*>::iterator it = m_apEvents.begin(); it != m_apEvents.end(); ++it )
	{
		IEventVariadic* pitEvent = *it;
		if( pitEvent == pEvent )
		{
			PrintOut( "Removing an event from the system '%s'", pEvent->GetName() );

			SafeDelete( pitEvent );

			m_apEvents.erase( it );

			return;
		}
	}

	ARTIS_ASSERT( false, "The event asked to be deleted, has already been deleted or never addd" );
}