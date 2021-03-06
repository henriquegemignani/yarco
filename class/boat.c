/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "boat.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/vector.h"
#include "../config/configuration.h"
#include "../lib/report.h"
#include <math.h>
#include <allegro.h>

#define NUM_BUTTONS 5
#define ACCEL_BUTTON 0
#define BRAKE_BUTTON 1
#define TURN_RIGHT_BUTTON 2
#define TURN_LEFT_BUTTON 3
#define ANCHOR_BUTTON 4

typedef struct objectList *listLink;

struct objectList {
    object person;
    listLink next;
};

static point shipPos;

struct Extra {
    int isAccel;                /*Verifica se esta acelerando, e em qual direcao: 1 para frente, -1 para tras e 0 caso nao acelere */
    int color;                  /*Cor usual do bote - guardado uma vez que boat->tex.color nao e constante */
    double accel;               /*Aceleracao do bote, seja para frente ou para tras */
    double friction;            /*Desaceleracao devida ao atrito */
    double anchorMultiplier;
    int isTurning;              /*Verifica se esta virando, e para qual lado ;  1: sentido horario, -1: sentido anti-horario */
    double turnRate;            /*Quanto o bote pode virar em um segundo, em radianos */
    velocity prevVel;           /*Velocidade anterior, para colisoes com outros botes */
    int life;
    double timeStuckLeft;       /*Quanto tempo falta para o barquinho encalhado dar respawn */
    double defaultTimeStuck;    /*Tempo que ele demora para dar respawn apos encalhar */
    int isAnchored;
    int player;
    int keyLayout[NUM_BUTTONS]; /*Vetor que representa qual tecla faz qual cosia*/
    int anchorButtonHeld;       /*Verifica se o botao de ancora esta pressionado, para ninguem ter que apretar por exatamente um frame*/
    listLink personList;        /*Lista de passageiros no bote*/
    int peopleHeld;             /*Numero de pessoas no bote*/
    int points;
    double unloadTimeLeft;
    double unloadTime;
    double unloadDistance;
    point respawnPoint;         /*Onde o bote volta pro mapa*/
    int extraLivesCount;        /*Quantas vidas extras o jogador ja ganhou*/
    int extraLifeScore;         /*Pontuacao base para ganhar mais vidas*/
    char *name;                 /*Nome do jogador*/
    double maxAnchorSpeed;      /*Velocidade maxima na qual o jogador pode ancorar*/
};

/*Guarda os valores padrao dos botes, ja que podem ser definidos via linha de comando*/
static struct boatDefaults {
    double turnRate;
    double accel;
    double friction;
    double anchorMultiplier;
    double unloadDistance;
    double unloadTime;
    int lives;
    int boatCapacity;
    double timeStuck;
    int extraLifeScore;
    double maxAnchorSpeed;
} boatDefaults;

void getShipPos(point p) /*Para saber onde esta o navio para verificar se esta na distancia de desembarque*/
{
    shipPos = p;
}

/*Funcoes privadas*/

void boatGetControls(boat b, int player) /*Inicializa os controles do bote*/
{
    char confgroup[8];
    strcpy(confgroup, "PlayerX");
    confgroup[6] = '1' + player;

    b->extra->keyLayout[ACCEL_BUTTON] =
        configGetValue(confgroup, "ButtonAccel").num;
    b->extra->keyLayout[BRAKE_BUTTON] =
        configGetValue(confgroup, "ButtonBrake").num;
    b->extra->keyLayout[TURN_RIGHT_BUTTON] =
        configGetValue(confgroup, "ButtonTurnRight").num;
    b->extra->keyLayout[TURN_LEFT_BUTTON] =
        configGetValue(confgroup, "ButtonTurnLeft").num;
    b->extra->keyLayout[ANCHOR_BUTTON] =
        configGetValue(confgroup, "ButtonAnchor").num;

}

boat boatNew(int player)
{
    int numPlayers = configGetValue("General", "NumPlayers").num;
    double startAngle = PI - player * 2 * PI / numPlayers;
    point pos = vectorCreate(MAX_X / 2 + MAX_X / 8 * cos(startAngle),
                             MAX_Y / 2 + MAX_Y / 8 * sin(startAngle));
    velocity vel = vectorCreate(0, 0);
    boat b;
    texture tex;

    char confgroup[8];
    strcpy(confgroup, "PlayerX");
    confgroup[6] = '1' + player;

    tex.color = configGetValue(confgroup, "Color").num;
    tex.type = TEX_TRIANGLE;
    b = boatCreate(tex, pos, vel);
    b->dir = PI / 2;
    b->extra->player = player;
    boatGetControls(b, player);
    b->extra->respawnPoint = b->pos;
    b->extra->name = configGetValue(confgroup, "Name").str;
    return b;
}

