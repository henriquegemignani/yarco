/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/vector.h"
#include "../config/configuration.h"
#include <math.h>
#include <allegro.h>

#define MAXSPEED 50
#define ANCHOR_MULTIPLIER 10
#define BOAT_PEOPLE_LIMIT 10
#define UNLOAD_TIME 1
#define BOAT_RESCUE_DIST 120
#define PERSON_UNLOAD_TIME 1
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define NUM_BUTTONS 5
#define ACCEL_BUTTON 0
#define BRAKE_BUTTON 1
#define TURN_RIGHT_BUTTON 2
#define TURN_LEFT_BUTTON 3
#define ANCHOR_BUTTON 4

typedef struct objectList *listLink;

struct objectList{
    object person;
    listLink next;
};

static point shipPos;

struct Extra {
    int isAccel;                /*Verifica se esta acelerando, e em qual direcao: 1 para frente, -1 para tras e 0 caso nao acelere */
    int color;                  /*Cor usual do bote - guardado uma vez que boat->tex.color nao e constante */
    double accel;               /*Aceleracao do bote, seja para frente ou para tras */
    double friction;            /*Desaceleracao devida ao atrito */
    int isTurning;              /*Verifica se esta virando, e para qual lado -  -1: sentido horario, 1: sentido anti-horario */
    double turnRate;            /*Quanto o bote pode virar em um segundo, em radianos */
    velocity prevVel;           /*Velocidade anterior, para colisoes com outros botes */
    int life;
    //int defaultLives;           /*Numero padrao de vidas */ /*Nao sera mais necessario, ja que uma vez que o barquinho morre, nunca mais volta*/
    double timeStuckLeft;       /*Quanto tempo falta para o barquinho encalhado dar respawn */
    double defaultTimeStuck;    /*Tempo que ele demora para dar respawn apos encalhar */
    int isAnchored;
    int player;
    int keyLayout[NUM_BUTTONS];
    int anchorButtonHeld;
    listLink personList;
    int peopleHeld;
    int points;
    double unloadTimeLeft;
    point respawnPoint;
};

/*Guarda os valores padrao dos botes, ja que podem ser definidos via linha de comando*/
static struct boatDefaults {
    double turnRate;
    double accel;
    double friction;
    int lives;
    double timeStuck;
} boatDefaults;

void getShipPos(point p)
{
    shipPos = p;
}

/*Funcoes privadas*/
void boatGeneratePosAndVelInBorder(double speed, point * pos,
                                   velocity * vel)
{
    double dir;
    generatePosInBorder(pos, &dir);
    *vel =
        vectorPolarToCartesian(randDouble(0, speed),
                               dir + PI / 4 * randInt(0, 4));
}

void boatGetControls(boat b, int player)
{
    //TempCode
    b->extra->keyLayout[ACCEL_BUTTON] = KEY_W;
    b->extra->keyLayout[BRAKE_BUTTON] = KEY_S;
    b->extra->keyLayout[TURN_RIGHT_BUTTON] = KEY_D;
    b->extra->keyLayout[TURN_LEFT_BUTTON] = KEY_A;
    b->extra->keyLayout[ANCHOR_BUTTON] = KEY_Q;

}

boat boatNew(int player)
{
    point pos = vectorCreate((double)MAX_X/4 + (double)player * (double)MAX_X/2, (double)MAX_Y/2);
    velocity vel = vectorCreate(0,0);
    boat b;
	texture tex;

	char confgroup[8];
	strcpy(confgroup, "PlayerX");
	confgroup[6] = '1' + player;
	
    tex.color = configGetValue(confgroup, "Color").num;
    tex.type = TEX_TRIANGLE;
    b = boatCreate(tex, pos, vel);
    b->dir = PI/2;
    b->extra->player = player;
    boatGetControls(b, player);
    b->extra->respawnPoint = b->pos;
    return b;
}

/*Funcoes publicas*/

int boatFullOrCrashed(boat b)
{
    return (b->extra->peopleHeld >= BOAT_PEOPLE_LIMIT || b->extra->timeStuckLeft > 0);
}

void boatPointAdd(boat b, int point)
{
    b->extra->points += point;
}

void boatRetrievePerson(boat b, object o)
{
    listLink newLink;
    AUTOMALLOC(newLink);
    newLink->person = o;
    newLink->next = b->extra->personList;
    b->extra->personList = newLink;
    b->extra->peopleHeld++;
    debugMsg("entra em retireve person");
}

void boatInitializeClass()
{
    classAdd(TYPE_BOAT,
             boatUpdate, boatRemove, boatCollide, boatOB, boatDump);
	
    boatDefaults.turnRate = configGetValue("Gameplay", "TurnRate").real;
    boatDefaults.accel = 	configGetValue("Gameplay", "Acceleration").real;
    boatDefaults.friction = configGetValue("Gameplay", "Friction").real;
    boatDefaults.lives =    configGetValue("Gameplay", "InitialLives").num;
    boatDefaults.timeStuck = configGetValue("Gameplay", "TimeStuck").num;
}

