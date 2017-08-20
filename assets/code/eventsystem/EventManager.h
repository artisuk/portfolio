#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include "EventManagerVariadic.h"

class CEventManager
	: public CEventManagerVariadic
{
private:
	static CEventManager* sm_pEventManager;

public:
	CEventManager( void );
	virtual ~CEventManager( void );

	void Destroy(void);

	//////////////////////////////////////////////////////////////////////////
	// inline static functions
	static inline CEventManager* GetEventManger( void );
	static CEventManager* CreateEventManager( void );
	static void DeleteEventManager( void );
};

CEventManager* CEventManager::GetEventManger( void )
{
	return sm_pEventManager;
}

#endif // _EVENTMANAGER_H_