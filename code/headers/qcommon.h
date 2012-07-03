#ifndef QCOMMON_H
#define QCOMMON_H

#include <QtGlobal>
#include <string.h>
#include <math.h>

#define ROUND(x) (x<0?ceil((x)-0.5):floor((x)+0.5))

typedef unsigned char qbyte8u;
typedef unsigned short qbyte16u;
typedef unsigned int qbyte32u;
typedef qbyte8u qbyteu;

typedef signed char qbyte8s;
typedef signed short qbyte16s;
typedef signed int qbyte32s;
typedef qbyte8s qbytes;

typedef qbyte8u qbyte8;
typedef qbyte16u qbyte16;
typedef qbyte32u qbyte32;
typedef qbyte8 qbyte;

typedef float qfloat;

#endif
