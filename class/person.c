/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "../lib/object.h"
#include "../lib/physics.h"
#include "person.h"
#include "../lib/class.h"
#include "../lib/objecttable.h"

/* Funcoes privadas. */

person personCreate(texture tex, point pos, velocity vel)
{
    return objectCreate(TYPE_PERSON, 0, pos, vel, PERSON_RADIUS, tex);
}

void generatePosAndVelInBorder(double speed, point * pos, velocity * vel)
{
    double dir;
    /*Dir determina a primeira direcao do passageiro de modo que ele nao saia imediatamente da tela */

    switch (randInt(1, 4)) {
    case 1:
        pos->x = 0;
        pos->y = randDouble(0, MAX_Y);
        dir = -PI / 2;
        break;
    case 2:
        pos->x = MAX_X;
        pos->y = randDouble(0, MAX_Y);
        dir = PI / 2;
        break;
    case 3:
        pos->x = randDouble(0, MAX_X);
        pos->y = 0;
        dir = 0;
        break;
    case 4:
        pos->x = randDouble(0, MAX_X);
        pos->y = MAX_Y;
        dir = PI;
        break;
    default:
        genError
            ("Erro em personNew: numero aleatorio nao esta entre 1 e 4\n");
    }
    *vel =
        vectorPolarToCartesian(vectorCreate
                               (randomizeAround(speed, STD_DIST),
                                dir + PI / 4 * randInt(0, 4)));
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
    generatePosAndVelInBorder(speed, &pos, &vel);
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

void personMoveToRandomBorder(person p, objectTable table)
{
	do{
		//generatePosAndVelInBorder(vectorLength(p->vel), &p->pos, &p->vel);
		generatePosAndVelInBorder(table->config->defaultSpeed, &p->pos, &p->vel);
		p->quadrante = quadSet(p->pos.x/QUAD_SIZE_X, p->pos.y/QUAD_SIZE_Y);
	} while( objectTableIsObjectColliding(table, p) );
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
    printf("\n");
}

person personAddNewToTable(objectTable table, double speed)
{
  person p = personNew(createTexture(randInt(40,200), randInt(40,200), randInt(40,200), TEX_CIRCLE), speed);
  int err;
  do {
    err = objectTableAddObject(table, p);
    if (err == ERROR_OBJECT_LIMIT_EXCEEDED) {
      personRemove(p);
      return NULL;
    } else if (err == ERROR_OBJECT_IS_COLLIDING) {
      generatePosAndVelInBorder(speed, &p->pos, &p->vel);
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


/*person personCreateToTable(objectTable table, point pos, velocity vel)
{
  person aux, p;
  aux = 
    personCreate(createTexture(randInt(40,200), randInt(40,200), randInt(40,200), TEX_CIRCLE), pos, vel);
  p = objectTableAddObject(table, aux);
  if (p == ERROR_OBJECT_LIMIT_EXCEEDED)
    personRemove(aux);
  return p;
  }*/

void personCollide(person per, object other, double timedif) {
	vector distance, nextPos;
	double distanceAngle, velAngle, halfCoralSize;
	switch( other->type ) {
		case TYPE_PERSON:
			//angOfCol=vectorAngle(vectorSub(per->pos, other->pos));
			if( vectorLength(other->prevSpeed) != 0 ) {
				/* segunda colisao */
				per->vel = /*vectorRotate(*/other->prevSpeed/*,angOfCol)*/;
				//per->vel.x = (per->vel.x + other->prevSpeed.x)*sin(angOfCol);///2;
				//per->vel.y = (per->vel.y + other->prevSpeed.y)*cos(angOfCol);///2;
				//other->prevSpeed = vectorLengthSet(other->prevSpeed, 0);
				other->prevSpeed = vectorCreate(0,0);
			} else {
				/* primeira colisao */
				per->prevSpeed = per->vel;
				per->vel = /*VectorRotate(*/other->vel/*, angOfCol)*/;
				//per->vel.x = (per->vel.x + other->vel.x)*sin(angOfCol);///2;
				//r->vel.y = (per->vel.y + other->vel.y)*cos(angOfCol);///2;
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

			/*
			per->vel.x *= -1;
			per->vel.y *= -1;
				*/
			/*
				if((per->pos.x + per->radius >= other->pos.x - (other->radius*SQRT_2/2)) ^ (per->pos.x - per->radius <= other->pos.x + (other->radius*SQRT_2/2)))
				//if(abs(per->pos.x - other->pos.x) >= abs(per->pos.y - other->pos.y))
					per->vel.x *= -1;
				if((per->pos.y + per->radius >= other->pos.y - (other->radius*SQRT_2/2)) ^ (per->pos.y - per->radius <= other->pos.y + (other->radius*SQRT_2/2)))
				//if(abs(per->pos.y - other->pos.y) >= abs(per->pos.x - other->pos.x))
					per->vel.y *= -1; */
			break;
		case TYPE_BOAT:
			/* TODO(personCollide): mandar objectTable remover essa pessoa. Problema: consiguir a table. */
		default:
			debugMsg("Erro (Person): colisao com objeto de tipo desconhecido.");
	}
}
  
