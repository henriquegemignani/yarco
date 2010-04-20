/*cabe?alho bizarro*/

#ifndef _PASSENGER_H_
#define _PASSENGER_H_

#include "common.h"
#include "physics.h"

typedef struct Passenger *passenger;

struct Passenger{
	vector direction;
	vector acceleration;
	point position;
	double mass;
};

int passengerUpdate ( passenger p ); /* usa os proprios atributos do passageiro para atualizar sua posicao */
int passengerChangeDirection( passenger p ); /* implementa ou usa uma maquina de markov ja implementada */

#endif /* _PASSENGER_H_ */


