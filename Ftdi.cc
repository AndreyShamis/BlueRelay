// src/Ftdi.cc
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

#include "Ftdi.hh"
#include <ftdi.h>
#include <sstream>
using namespace std;

Ftdi::Ftdi(int vendor, int product,int baudrate, uint8_t bitmask)
{
  check_error( ftdi_init(&ctx) );
  check_error( ftdi_usb_open(&ctx, vendor, product) );
  check_error( ftdi_enable_bitbang(&ctx, bitmask) );
  check_error( ftdi_set_baudrate(&ctx, baudrate) );
}

Ftdi::~Ftdi(void)
{
  check_error( ftdi_usb_close(&ctx) );
  ftdi_deinit(&ctx);
}

uint8_t Ftdi::read(void)
{
  uint8_t data;
  check_error( ftdi_read_pins(&ctx, &data) );
  return data;
}

void Ftdi::write(uint8_t data)
{
  check_error( ftdi_write_data(&ctx,&data,1) );
}

void Ftdi::write(vector<uint8_t>::const_iterator b,
		 vector<uint8_t>::const_iterator e)
{
  check_error( ftdi_write_data(&ctx,const_cast<unsigned char *>(&(*b)),e-b) );
}

void Ftdi::check_error(int rc)
{
  if (rc<0) {
    if (!ctx.error_str) {
      stringstream err_msg;
      err_msg << "libftdi error " << rc;
      throw err_msg.str();
    }
    throw ctx.error_str;
  }
}

