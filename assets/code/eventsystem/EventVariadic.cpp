#include "EventVariadic.h"
#include <string>
#include "Common.h"


IEventVariadic::IEventVariadic( const char* pszName, bool bMember )
	: m_bMember( bMember )
{
	strcpy_s( m_pszName, sizeof( m_pszName ), pszName );
}

IEventVariadic::~IEventVariadic()
{
	SafeDeleteArray( m_aIDs );
	m_uSize = 0;
}