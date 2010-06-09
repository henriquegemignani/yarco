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
    int isAccel;                /*Verifica se esta acelerando, e em qual direcao: 1 para frente, -1 para tras e 0 caso nao acelere */
    int color;                  /*Cor usual do bote - guardado uma vez que boat->tex.color nao e constante */
    double accel;               /*Aceleracao do bote, seja para frente ou para tras */
    double friction;            /*Desaceleracao devida ao atrito */
    int isTurning;              /*Verifica se esta virando, e para qual lado -  -1: sentido horario, 1: sentido anti-horario */
    double turnRate;            /*Quanto o bote pode virar em um segundo, em radianos */
    velocity prevVel;           /*Velocidade anterior, para colisoes com outros botes */
    int life;                   /*Quantas vezes ele pode bater num coral antes de encalhar
                                   Ja que a chance de encalhar e arbitraria, definimos como 0, se bateu um numero de vezes menor
                                   que o numero de vidas, e 1 caso contrario. */
    int defaultLives;           /*Numero padrao de vidas */
    double timeStuckLeft;       /*Quanto tempo falta para o barquinho encalhado dar respawn */
    double defaultTimeStuck;    /*Tempo que ele demora para dar respawn apos encalhar */
} Extra;

/*Guarda os valores padrao dos botes, ja que podem ser definidos via linha de comando*/
static struct boatDefaults {
    double turnRate;
    double accel;
    double friction;
    int lives;
    double timeStuck;
} boatDefaults;

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
    b->extra->life = b->extra->defaultLives = boatDefaults.lives;
    b->extra->friction = boatDefaults.friction;
    b->extra->turnRate = boatDefaults.turnRate;
    b->extra->defaultTimeStuck = boatDefaults.timeStuck;
    b->extra->color = b->tex.color;
    return b;
}

void boatUpdate(boat b, int keepDir, double timedif)
{
    if (b->extra->life <= 0) {  /*Se o barco esta encalhado */
        b->extra->timeStuckLeft -= timedif;
        b->tex.color = b->extra->color / 2;     /*Torna o bote mais escuro - note que
                                                   os valores para R e G sempre sao pares para lidar com isso */
        if (b->extra->timeStuckLeft <= 0) {
            b->extra->life = b->extra->defaultLives;
            boatGeneratePosAndVelInBorder(MAXSPEED, &b->pos, &b->vel);
            b->tex.color = b->extra->color;     /*Retornando a cor original,
                                                   ja que o bote muda de cor quando encalhado */
        }
        return;
    }
    if (!keepDir) {
        b->extra->isTurning = randInt(0, 2) - 1;        /*Feito dessa forma uma vez que randInt buga para valores negativos */
        b->extra->isAccel = randInt(0, 2) - 1;
    }
    if (b->extra->isAccel) {
        b->acc.x = -cos(b->dir) * b->extra->accel * b->extra->isAccel;
        b->acc.y = -sin(b->dir) * b->extra->accel * b->extra->isAccel;
    } else
        b->acc = vectorCreate(0, 0);
    b->acc.x = b->acc.x - b->vel.x * b->extra->friction;
    b->acc.y = b->acc.y - b->vel.y * b->extra->friction;

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
        if (b->extra->life > 0) {
            objectSide = o->radius * SQRT_2 / 2;        /*Uma vez que coral e um quadrado inscrito ao circulo de colisao */
            /*Note que nem sempre que uma colisao e detectada algo acontece. Isso ocorre porque e possivel que o circulo
             * de colisao dos dois objetos estejam colidindo sem que os objetos em si estejam*/
            /*Se estiver batendo por cima ou por baixo */
            if (abs(b->pos.x - o->pos.x) <= objectSide
                && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius)) {
                b->vel.y *= -1;
                b->extra->life--;
                /*Se estiver batendo pela direita ou esquerda */
            } else if (abs(b->pos.y - o->pos.y) <= objectSide
                       && abs(b->pos.x - o->pos.x) <=
                       (objectSide + b->radius)) {
                b->vel.x *= -1;
                b->extra->life--;
                /*Se estiver batendo na quina */
            } else if (abs(b->pos.x - o->pos.x) >= objectSide
                       && abs(b->pos.y - o->pos.y) >= objectSide) {
                b->vel.x *= -1;
                b->vel.y *= -1;
                b->extra->life--;
            }
            /*Se apos essa colisao, encalhou */
            if (b->extra->life <= 0) {
                b->vel.x = 0;
                b->vel.y = 0;
                b->extra->timeStuckLeft = b->extra->defaultTimeStuck;
            }
        }
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
    objectQuadUpdate(b);
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