boat boatCreate(texture tex, point pos, velocity vel)
{
    boat b;
    b = objectCreate(TYPE_BOAT, 0, pos, vel, BOAT_RADIUS, tex);
    AUTOMALLOC(b->extra);
    b->extra->accel = boatDefaults.accel;
    b->extra->life = /*b->extra->defaultLives =*/ boatDefaults.lives;
    b->extra->friction = boatDefaults.friction;
    b->extra->turnRate = boatDefaults.turnRate;
    b->extra->defaultTimeStuck = boatDefaults.timeStuck;
    b->extra->color = b->tex.color;
    b->extra->isAnchored = 0;
    b->extra->isTurning = 0;
    b->extra->isAccel = 0;
    b->extra->anchorButtonHeld = 0;
    b->extra->peopleHeld = 0;
    b->extra->points = 0;
    b->extra->unloadTimeLeft = UNLOAD_TIME;
    b->extra->personList = NULL;
    return b;
}

void boatReadKeyboard(boat b)
{
 //TODO: Diferenciar botes
    b->extra->isAccel = 0;
    b->extra->isTurning = 0;
    if(key[b->extra->keyLayout[ACCEL_BUTTON]])
        b->extra->isAccel +=1;
    if(key[b->extra->keyLayout[BRAKE_BUTTON]])
        b->extra->isAccel -= 1;
    if(key[b->extra->keyLayout[TURN_RIGHT_BUTTON]])
        b->extra->isTurning += 1;
    if(key[b->extra->keyLayout[TURN_LEFT_BUTTON]])
        b->extra->isTurning -= 1;
    if(key[b->extra->keyLayout[ANCHOR_BUTTON]]){
        if(!b->extra->anchorButtonHeld){
            b->extra->isAnchored = !b->extra->isAnchored;
            b->extra->anchorButtonHeld = 1;
        }
    }
    else
        if(b->extra->anchorButtonHeld)
            b->extra->anchorButtonHeld = 0;

}

void rescuePerson(boat b)
{
    listLink aux;
    OBJECT_REMOVE(b->extra->personList->person);
    aux = b->extra->personList;
    b->extra->personList = b->extra->personList->next;
    free (aux);
    b->extra->peopleHeld--;
    b->extra->points += 50;
}

void boatUpdate(boat b, int keepDir, double timedif)
{
    double anchorRatio;
    if (b->extra->timeStuckLeft > 0) {  /*Se o barco esta encalhado */
        b->extra->timeStuckLeft -= timedif;
        b->tex.color = b->extra->color / 2;     /*Torna o bote mais escuro - note que
                                                   os valores para R e G sempre sao pares para lidar com isso */
        if (b->extra->timeStuckLeft <= 0) {
        	if(b->extra->life >= 0){
        		b->extra->timeStuckLeft = 0;
	  //      b->extra->life = b->extra->defaultLives;
        		//boatGeneratePosAndVelInBorder(MAXSPEED, &b->pos, &b->vel);
        		b->pos = b->extra->respawnPoint;
        		b->vel = vectorCreate(0,0);
        		b->acc = vectorCreate(0,0);
        		b->tex.color = b->extra->color;     /*Retornando a cor original,
						  ja que o bote muda de cor quando encalhado */
	  }
	  else
	    b->toBeRemoved = 1;
        }
        return;
    }
    boatReadKeyboard(b);
    if(b->extra->isAccel && !b->extra->isAnchored){
    	b->acc.x = -b->extra->accel * cos (b->dir) * b->extra->isAccel;
    	b->acc.y = -b->extra->accel * sin (b->dir) * b->extra->isAccel;
    }
    else
    	b->acc = vectorCreate(0,0);
    if(b->extra->isAnchored)
        anchorRatio = ANCHOR_MULTIPLIER;
    else
        anchorRatio = 1;
    b->acc.x = b->acc.x - b->vel.x * b->extra->friction * anchorRatio;
    b->acc.y = b->acc.y - b->vel.y * b->extra->friction * anchorRatio;
    b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
    b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
    if(!b->extra->isAnchored)
        b->dir += b->extra->isTurning * b->extra->turnRate * timedif;
    objectQuadUpdate(b);
    if(b->extra->isAnchored){
        if(distanceBetweenPoints(b->pos, shipPos) <= BOAT_RESCUE_DIST)
            while(b->extra->personList != NULL)
                if(b->extra->unloadTimeLeft <= 0){
                    rescuePerson(b);
                    b->extra->unloadTimeLeft = UNLOAD_TIME;
                }
                else
                    b->extra->unloadTimeLeft -= timedif;
    }
    else
        b->extra->unloadTimeLeft = UNLOAD_TIME;
}

void boatRemove(boat b)
{
    free(b->extra);
    free(b);
}

