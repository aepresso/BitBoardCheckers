#ifndef BIT_OPS_H // header file for operations
#define BIT_OPS_H

#include <stdint.h> 

uint64_t setBit(uint64_t value, int position);
uint64_t clearBit(uint64_t value, int position);
uint64_t toggleBit(uint64_t value, int position);
uint64_t getBit(uint64_t value, int position);

#endif
