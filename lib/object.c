#include "object.h"

void updateObject( object o ){
	o.pos = (point) vectorSum( (vector)o.pos, (vector)o.vel );
	o.vel = (velocity) vectorSum( (vector)o.vel, (vector)o.acc );
}