/*Funcoes publicas*/

int boatFullOrCrashed(boat b)
{
    return (b->extra->peopleHeld >= boatDefaults.boatCapacity
            || b->extra->timeStuckLeft > 0);
}
/*
void boatScoreAdd(boat b, int point)
{
    b->extra->points += point;
}
*/
void boatRetrievePerson(boat b, object o) /*Move a pessoa pro bote*/
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

    double difficultyExp =
        (configGetValue("Gameplay", "Difficulty").real - 3) / 8;

    boatDefaults.turnRate =
        configGetValue("Gameplay",
                       "TurnRate").real * exp(-difficultyExp / 4);
    boatDefaults.accel =
        configGetValue("Gameplay",
                       "Acceleration").real * exp(-difficultyExp);
    boatDefaults.friction =
        configGetValue("Gameplay", "Friction").real * exp(-difficultyExp);
    boatDefaults.timeStuck = configGetValue("Gameplay", "TimeStuck").num;
    boatDefaults.lives = configGetValue("Gameplay", "InitialLives").num;
    boatDefaults.unloadDistance =
        configGetValue("Gameplay", "UnloadDistance").real;
    boatDefaults.unloadTime =
        configGetValue("Gameplay",
                       "UnloadTime").real * exp(difficultyExp / 2);
    boatDefaults.boatCapacity =
        configGetValue("Gameplay", "BoatCapacity").num;
    boatDefaults.anchorMultiplier =
        configGetValue("Gameplay", "AnchorFrictionMultiplier").real;
    boatDefaults.extraLifeScore =
        configGetValue("Gameplay", "ExtraLifeScore").num;
    boatDefaults.maxAnchorSpeed = configGetValue("Gameplay", "MaxAnchorSpeed").real;
}

boat boatCreate(texture tex, point pos, velocity vel)
{
    boat b;
    static double boatRadius = -1;
    if (boatRadius == -1)
        boatRadius = configGetValue("Radius", "Boat").real;

    b = objectCreate(TYPE_BOAT, 0, pos, vel, boatRadius, tex);
    AUTOMALLOC(b->extra);
    b->extra->accel = boatDefaults.accel;
    b->extra->life = boatDefaults.lives;
    b->extra->friction = boatDefaults.friction;
    b->extra->anchorMultiplier = boatDefaults.anchorMultiplier;
    b->extra->turnRate = boatDefaults.turnRate;
    b->extra->defaultTimeStuck = boatDefaults.timeStuck;
    b->extra->unloadTime = boatDefaults.unloadTime;
    b->extra->unloadDistance = boatDefaults.unloadDistance;
    b->extra->extraLifeScore = boatDefaults.extraLifeScore;
    b->extra->maxAnchorSpeed = boatDefaults.maxAnchorSpeed;
    b->extra->color = b->tex.color;
    b->extra->isAnchored = 0;
    b->extra->isTurning = 0;
    b->extra->isAccel = 0;
    b->extra->anchorButtonHeld = 0;
    b->extra->peopleHeld = 0;
    b->extra->points = 0;
    b->extra->unloadTimeLeft = b->extra->unloadTime;
    b->extra->timeStuckLeft = 0;
    b->extra->personList = NULL;
    b->extra->extraLivesCount = 1;
    b->extra->prevVel = vectorCreate(0,0);
    return b;
}

void boatReadKeyboard(boat b)
{
    b->extra->isAccel = 0;
    b->extra->isTurning = 0;
    if (key[b->extra->keyLayout[ACCEL_BUTTON]])
        b->extra->isAccel += 1;
    if (key[b->extra->keyLayout[BRAKE_BUTTON]])
        b->extra->isAccel -= 1;
    if (key[b->extra->keyLayout[TURN_RIGHT_BUTTON]])
        b->extra->isTurning += 1;
    if (key[b->extra->keyLayout[TURN_LEFT_BUTTON]])
        b->extra->isTurning -= 1;
    if (key[b->extra->keyLayout[ANCHOR_BUTTON]]) {
        if (!b->extra->anchorButtonHeld && vectorLength(b->vel) <= b->extra->maxAnchorSpeed) {
            b->extra->isAnchored = !b->extra->isAnchored;
            b->extra->anchorButtonHeld = 1;
        }
    } else
        b->extra->anchorButtonHeld = 0;

}

