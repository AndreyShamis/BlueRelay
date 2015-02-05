# src/Makefile
# This file is part of SlugPower; see http://chezphil.org/slugpower
# (C) 2006 Philip Endecott

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


default_target: compile

EXECUTABLE=ftdi

compile: $(EXECUTABLE)


LIBPBE_DIR=/project/libpbe/work/src

PKG_CONFIG=pkg-config

FTDI_CFLAGS=$(shell $(PKG_CONFIG) --cflags libftdi)
FTDI_LIBS=$(shell $(PKG_CONFIG) --libs libftdi)

CPP_FLAGS=$(ROTE_CFLAGS) $(FTDI_CFLAGS)
#-I$(LIBPBE_DIR)

GCC_FLAGS=-D_REENTRANT
# -pthread

NO_OPT_COMPILE_FLAGS=$(CPP_FLAGS) $(GCC_FLAGS) -Wall
COMPILE_FLAGS=$(NO_OPT_COMPILE_FLAGS) -O


C_COMPILE_FLAGS=$(COMPILE_FLAGS) -std=gnu99


LINK_FLAGS=$(FTDI_LIBS)

#-L$(LIBPBE_DIR) -lpbe
#	-lomnithread -lrecode

C_SRCS=$(wildcard *.c)
CC_SRCS=$(wildcard *.cc)

OBJS=$(addsuffix .o,$(basename $(C_SRCS) $(CC_SRCS)))

%.o: %.cc
	$(CXX) $(COMPILE_FLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(C_COMPILE_FLAGS) -o $@ -c $<


$(EXECUTABLE): $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(LINK_FLAGS)

%.d: %.cc
	$(CXX) -MM -MG -MT $@ -MT $(<:%.cc=%.o) $(CPP_FLAGS) $(GCC_FLAGS) -o $@ $<

%.d: %.c
	$(CC) -MM -MG -MT $@ -MT $(<:%.c=%.o) $(CPP_FLAGS) $(GCC_FLAGS) -o $@ $<

DEPENDS=$(addsuffix .d,$(basename $(OBJS)))

-include $(DEPENDS)

clean: FORCE
	$(RM) -f *.o

veryclean: clean
	$(RM) -f *.d


.PHONY: default_target compile install FORCE
