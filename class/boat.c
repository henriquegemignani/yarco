/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/vector.h"
#include <math.h>
#include <allegro.h>
#include <allegro/keyboard.h>

#define MAXSPEED 50
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define ACCEL_BUTTON 0
#define BRAKE_BUTTON 1
#define TURN_RIGHT_BUTTON 2
#define TURN_LEFT_BUTTON 3
#define ANCHOR_BUTTON 4



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
    int keyLayout[];
} Extra;

/*Guarda os valores padrao dos botes, ja que podem ser definidos via linha de comando*/
static struct boatDefaults {
    double turnRate;
    double accel;
    double friction;
    int lives;
    double timeStuck;
} boatDefaults;

static int curPlayer = PLAYER_ONE; /*<_<*//*Guarda qual jogador esta sendo criado no momento*/

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
    b->extra->keyLayout[TURN_RIGHT_BUTTON] = KEY_A;
    b->extra->keyLayout[TURN_LEFT_BUTTON] = KEY_D;
    b->extra->keyLayout[ANCHOR_BUTTON] = KEY_Q;

}

boat boatNew(texture tex, double speed)
{
    point pos;
    velocity vel;
    boat b;

    //boatGeneratePosAndVelInBorder(speed, &pos, &vel);
    b = boatCreate(tex, pos, vel);
    b->pos.y = (double)MAX_Y/2;
    b->pos.x = (double)MAX_X/4 + (double)curPlayer * (double)MAX_X/2;
    b->dir = PI/2;
    b->extra->player = curPlayer;
    boatGetControls(b, curPlayer);
    if(curPlayer == PLAYER_ONE)
        curPlayer = PLAYER_TWO;
    //else
    //    genError("Erro: Mais de dois botes gerados!\n");
    return b;
}

/*Funcoes publicas*/

void boatGetDefaults(double turnRate, double accel, double friction,
                     int lives, double timeStuck)
{
    boatDefaults.turnRate = turnRate;
    boatDefaults.accel = accel;
    boatDefaults.friction = friction;
    boatDefaults.lives = lives;
    boatDefaults.timeStuck = timeStuck;
}


void boatInitializeClass()
{
    classAdd(TYPE_BOAT,
             boatUpdate, boatRemove, boatCollide, boatOB, boatDump);
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
    return b;
}

void boatReadKeyboard(boat b)
{
 //pisseudo codigo ahead. TODO: Diferenciar botes
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
    if(key[b->extra->keyLayout[ANCHOR_BUTTON]])
        b->extra->isAnchored = !b->extra->isAnchored;
}

void boatUpdate(boat b, int keepDir, double timedif)
{
    if (b->extra->life <= 0) {  /*Se o barco esta encalhado */
        b->extra->timeStuckLeft -= timedif;
        b->tex.color = b->extra->color / 2;     /*Torna o bote mais escuro - note que
                                                   os valores para R e G sempre sao pares para lidar com isso */
        if (b->extra->timeStuckLeft <= 0) {
	  if(b->extra->life >= 0){
	  //      b->extra->life = b->extra->defaultLives;
            boatGeneratePosAndVelInBorder(MAXSPEED, &b->pos, &b->vel);
            b->tex.color = b->extra->color;     /*Retornando a cor original,
						  ja que o bote muda de cor quando encalhado */
	  }
	  else
	    boatRemove(b);
        }
        return;
    }
    boatReadKeyboard(b);
    b->acc.x = b->acc.x - b->vel.x * b->extra->friction;
    b->acc.y = b->acc.y - b->vel.y * b->extra->friction;
    if(b->extra->isAnchored)
    	vectorMulDouble(b->acc, 10);
    b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
    b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
    b->dir += b->extra->isTurning * b->extra->turnRate * timedif;
    objectQuadUpdate(b);
}

void boatRemove(boat b)
{
    free(b->extra);
    free(b);
}

void boatPersonFree(boat b){
    return;
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
       if (abs(b->pos.x - o->pos.x) <= objectSide
            && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius) || abs(b->pos.y - o->pos.y) <= objectSide
                    && abs(b->pos.x - o->pos.x) <=
                     (objectSide + b->radius) || (abs(b->pos.x - o->pos.x) >= objectSide
                  && abs(b->pos.y - o->pos.y) >= objectSide)  )
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

boat boatAddNewToTable(int color)
{
    texture tex;
    boat b;
    int err;
    tex.color = color;
    tex.type = TEX_TRIANGLE;
    b = boatNew(tex, randDouble(0, MAXSPEED));
    err = objectTableAddObject(b);
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