void rescuePerson(boat b) /*Resgata definitivamente a pessoa no navio*/
{
    listLink aux;
    OBJECT_REMOVE(b->extra->personList->person);
    aux = b->extra->personList;
    b->extra->personList = b->extra->personList->next;
    free(aux);
    b->extra->peopleHeld--;
    b->extra->points += 50;
    debugMsg("I IS IN RESCUEEEEEEEE");
}

void boatUpdate(boat b, int keepDir, double timedif)
{
    double anchorRatio;
    if (b->extra->timeStuckLeft > 0) {  /*Se o barco esta encalhado */
        b->extra->timeStuckLeft -= timedif;
        b->tex.color = b->extra->color / 2;
        /* Torna o bote mais escuro - note que os valores para R e G sempre sao pares para lidar com isso */

        if (b->extra->timeStuckLeft <= 0) {
            if (b->extra->life >= 0) {
                b->extra->timeStuckLeft = 0;
                b->pos = b->extra->respawnPoint;
                b->vel = vectorCreate(0, 0);
                b->acc = vectorCreate(0, 0);
                b->dir = PI/2;
                b->tex.color = b->extra->color;
                /* Retornando a cor original, ja que o bote muda de cor quando encalhado */
            } else
                b->toBeRemoved = 1;
        }
        return;
    }
    /*Verificando se ja deve ganahr uma vida nova*/
    if (b->extra->points >=
        b->extra->extraLivesCount * b->extra->extraLifeScore) {
        b->extra->life++;
        b->extra->extraLivesCount++;
    }
    /*Le teclado*/
    boatReadKeyboard(b);
    if (b->extra->isAccel && !b->extra->isAnchored) {
        b->acc.x = -b->extra->accel * cos(b->dir) * b->extra->isAccel;
        b->acc.y = -b->extra->accel * sin(b->dir) * b->extra->isAccel;
    } else
        b->acc = vectorCreate(0, 0);
    if (b->extra->isAnchored)
        anchorRatio = b->extra->anchorMultiplier;
    else
        anchorRatio = 1;
    b->acc.x = b->acc.x - b->vel.x * b->extra->friction * anchorRatio;
    b->acc.y = b->acc.y - b->vel.y * b->extra->friction * anchorRatio;
    b->vel = vectorSum(b->vel, vectorMulDouble(b->acc, timedif));
    b->pos = vectorSum(b->pos, vectorMulDouble(b->vel, timedif));
    if (!b->extra->isAnchored)
        b->dir += b->extra->isTurning * b->extra->turnRate * timedif;
    objectQuadUpdate(b);
    /*Resgate de pessoas*/
    if (b->extra->isAnchored
        && distanceBetweenPoints(b->pos,
                                 shipPos) <= b->extra->unloadDistance) {
        if (b->extra->personList != NULL) {
            if (b->extra->unloadTimeLeft <= 0.0) {
                debugDouble("b->extra->unloadtimeleft",
                            b->extra->unloadTimeLeft);
                rescuePerson(b);
                b->extra->unloadTimeLeft = b->extra->unloadTime;
            } else
                b->extra->unloadTimeLeft =
                    b->extra->unloadTimeLeft - timedif;
        }
    } else
        b->extra->unloadTimeLeft = b->extra->unloadTime;
    /*Fala o que precisa ser mostrado no display*/
    statusReport(b->extra->player, b->extra->name, b->extra->life,
                        b->extra->points, b->extra->peopleHeld);
}

void boatRemove(boat b)
{
    free(b->extra);
    free(b);
}

