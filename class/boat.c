/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/vector.h"
#include <math.h>

#define MAXSPEED 50

struct Extra {
  int isAccel;
  int color;
  double accel;
  double friction;
  int isTurning;
  double turnRate;
  velocity prevVel;
  int life;
  int defaultLives;
  double timeStuckLeft;
  double defaultTimeStuck;
} Extra;

static struct boatDefaults{
	int turnFlag;
	int accelFlag;
	int turnValue;
	int accelValue;
	double turnRate;
	double accel;
	double friction;
	int lives;
	double timeStuck;
} boatDefaults;



void boatGetDefaults(double turnRate, double accel, double friction , int lives, double timeStuck){
	boatDefaults.turnRate = turnRate;
	boatDefaults.accel = accel;
	boatDefaults.friction = friction;
	boatDefaults.lives = lives;
	boatDefaults.timeStuck = timeStuck;
}

void boatInitializeClass()
{
    classAdd(TYPE_BOAT,
             boatUpdate,
             boatRemove,
             boatCollide,
			 boatOB,
			 boatDump);
}

boat boatCreate(texture tex, point pos, velocity vel){
	boat b;
	b= objectCreate(TYPE_BOAT, 0/*TODO (boatCreate): fix ID*/, pos, vel, BOAT_RADIUS, tex);
	AUTOMALLOC(b->extra);
	b->extra->accel = boatDefaults.accel;
	b->extra->life = b->extra->defaultLives = boatDefaults.lives;
	b->extra->friction = boatDefaults.friction;
	b->extra->turnRate = boatDefaults.turnRate;
	b->extra->defaultTimeStuck = boatDefaults.timeStuck;
	b->extra->color = b->tex.color;
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
		b->tex.color = b->extra->color/2;
		if(b->extra->timeStuckLeft <=0){
			b->extra->life = b->extra->defaultLives;
			boatGeneratePosAndVelInBorder(MAXSPEED, &b->pos, &b->vel);
			b->tex.color = b->extra->color;
		}
		return;
	}
  if(!keepDir){
		b->extra->isTurning = randInt(0, 2)-1;
    /*b->extra->isTurning = 0;*/
		b->extra->isAccel = randInt(0, 2)-1;
    /*b->extra->isAccel = 1;*/
  }
  /*
  debugOp(b->tex.color = 0x808080 + b->extra->isAccel* 0x303030);
  */
  if(b->extra->isAccel){
	  /*
	  b->acc = vectorPolarToCartesian(b->extra->accel * b->extra->isAccel, b->dir);
	  */
	  b->acc.x = -cos(b->dir)*b->extra->accel*b->extra->isAccel;
	  b->acc.y = -sin(b->dir)*b->extra->accel*b->extra->isAccel;
	  /*
	  debugMsg("preatrito");
	  debugDouble("b->acc.x", b->acc.x);
	  debugDouble("b->acc.y", b->acc.y);
	  */
  }
  else
	  b->acc = vectorCreate(0,0);
  /*
  debugDouble("aceleracao", vectorLength(b->acc));
  debugDouble("vectorLength(b->vel)*b->extra->friction", vectorLength(b->vel)*b->extra->friction)
  debugDouble("vectorLength(b->vel)",vectorLength(b->vel))
  */

  /*
  debugMsg("posatrito");
  debugDouble("b->vel.x", b->vel.x);
  debugDouble("b->vel.y", b->vel.y);

  debugDouble("b->acc.x", b->acc.x);
  debugDouble("b->acc.y", b->acc.y);
  */
  
  b->acc.x =  b->acc.x - b->vel.x*b->extra->friction;
  b->acc.y =  b->acc.y - b->vel.y*b->extra->friction;
  
  b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
  b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
  b->dir += b->extra->isTurning * b->extra->turnRate * timedif;
  /*
  if(vectorLength(b->vel)>b->extra->maxSpeed){
  genWarning("Aviso: Velocidade do barco superior a velocidade maxima\n");
  */
  b->quad = quadSet(b->pos.x/QUAD_SIZE_X, b->pos.y/QUAD_SIZE_Y);

}

void boatRemove(boat b){
  free(b->extra);
  free(b);
}

void boatCollide(boat b, object o, double timediff){
  double objectSide;
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
   	/*b->extra->life--;*/

   if(b->extra->life>0){
	objectSide = o->radius * SQRT_2/2;
			if(abs(b->pos.x - o->pos.x)<= objectSide && abs(b->pos.y - o->pos.y)<=(objectSide + b->radius)){
				b->vel.y *=-1;
				b->extra->life--;
			}
			else if(abs(b->pos.y - o->pos.y)<= objectSide && abs(b->pos.x - o->pos.x)<=(objectSide + b->radius)){
				b->vel.x *= -1;
				b->extra->life--;
			}
			else if(abs(b->pos.x - o->pos.x)>=objectSide && abs(b->pos.y - o->pos.y) >= objectSide){
				b->vel.x *=-1;
				b->vel.y *= -1;
				b->extra->life--;
			}
			if(b->extra->life <=0){
				/*
					b->extra->life=-1;
					*/
					b->vel.x=0;
					b->vel.y=0;
					/*adicoes bem-vindas*/
					b->extra->timeStuckLeft = b->extra->defaultTimeStuck;
			   }
   }
	break;
  case TYPE_SHIP:
	  objectSide = o->radius/SQRT_5;

	  /*
	  if((b->pos.x+b->radius) > (o->pos.x-(2*(o->radius/SQRT_5))) && b->pos.x < (o->pos.x+(2*(o->radius/SQRT_5)) ) )
	  b->vel.x*=-1;
	  if( (b->pos.y+b->radius) > (o->pos.y-(o->radius/SQRT_5)) && b->pos.y < (o->pos.y+(o->pos.y/SQRT_5)))
	  	b->vel.y*=-1;
	  */
		  if(abs(b->pos.x - o->pos.x)<= 2*objectSide && abs(b->pos.y - o->pos.y)<=(objectSide + b->radius)){
		  				b->vel.y *=-1;
		  			}
		  			else if(abs(b->pos.y - o->pos.y)<= objectSide && abs(b->pos.x - o->pos.x)<=(2*objectSide + b->radius)){
		  				b->vel.x *= -1;
		  			}
		  			else if(abs(b->pos.x - o->pos.x)>=2*objectSide && abs(b->pos.y - o->pos.y) >= objectSide){
		  				b->vel.x *=-1;
		  				b->vel.y *= -1;
		  			}
		  break;
  case TYPE_PERSON: break;
  default: genWarning("Colisao de barco com tipo desconhecido!\n");
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


void boatDump(boat b){
	printf("Bote:\n\n");
	objectDump(b);
	printf("Virando: %s\n", b->extra->isTurning==0?"Nao":b->extra->isTurning<0?"Sentido horario":"Sentido anti-horario");
	printf("Acelerando: %s\n", b->extra->isAccel==0?"Nao":b->extra->isTurning<0?"Para tras":"Para frente");
}
