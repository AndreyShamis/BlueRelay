// src/Ftdi.hh
// This file is part of SlugTerm; see http://chezphil.org/slugterm
// (C) 2005 Philip Endecott

// This is version $Name:  $
//   (if there is no version (e.g. V0-1) mentioned in the previous line,
//    this is probably a snapshot from between "official" releases.)

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#ifndef Ftdi_hh
#define Ftdi_hh

#include <ftdi.h>

#include <stdint.h>
#include <vector>


class Ftdi {

public:
  Ftdi(int vendor, int product, int baudrate, uint8_t bitmask);
  ~Ftdi();
  uint8_t read(void);
  void write(uint8_t data);
  void write(std::vector<uint8_t>::const_iterator b,
	     std::vector<uint8_t>::const_iterator e);

private:
  ftdi_context ctx;
  void check_error(int rc);

};



#endif

