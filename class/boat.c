/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#define MAXTURN PI
#define MAXSPEED 50.0
#define IDLEACCEL 5

struct Extra {
  int isAccel;
  double maxSpeed;
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

boat boatCreate(texture tex, point pos){
	boat b;
	b= objectCreate(TYPE_BOAT, 0/*TODO (boatCreate): fix ID*/, pos, vectorCreate(0,0), BOAT_RADIUS, tex);
	AUTOMALLOC(b->extra);
	return b;
}

void boatUpdate(boat b, int keepDir, double timedif){
  /*Var*/
  if(!keepDir){
    b->acc.y = randDouble(-MAXTURN, MAXTURN);
    b->extra->isAccel = randInt(-1, 1);
  }
  if(b->extra->isAccel)
    b->acc = vectorPolarToCartesian(vectorCreate(b->extra->maxSpeed - objectGetSpeed(b)*b->extra->isAccel, b->dir));
  else
    b->acc = vectorPolarToCartesian(vectorCreate(-objectGetSpeed(b)*IDLEACCEL, b->dir));
  b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
  b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
}

void boatRemove(boat b){
  free(b->extra);
  free(b);
}

void boatCollide(boat b, object o, double timedif){
  switch(o->type){
  case TYPE_BOAT: /*TODO (boatCollide): Colisao barco-barco*/; break;
  case TYPE_CORAL: b->extra->life--;
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
  if(b->pos.x< 0 || b->pos.x > MAX_X)
    b->vel.x = -b->vel.x;
  if(b->pos.y<0 || b->pos.y> MAX_Y)
    b->vel.y = -b->vel.y;
}
  
boat boatAddNewToTable(objectTable table, int color) {
	texture tex;
	point p = vectorCreate(randDouble(0, MAX_X), randDouble(0, MAX_Y));
	boat b;
	int err;
	tex.color = color;
	tex.type = TEX_TRIANGLE;
	b = boatCreate(tex, p);
	err = objectTableAddObject(table, b);
	if(err == ERROR_OBJECT_LIMIT_EXCEEDED) {
		boatRemove(b);
		return NULL;
	}
	return b;
}
