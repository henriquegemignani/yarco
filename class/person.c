/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "person.h"
#include "../lib/common.h"
#include "../lib/vector.h"
#include "../lib/objecttable.h"
#include "../lib/class.h"
#include "../lib/configuration.h"

/* Funcoes privadas. */

vector newDirection(vector v)
{
    int randNum;
    if ((randNum = randInt(1, 20)) > 13)        /*13/20 = 0.65 de chance de nao mudar, 1/20 = 0.05 para cada outra direcao */
        v = vectorRotate(v, PI / 4 * (randNum - 13));
    return v;
}

person personCreate(texture tex, point pos, velocity vel)
{
    return objectCreate(TYPE_PERSON, 0, pos, vel, PERSON_RADIUS, tex);
}

void personGeneratePosAndVelInBorder(double speed, point * pos, velocity * vel)
{
    double dir;
    generatePosInBorder(pos, &dir);
    *vel =
        vectorPolarToCartesian(
                               randomizeAround(speed, STD_DIST),
                                dir + PI / 4 * randInt(0, 4));
}

/* Funcoes publicas. */

void personInitializeClass()
{
    classAdd(TYPE_PERSON,
             personUpdate,
             removeObject,
             personCollide,
			 personMoveToRandomBorder,
			 objectDump);
}

person personNew(texture tex, double speed)
{
    point pos;
    velocity vel;
    personGeneratePosAndVelInBorder(speed, &pos, &vel);
    return personCreate(tex, pos, vel);
}


void personRemove(person p)
{
    free(p);
}

void personUpdate(person p, int keepDir, double timedif)
{
    if (!keepDir)
        p->vel = newDirection(p->vel);
    updateObject(p, timedif);
}

void personMoveToRandomBorder(person p)
{
	do{
		personGeneratePosAndVelInBorder(configurationGet()->defaultSpeed, &p->pos, &p->vel);
		p->quadrante = quadSet(p->pos.x/QUAD_SIZE_X, p->pos.y/QUAD_SIZE_Y);
	} while( objectTableIsObjectColliding(p) );
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
    printf("\n");
}

person personAddNewToTable(double speed)
{
  person p = personNew(createTexture(randInt(40,200), randInt(40,200), randInt(40,200), TEX_CIRCLE), speed);
  int err;
  do {
    err = objectTableAddObject(p);
    if (err == ERROR_OBJECT_LIMIT_EXCEEDED) {
      personRemove(p);
      return NULL;
    } else if (err == ERROR_OBJECT_IS_COLLIDING) {
      personGeneratePosAndVelInBorder(speed, &p->pos, &p->vel);
    }
    if( err != 0 ) {
      printf("Tentando criar pessoa. Err = %d", err );
      vectorPrint(p->pos);
      vectorPrint(p->vel);
      printf("\n");
    }
  } while( err != 0 );
  return p;
}

void personCollide(person per, object other, double timedif) {
	/* vector distance, nextPos; */
	double /*distanceAngle, velAngle, */halfCoralSize;
	switch( other->type ) {
		case TYPE_PERSON:
			/* angOfCol=vectorAngle(vectorSub(per->pos, other->pos)); */
			if( vectorLength(other->prevSpeed) != 0 ) {
				/* segunda colisao */
				per->vel = other->prevSpeed;
				other->prevSpeed = vectorCreate(0,0);
			} else {
				/* primeira colisao */
				per->prevSpeed = per->vel;
				per->vel = other->vel;
			}
			break;
		case TYPE_SHIP:
			if((per->pos.x+per->radius) > (other->pos.x-other->radius) && per->pos.x < (other->pos.x+(3*other->radius)) )
				per->vel.x*=-1;
			if( (per->pos.y+per->radius) > (other->pos.y-other->radius) && per->pos.y < (other->pos.y+other->pos.y) )
				per->vel.y*=-1;
			break;
		case TYPE_CORAL:
			halfCoralSize = other->radius * SQRT_2/2;
			if(abs(per->pos.x - other->pos.x)<= halfCoralSize && abs(per->pos.y - other->pos.y)<=(halfCoralSize + per->radius))
				per->vel.y *=-1;
			else if(abs(per->pos.y - other->pos.y)<= halfCoralSize && abs(per->pos.x - other->pos.x)<=(halfCoralSize + per->radius))
				per->vel.x *= -1;
			else if(abs(per->pos.x - other->pos.x)>=halfCoralSize && abs(per->pos.y - other->pos.y) >= halfCoralSize){
				per->vel.x *=-1;
				per->vel.y *= -1;
			}
			break;
		case TYPE_BOAT:
			/* TODO(personCollide): mandar objectTable remover essa pessoa. Problema: consiguir a table. */
			/* personAddNewToTable(vectorLength(per->vel)); */
			objectTableRemoveObject(per);
			debugMsg("OH NEOS PERSON COLIDIU COM BARCO!!");
			
			break;
		default:
			debugMsg("Erro (Person): colisao com objeto de tipo desconhecido.");
	}
}
  
