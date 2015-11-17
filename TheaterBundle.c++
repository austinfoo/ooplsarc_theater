
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

// ----------------------------
// projects/twobuttons/Twobuttons.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>



// ------------
// theater_eval
// ------------

uint64_t factorial (uint64_t n) {
  uint64_t retval = 1;
  for (int i = 1; i <= n; ++i) {
    retval *= i;
  }
  return retval;
}

uint64_t upper_factorial (uint64_t n, uint64_t m) {
  uint64_t retval = 1;
  for (int i = m; i <= n; ++i) {
    retval *= i;
  }
  return retval;
}

#if 0
uint64_t theater_eval (int n, int m, int t)
{
  uint64_t result = 0;

  for (int b = 4; b <= t - 1; ++b)
  {
      int g = t - b;

      //uint64_t boy_combs = (factorial(n) / factorial(n-b)) / factorial(b);
      //uint64_t girl_combs = (factorial(m) / factorial(m-g)) / factorial(g);

      //uint64_t boy_combs  = upper_factorial(n, n-b+1) / factorial(b);
      //uint64_t girl_combs = upper_factorial(m, m-g+1) / factorial(g);

      uint64_t boy_combs = 0;
      if ((n-b) > b) {
	boy_combs  = upper_factorial(n, n-b+1) / factorial(b);
      } else {
	boy_combs  = upper_factorial(n, b+1) / factorial(n-b);
      }

      uint64_t girl_combs = 0;
      if ((m-g) > g) {
	girl_combs  = upper_factorial(m, m-g+1) / factorial(g);
      } else {
	girl_combs  = upper_factorial(m, g+1) / factorial(m-g);
      }

      uint64_t total_combs = boy_combs * girl_combs;
      result += total_combs;
  }

  return result;
}
#endif

void append_range (std::vector<uint64_t>& vect, uint64_t start, uint64_t end) {
  for (uint64_t i = start; i <= end; ++i) {
    vect.push_back(i);
  }
}

void cancel (std::vector<uint64_t>& num, std::vector<uint64_t>& den) {
  for (uint64_t& den_val : den) {
    for (uint64_t& num_val : num) {
      if (num_val % den_val == 0) {
	num_val = num_val / den_val;
	den_val = 1;
	break;
      }
    }
  }
}

uint64_t multiply (std::vector<uint64_t>& vect) {
  uint64_t product = 1;
  for (uint64_t i = 0; i < vect.size(); ++i) {
    product *= vect[i];
  }
  return product;
}

uint64_t theater_eval (int n, int m, int t)
{
  uint64_t result = 0;
  std::vector<uint64_t> num;
  std::vector<uint64_t> den;
  int max_boys = std::min (t - 1, n);
  int max_girls = std::min (t - 4, m);
  for (int b = 4; b <= max_boys; ++b)
  {
      int g = t - b;
      if (g  > max_girls) continue;

      // boys
      num.clear();
      den.clear();
      append_range (num, 1, n);
      append_range (den, 1, n-b);
      append_range (den, 1, b);
      cancel (num, den);
      uint64_t boy_combs = multiply(num) / multiply(den);

      // girls
      num.clear();
      den.clear();
      append_range (num, 1, m);
      append_range (den, 1, m-g);
      append_range (den, 1, g);
      cancel (num, den);
      uint64_t girl_combs = multiply(num) / multiply(den);

      result += boy_combs * girl_combs;
  }

  return result;
}

// -------------
// theater_print
// -------------

void theater_print (std::ostream& w, uint64_t answer)
{
  w << answer << std::endl;
}

// -------------
// theater_solve
// -------------

void theater_solve (std::istream& r, std::ostream& w) 
{
  std::string s;

  // Get the boys, girls, and group size
  int n = 0;
  int m = 0;
  int t = 0;
  if (std::getline(r, s)) {
    std::istringstream sin(s);
    sin >> n >> m >> t;
  }

  // Determine the answer
  uint64_t answer = theater_eval(n, m , t);

  // Print the result
  theater_print(w, answer);
}

#include <iostream>



// ----
// main
// ----

int main () {
    using namespace std;
    theater_solve(cin, cout);
    return 0;
}
