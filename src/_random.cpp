//
// Created by ZzyPC on 2021/6/8.
//
#include <math.h>
#include "../include/_random.h"

unsigned short rnd::_rand48_seed[3] = {
            RAND48_SEED_0,
            RAND48_SEED_1,
            RAND48_SEED_2
};
unsigned short rnd::_rand48_mult[3] = {
        RAND48_MULT_0,
        RAND48_MULT_1,
        RAND48_MULT_2
};
unsigned short rnd::_rand48_add = RAND48_ADD;

void rnd::_dorand48(unsigned short xseed[3]) {
    unsigned long accu;
    unsigned short temp[2];

    accu = (unsigned long) rnd::_rand48_mult[0] * (unsigned long) xseed[0] +
        (unsigned long) rnd::_rand48_add;
    temp[0] = (unsigned short) accu;        /* lower 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += (unsigned long) rnd::_rand48_mult[0] * (unsigned long) xseed[1] +
            (unsigned long) rnd::_rand48_mult[1] * (unsigned long) xseed[0];
    temp[1] = (unsigned short) accu;        /* middle 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += rnd::_rand48_mult[0] * xseed[2] + rnd::_rand48_mult[1] * xseed[1] + rnd::_rand48_mult[2] * xseed[0];
    xseed[0] = temp[0];
    xseed[1] = temp[1];
    xseed[2] = (unsigned short) accu;
}

double rnd::erand48(unsigned short xseed[3]) {
    _dorand48(xseed);
    return ldexp((double) xseed[0], -48) +
        ldexp((double) xseed[1], -32) +
        ldexp((double) xseed[2], -16);
}

double rnd::drand48(void) {
    return erand48(rnd::_rand48_seed);
}

long rnd::lrand48(void) {
    _dorand48(rnd::_rand48_seed);
    return ((long) rnd::_rand48_seed[2] << 15) + ((long) rnd::_rand48_seed[1] >> 1);
}

long rnd::nrand48(unsigned short xseed[3]) {
    _dorand48(xseed);
    return ((long) xseed[2] << 15) + ((long) xseed[1] >> 1);
}

long rnd::mrand48(void) {
    _dorand48(rnd::_rand48_seed);
    return ((long) rnd::_rand48_seed[2] << 16) + (long) rnd::_rand48_seed[1];
}

long rnd::jrand48(unsigned short xseed[3]) {
    _dorand48(xseed);
    return ((long) xseed[2] << 16) + (long) xseed[1];
}

void rnd::srand48(long seed) {
    rnd::_rand48_seed[0] = RAND48_SEED_0;
    rnd::_rand48_seed[1] = (unsigned short) seed;
    rnd::_rand48_seed[2] = (unsigned short) (seed >> 16);
    rnd::_rand48_mult[0] = RAND48_MULT_0;
    rnd::_rand48_mult[1] = RAND48_MULT_1;
    rnd::_rand48_mult[2] = RAND48_MULT_2;
    rnd::_rand48_add = RAND48_ADD;
}

unsigned short * rnd::seed48(unsigned short xseed[3]) {
    static unsigned short sseed[3];

    sseed[0] = rnd::_rand48_seed[0];
    sseed[1] = rnd::_rand48_seed[1];
    sseed[2] = rnd::_rand48_seed[2];
    rnd::_rand48_seed[0] = xseed[0];
    rnd::_rand48_seed[1] = xseed[1];
    rnd::_rand48_seed[2] = xseed[2];
    rnd::_rand48_mult[0] = RAND48_MULT_0;
    rnd::_rand48_mult[1] = RAND48_MULT_1;
    rnd::_rand48_mult[2] = RAND48_MULT_2;
    rnd::_rand48_add = RAND48_ADD;
    return sseed;
}

void rnd::lcong48(unsigned short p[7]) {
    rnd::_rand48_seed[0] = p[0];
    rnd::_rand48_seed[1] = p[1];
    rnd::_rand48_seed[2] = p[2];
    rnd::_rand48_mult[0] = p[3];
    rnd::_rand48_mult[1] = p[4];
    rnd::_rand48_mult[2] = p[5];
    rnd::_rand48_add = p[6];
}