void boatPersonFree(boat b) /*Joga as pessoas de volta no oceano*/
{
    int i, errorCode;
    listLink aux = b->extra->personList;
    double angDif = 2 * PI / b->extra->peopleHeld;
    for (i = 0; i < b->extra->peopleHeld; i++) {
        if (aux == NULL)
            genError
                ("Falha de sincronia entre personList e peopleHeld! Contate um programador.");
        aux->person->pos =
            vectorSum(b->pos,
                      vectorPolarToCartesian(b->radius +
                                             aux->person->radius,
                                             i * angDif));
        aux->person->vel = vectorAngleSet(aux->person->vel, angDif);
        if ((errorCode = objectTableAddObject(aux->person))) {
            if (errorCode == ERROR_OBJECT_LIMIT_EXCEEDED)
                genWarning
                    ("Nao foi possivel fazer a pessoa cair do bote!\n");
            if (errorCode == ERROR_OBJECT_IS_COLLIDING) {
                do {
                    aux->person->pos =
                        vectorSum(aux->person->pos,
                                  vectorMulDouble(vectorSub
                                                  (aux->person->pos,
                                                   b->pos), 1.1));
                    /*Se ele tentar colocar a pessoa num lugar ja ocupado, ele joga ela pra mais longe ate estar num lugar disponivel*/
                } while (objectTableAddObject(aux->person) ==
                         ERROR_OBJECT_IS_COLLIDING);
            }
        }
        aux = aux->next;
    }
    for (aux = b->extra->personList; aux != NULL;
         aux = b->extra->personList) {
        b->extra->personList = b->extra->personList->next;
        free(aux);
        b->extra->peopleHeld--;
    }
}

void boatCrash(boat b)
{
    b->extra->life--;
    boatPersonFree(b);
    b->extra->timeStuckLeft = b->extra->defaultTimeStuck;
}

void personBoatCollision(boat b, object o)
{
    boatRetrievePerson(b, o);
    b->extra->points += 10;
    objectTableLeave(o->id);
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

        b->pos =
            vectorSum(vectorLengthSet
                      (vectorSub(b->pos, o->pos),
                       b->radius + o->radius + 1), o->pos);

        break;
    case TYPE_CORAL:
        objectSide = o->radius * SQRT_2 / 2;
        /*Note que a colisao so existe caso bata num dos lados do coral, nao se simplesmente estiver no circulo de colisao*/
        if (((abs(b->pos.x - o->pos.x) <= objectSide
              && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius))
             || (abs(b->pos.y - o->pos.y) <= objectSide
                 && abs(b->pos.x - o->pos.x) <= (objectSide + b->radius))
             ||
             ((abs(b->pos.x - o->pos.x) >= objectSide
               && abs(b->pos.y - o->pos.y) >= objectSide)))
            && b->extra->timeStuckLeft == 0)
            boatCrash(b);
        break;
    case TYPE_SHIP:
        objectSide = o->radius / SQRT_5;        /*Note que o retangulo e um retangulo
                                                   inscrito ao circulo de colisao */
        /*Vide comentarios para colisao com coral */
        if (abs(b->pos.x - o->pos.x) <= 2 * objectSide
            && abs(b->pos.y - o->pos.y) <= (objectSide + b->radius)) {
            b->vel.y *= -1;
            (b->pos.y >= o->pos.y) ? (b->pos.y =
                                      o->pos.y + objectSide + b->radius +
                                      1) : (b->pos.y =
                                            o->pos.y - objectSide -
                                            b->radius - 1);
        } else if (abs(b->pos.y - o->pos.y) <= objectSide
                   && abs(b->pos.x - o->pos.x) <=
                   (2 * objectSide + b->radius)) {
            b->vel.x *= -1;
            (b->pos.x >= o->pos.x) ? (b->pos.x =
                                      o->pos.x + objectSide * 2 +
                                      b->radius + 1) : (b->pos.x =
                                                        o->pos.x -
                                                        objectSide * 2 -
                                                        b->radius - 1);
        } else if (abs(b->pos.x - o->pos.x) >= 2 * objectSide
                   && abs(b->pos.y - o->pos.y) >= objectSide) {
            b->vel.x *= -1;
            b->vel.y *= -1;
            b->pos =
                vectorSum(vectorLengthSet
                          (vectorSub(b->pos, o->pos),
                           b->radius + o->radius + 1), o->pos);
        }
        break;
    case TYPE_PERSON:
        if (!boatFullOrCrashed(b))
            personBoatCollision(b, o);
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
        b->pos.y = (b->pos.y < b->radius ? 0 : MAX_Y);
    }
    objectQuadUpdate(b);
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
