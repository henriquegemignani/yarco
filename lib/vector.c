/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "vector.h"
#include <math.h>

vector vectorSum(vector a, vector b)
{
    vector v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    return v;
}

vector vectorSub(vector a, vector b)
{
    vector v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    return v;
}

double vectorMulEsc(vector a, vector b)
{
    return ((a.x * b.x) + (a.y * b.y));
}

vector vectorMulDouble(vector v, double alfa)
{
    vector r;
    r.x = v.x * alfa;
    r.y = v.y * alfa;
    return r;
}

vector vectorDiv(vector v, double div)
{
    return vectorCreate(v.x / div, v.y / div);
}

vector vectorPolarToCartesian(double length, double ang)
{
    vector v;
    v.x = length * cos(ang);
    v.y = length * sin(ang);
    return v;
}

vector vectorCartesianToPolar(vector v)
{
    double vAng = vectorAngle(v), vLength = vectorLength(v);
    v.x = vLength;
    v.y = vAng;
    return v;
}

vector vectorRotate(vector v, double ang)
{
    double vAng;
    vAng = vectorAngle(v);
    return vectorAngleSet(v, ang + vAng);
}

double vectorAngle(vector v)
{
  return atan2(v.y, v.x);
}

vector vectorAngleSet(vector v, double ang)
{
    double vLength;
    vLength = vectorLength(v);
    v.x = cos(ang) * vLength;
    v.y = sin(ang) * vLength;
    return v;
}

vector vectorLengthSet(vector v, double length)
{
    double vAng;
    vAng = vectorAngle(v);
    v.x = length * cos(vAng);
    v.y = length * sin(vAng);
    return v;
}

double distanceBetweenPoints(point a, point b)
{
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}

double vectorLength(vector v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

int vectorPrint(vector v)
{
    return printf("(%8.3f,%8.3f)", v.x, v.y);
}
