#include "common.h"
#include "passenger.h"

int passengerUpdate( passenger p ){

	return 1;
}

int passengerChangeDirection( passenger p )
{

	return 1;
}

crew initializeCrew( int size ){
	crew c;
	int i;
	c = malloc( size * sizeof(passenger) );
	for( i=0; i<size; i++)
		c[i] = malloc(sizeof(struct Passenger));
	return c;
}