void boatPersonFree(boat b)
{
    int i, errorCode;
    listLink aux = b->extra->personList;
    double angDif = 2*PI/b->extra->peopleHeld;
    for(i=0; i< b->extra-> peopleHeld; i++){
        if(aux == NULL)
            genError("Falha de sincronia entre personList e peopleHeld! Contate um programador.");
        aux->person->pos = vectorSum(b->pos, vectorPolarToCartesian(b->radius + aux->person->radius, i*angDif));
        aux->person->vel = vectorAngleSet(aux->person->vel, angDif);
        if((errorCode = objectTableAddObject(aux->person))){
            if(errorCode == ERROR_OBJECT_LIMIT_EXCEEDED)
                genWarning("Nao foi possivel fazer a pessoa cair do bote!\n");
            if(errorCode == ERROR_OBJECT_IS_COLLIDING){
                do{
                   aux->person->pos = vectorSum(aux->person->pos, vectorMulDouble(vectorSub(aux->person->pos, b->pos), 1.5));
                }while(objectTableAddObject(aux->person) == ERROR_OBJECT_IS_COLLIDING);
            }
        }
        aux=aux->next;
    }
    for(aux=b->extra->personList; aux!=NULL;aux=b->extra->personList){
        b->extra->personList = b->extra->personList->next;
        free(aux);
        b->extra->peopleHeld--;
    }
}

void boatCrash(boat b){
  b->extra->life--;
  boatPersonFree(b);
  b->extra->timeStuckLeft = b->extra->defaultTimeStuck;
}

void boatCollide(boat b, object o, double timediff)
{
    double objectSide;          /*Variavel que guarda o tamanho de um dos lados do outro objeto, caso seja o Asimov ou um coral */
    switch (o->type) {
    case TYPE_BOAT:
        if (vectorLength(o->extra->prevVel) != 0) {
            b->vel = o->extra->prevVel;
            o->extra->prevVel = vectorCreate(0, 0);
        } else {
            b->extra->prevVel = b->vel;
            b->vel = o->vel;
        }
        break;
    case TYPE_CORAL:
    	objectSide = o->radius * SQRT_2/2;
       if (((abs(b->pos.x - o->pos.x) <= objectSide
            && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius)) ||( abs(b->pos.y - o->pos.y) <= objectSide
                    && abs(b->pos.x - o->pos.x) <=
                     (objectSide + b->radius)) ||( (abs(b->pos.x - o->pos.x) >= objectSide
                  && abs(b->pos.y - o->pos.y) >= objectSide) ) ) && b->extra->timeStuckLeft == 0 )
	 boatCrash(b);
        break;
    case TYPE_SHIP:
        objectSide = o->radius / SQRT_5;        /*Note que o retangulo e um retangulo
                                                   inscrito ao circulo de colisao */
        /*Vide comentarios para colisao com coral */
        if (abs(b->pos.x - o->pos.x) <= 2 * objectSide
            && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius)) {
            b->vel.y *= -1;
        } else if (abs(b->pos.y - o->pos.y) <= objectSide
                   && abs(b->pos.x - o->pos.x) <=
                   (2 * objectSide + b->radius)) {
            b->vel.x *= -1;
        } else if (abs(b->pos.x - o->pos.x) >= 2 * objectSide
                   && abs(b->pos.y - o->pos.y) >= objectSide) {
            b->vel.x *= -1;
            b->vel.y *= -1;
        }
        break;
    case TYPE_PERSON:
        if(!boatFullOrCrashed(b)){
            boatRetrievePerson(b, o);
            b->extra->points += 10;
            objectTableLeave(o->id);
        }
        break;
    default:
        genWarning("Colisao de barco com tipo desconhecido!\n");
    }
}

void boatOB(boat b)
{
    if (b->pos.x < 0 || b->pos.x > MAX_X) {
        b->vel.x = -b->vel.x;
        /*Coloca o bote de volta na borda */
        b->pos.x = (b->pos.x < 0 ? 0 : MAX_X);
    }
    if (b->pos.y < 0 || b->pos.y > MAX_Y) {
        b->vel.y = -b->vel.y;
        b->pos.y = (b->pos.y < 0 ? 0 : MAX_Y);
    }
    objectQuadUpdate    (b);
}

boat boatAddNewToTable(int player)
{
    boat b = boatNew(player);
    int err = objectTableAddObject(b);
    if (err == ERROR_OBJECT_LIMIT_EXCEEDED) {
        boatRemove(b);
        return NULL;
    }
    return b;
}


void boatDump(boat b)
{
    printf("Bote:\n\n");
    objectDump(b);
    printf("Virando: %s\n",
           b->extra->isTurning == 0 ? "Nao" : b->extra->isTurning <
           0 ? "Sentido anti-horario" : "Sentido horario");
    printf("Acelerando: %s\n",
           b->extra->isAccel == 0 ? "Nao" : b->extra->isTurning <
           0 ? "Para tras" : "Para frente");
    printf("Vida: %d\n", b->extra->life);
}

