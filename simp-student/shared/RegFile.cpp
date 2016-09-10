/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Register file class implementation

    Copyright (C) 2016  Jay B. Brockman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RegFile.h"

RegFile::RegFile() {
    for (int i = 0;  i < 32;  i++)
        A[i] = 0;
}

uint32_t& RegFile::operator [](unsigned i) {
  if (i == 0) {
    A[0] = 0;
    return A[0];
  }
  else
  return A[i];
}

