
#ifndef Theater_h
#define Theater_h

// --------
// includes
// --------

#include <iostream>
#include <string>
#include <vector>
#include <cinttypes>

// ------------
// theater_eval
// ------------

uint64_t theater_eval (int n, int m, int t);

// -------------
// theater_print
// -------------

void theater_print (std::ostream& w, uint64_t answer);

// -------------
// theater_solve
// -------------

void theater_solve (std::istream& r, std::ostream& w);

#endif
