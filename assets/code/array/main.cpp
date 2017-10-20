#include "StaticArrayNested.h"


int main()
{
	const int x = 10;
	const int y = 11;
	const int z = 12;

	TStaticArrayNested<int, x, y, z> cNestedArray( 1 ); 

	return 0;
}
