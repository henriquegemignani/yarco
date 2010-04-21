#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "common.h"

typedef struct Object object;

struct Object
{
	acceleration acc;
	velocity vel;
	point pos;
};

void updateObject( object o );

#endif /* _OBJECT_H_ */
