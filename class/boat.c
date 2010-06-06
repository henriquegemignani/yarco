/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/vector.h"
#include <math.h>

#define MAXTURN (PI/2)
#define ACCEL 5000
#define MAXSPEED 50
#define IDLEACCEL 5
#define FRICTION 10
#define DEFAULT_TIME_STUCK 5
#define DEFAULT_LIVES 3

struct Extra {
  int isAccel;
  double accel;
  double friction;
  double isTurning;
  velocity prevVel;
  int life;
  int defaultLives;
  double timeStuckLeft;
  double defaultTimeStuck;
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
	b->extra->accel = ACCEL;
	b->extra->life = b->extra->defaultLives = DEFAULT_LIVES;
	b->extra->friction = FRICTION;
	b->extra->isTurning=randInt(-1,1);
	b->extra->defaultTimeStuck = DEFAULT_TIME_STUCK;
	return b;
}

void boatGeneratePosAndVelInBorder(double speed, point * pos, velocity * vel){
	double dir;
	generatePosInBorder(pos, &dir);
	*vel =
	        vectorPolarToCartesian(
	                               randDouble(0, speed),
	                                dir + PI / 4 * randInt(0, 4));
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
	if(b->extra->life <= 0){
		b->extra->timeStuckLeft -= timedif;
		if(b->extra->timeStuckLeft <=0){
			b->extra->life = b->extra->defaultLives;
			boatGeneratePosAndVelInBorder(MAXSPEED, &b->pos, &b->vel);
		}
	}
  if(!keepDir){
    b->extra->isTurning = randInt(0, 2)-1;
    /*b->extra->isTurning = 0;*/
    b->extra->isAccel = randInt(0, 2)-1;
    /*b->extra->isAccel = 1;*/
  }
  debugOp(b->tex.color = 0x808080 + b->extra->isAccel* 0x303030);
  if(b->extra->isAccel){
	  /*
	  b->acc = vectorPolarToCartesian(b->extra->accel * b->extra->isAccel, b->dir);
	  */
	  b->acc.x = -cos(b->dir)*b->extra->accel*b->extra->isAccel;
	  b->acc.y = -sin(b->dir)*b->extra->accel*b->extra->isAccel;
	  debugMsg("preatrito");
	  debugDouble("b->acc.x", b->acc.x);
	  debugDouble("b->acc.y", b->acc.y);
  }
  else
	  b->acc = vectorCreate(0,0);
  /*
  debugDouble("aceleracao", vectorLength(b->acc));
  debugDouble("vectorLength(b->vel)*b->extra->friction", vectorLength(b->vel)*b->extra->friction)
  debugDouble("vectorLength(b->vel)",vectorLength(b->vel))
  */
  debugMsg("posatrito");
  debugDouble("b->vel.x", b->vel.x);
  debugDouble("b->vel.y", b->vel.y);

  debugDouble("b->acc.x", b->acc.x);
  debugDouble("b->acc.y", b->acc.y);

  
  b->acc.x =  b->acc.x - b->vel.x*b->extra->friction;
  b->acc.y =  b->acc.y - b->vel.y*b->extra->friction;
  
  b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
  b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
  b->dir += b->extra->isTurning * MAXTURN * timedif;
  /*
  if(vectorLength(b->vel)>b->extra->maxSpeed){
  genWarning("Aviso: Velocidade do barco superior a velocidade maxima\n");
  */


}

void boatRemove(boat b){
  free(b->extra);
  free(b);
}

void boatCollide(boat b, object o, double timediff){
  switch(o->type){
  case TYPE_BOAT: 
	 	if(vectorLength(o->extra->prevVel) != 0)
		{
			b->vel=o->extra->prevVel;
			o->extra->prevVel = vectorCreate(0, 0);
		}	
		else
		{
			b->extra->prevVel = b->vel;
			b->vel=o->vel;
		}	
	break;
  case TYPE_CORAL:
   	b->extra->life--;
   if(b->extra->life == 0){
		b->extra->life=-1;
		b->vel.x=0;
		b->vel.y=0;
		/*adicoes bem-vindas*/
		b->extra->timeStuckLeft = b->extra->defaultTimeStuck;
   }	   
	break;
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

void boatOB(boat b){
  if(b->pos.x< 0 || b->pos.x > MAX_X){
    b->vel.x = -b->vel.x;
    b->pos.x = (b->pos.x <0? 0: MAX_X);
  }
  if(b->pos.y<0 || b->pos.y> MAX_Y){
    b->vel.y = -b->vel.y;
    b->pos.y = (b->pos.y <0? 0:MAX_Y);
  }
}
boat boatAddNewToTable(int color) {
	texture tex;
	/* point p = vectorCreate(randDouble(0, MAX_X), randDouble(0, MAX_Y)); */
	boat b;
	int err;
	tex.color = color;
	tex.type = TEX_TRIANGLE;
	b = boatNew(tex, randDouble(0, MAXSPEED));
	err = objectTableAddObject(b);
	if(err == ERROR_OBJECT_LIMIT_EXCEEDED) {
		boatRemove(b);
		return NULL;
	}
	return b;
}
