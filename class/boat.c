/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#define MAXTURN PI
#define MAXSPEED 50.0
#define IDLEACCEL 5

struct boatExtra {
  int isAccel;
  double maxSpeed;
  int life;
};

void boatUpdate(boat b, int keepDir, double timedif){
  /*Var*/
  if(!keepDir){
    b->acc.y = randDouble(-MAXTURN, MAXTURN);
    b->extra->isAccel = randInt(-1, 1);
  }
  if(b->extra->isAccel)
    b->acc = vectorPolarToCartesian(vectorCreate(b->extra->maxSpeed - objectGetSpeed(b))*isAccel, b->dir);
  else
    b->acc = vectorPolarToCartesian(vectorCreate(-objectGetSpeed(b)*IDLEACCEL, b->dir));
  b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
  b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
}

void boatRemove(boat b){
  free(b->extra);
  free(b);
}

void boatCollide(boat b, object o){
  if (o->objectType == TYPE_SHIP || TYPE_CORAL){
    /*TODO (boatCollide) : Finish this piece of shit*/
  }
}

void boatOB(boat b, objectTable table){
  if(b->pos.x< 0 || b->pos.x > MAX_X)
    b->vel.x = -b->vel.x;
  if(b->pos.y<0 || b->pos.y> MAX_Y)
    b->vel.v = -b->vel.y;
}
  
     
