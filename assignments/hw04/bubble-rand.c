/*
 * bubble-rand.c
 *
 *  Created on: Sep 21, 2016
 *      Author: Jay Brockman
 */

#include "mipslib.h"
#define SIZE 1000

int array[SIZE];
int m_w = 1, m_z = 2;

// 32-bit random number generator by George Marsaglia
// https://programmingpraxis.com/2010/10/05/george-marsaglias-random-number-generators/
int randInt() {
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  return (m_z << 16) + m_w;
}

int main()
{
  int i;
  int c, d, temp;

  for (i = 0;  i < SIZE;  i++) {
    array[i] = randInt();
  }

   for (c = 0 ; c < SIZE - 1; c++) {
    for (d = 0 ; d < SIZE - c - 1; d++) {
      if (array[d] > array[d+1]) {
        temp       = array[d];
        array[d]   = array[d+1];
        array[d+1] = temp;
      }
    }
  }

  //for (i = 0;  i < SIZE;  i++) {
  //  printf("%d\n", array[i]);
  //}

  return 0;
}


