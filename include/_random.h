//
// Created by ZzyPC on 2021/6/8.
//
#pragma once
#ifndef RENDERING__RANDOM_H
#define RENDERING__RANDOM_H
#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1   (0xabcd)
#define RAND48_SEED_2   (0x1234)
#define RAND48_MULT_0   (0xe66d)
#define RAND48_MULT_1   (0xdeec)
#define RAND48_MULT_2   (0x0005)
#define RAND48_ADD      (0x000b)

namespace rnd {
    extern unsigned short _rand48_seed[3];
    extern unsigned short _rand48_mult[3];
    extern unsigned short _rand48_add;
    void _dorand48(unsigned short xseed[3]);

    double erand48(unsigned short xseed[3]);

    double drand48(void);

    long lrand48(void);

    long nrand48(unsigned short xseed[3]);

    long mrand48(void);

    long jrand48(unsigned short xseed[3]);

    void srand48(long seed);

    unsigned short *seed48(unsigned short xseed[3]);

    void lcong48(unsigned short p[7]);
}
#endif //RENDERING__RANDOM_H
