/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/vector.h"

#define MAXTURN (PI/2)
#define MAXSPEED 100
#define IDLEACCEL 0.5

struct Extra {
  int isAccel;
  double maxSpeed;
  double idleAccel;
  double isTurning;
  int life;
} Extra;


void boatInitializeClass()
{
    classAdd(TYPE_BOAT,
             boatUpdate,
             boatRemove,
             boatCollide,
			 boatOB,
			 objectDump);
}

boat boatCreate(texture tex, point pos, velocity vel){
	boat b;
	b= objectCreate(TYPE_BOAT, 0/*TODO (boatCreate): fix ID*/, pos, vel, BOAT_RADIUS, tex);
	AUTOMALLOC(b->extra);
	b->extra->isAccel=randInt(-1,1);
	b->extra->maxSpeed = MAXSPEED;
	b->extra->life = 3;
	b->extra->idleAccel = IDLEACCEL;
	b->extra->isTurning=randInt(-1,1);
	return b;
}

void boatGeneratePosAndVelInBorder(double speed, point * pos, velocity * vel){
	double dir;
	generatePosInBorder(pos, &dir);
	*vel =
	        vectorPolarToCartesian(vectorCreate
	                               (randDouble(0, speed),
	                                dir + PI / 4 * randInt(0, 4)));
}

boat boatNew(texture tex, double speed)
{
    point pos;
    velocity vel;
    boat b;
    boatGeneratePosAndVelInBorder(speed, &pos, &vel);
    b = boatCreate(tex, pos, vel);
    b->dir = vectorAngle(b->vel);
	return b;
}


void boatUpdate(boat b, int keepDir, double timedif){
  /*Var*/
  if(!keepDir){
    b->extra->isTurning = randInt(0, 2)-1;
    b->extra->isAccel = randInt(0, 2)-1;
  }
	b->tex.color = 0x808080 + b->extra->isAccel* 0x303030;
  if(b->extra->isAccel){
	/* b->acc = vectorPolarToCartesian(vectorCreate(b->extra->maxSpeed - objectGetSpeed(b)*b->extra->isAccel, b->dir));*/
	  b->acc = vectorPolarToCartesian(
		vectorCreate(
			(abs(b->extra->maxSpeed) - abs(vectorLength(b->vel) )) * b->extra->isAccel,
			b->dir)
		);


          debugDouble("Velocidade do barco acelerando: ",vectorLength(b->vel));
  		  debugDouble("Aceleracao do barco acelerando: ",vectorLength(b->acc));
  }
  else
	  if(vectorLength(b->vel)>0){/*
		  b->acc = vectorPolarToCartesian(
			vectorCreate(
				-abs((vectorLength(b->vel) * b->extra->idleAccel)),
				vectorAngle(b->vel))
				);
				*/
		  b->acc.x = b->extra->idleAccel * b->vel.x * -1;
		  b->acc.y = b->extra->idleAccel * b->vel.y * -1;
		  debugDouble("Velocidade do barco nao acelerando: ",vectorLength(b->vel));
		  debugDouble("Aceleracao do barco nao acelerando: ",vectorLength(b->acc));
	  }
  b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
  b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
  b->dir += b->extra->isTurning * MAXTURN * timedif;
  if(vectorLength(b->vel)>b->extra->maxSpeed){
  genWarning("Aviso: Velocidade do barco superior a velocidade maxima\n");
  }

}

void boatRemove(boat b){
  free(b->extra);
  free(b);
}

void boatCollide(boat b, object o, double timedif){
  switch(o->type){
  case TYPE_BOAT: /*TODO (boatCollide): Colisao barco-barco*/; break;
  case TYPE_CORAL: b->extra->life--; break;
  case TYPE_SHIP:
	  if((b->pos.x+b->radius) > (o->pos.x-o->radius) && b->pos.x < (o->pos.x+(3*o->radius)) )
	  	b->vel.x*=-1;
	  if( (b->pos.y+b->radius) > (o->pos.y-o->radius) && b->pos.y < (o->pos.y+o->pos.y) )
	  	b->vel.y*=-1;
	  ; break;
  case TYPE_PERSON: break;
  default: debugMsg("Colisao de barco com tipo desconhecido!\n")
  }
}

void boatOB(boat b, objectTable table){
  if(b->pos.x< 0 || b->pos.x > MAX_X){
    b->vel.x = -b->vel.x;
    b->pos.x = (b->pos.x <0? 0: MAX_X);
  }
  if(b->pos.y<0 || b->pos.y> MAX_Y){
    b->vel.y = -b->vel.y;
    b->pos.y = (b->pos.y <0? 0:MAX_Y);
  }
}
boat boatAddNewToTable(objectTable table, int color) {
	texture tex;
	/* point p = vectorCreate(randDouble(0, MAX_X), randDouble(0, MAX_Y)); */
	boat b;
	int err;
	tex.color = color;
	tex.type = TEX_TRIANGLE;
	b = boatNew(tex, randDouble(0, MAXSPEED));
	err = objectTableAddObject(table, b);
	if(err == ERROR_OBJECT_LIMIT_EXCEEDED) {
		boatRemove(b);
		return NULL;
	}
	return b;
}
