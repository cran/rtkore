#-----------------------------------------------------------------------
#     Copyright (C) 2004-2016  Serge Iovleff, Université Lille 1, Inria
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as
#    published by the Free Software Foundation; either version 2 of the
#    License, or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this program; if not, write to the
#    Free Software Foundation, Inc.,
#    59 Temple Place,
#    Suite 330,
#    Boston, MA 02111-1307
#    USA
#
#    Contact : S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
#
#-----------------------------------------------------------------------
#
# Purpose:  Makefile of the tutos
# Author:   Serge Iovleff, S..._Dot_I..._At_stkpp_Dot_org (see copyright for ...)
#
#-----------------------------------------------------------------------
# makevars contains general definitions and flags.
#
include ../../../makevars

#-----------------------------------------------------------------------
# overide Paths BIN and LIB
#
BIN_DIR = ../../../bin/
LIB_DIR = ../../../lib/
INC_DIR = ../../../include/
PROJECTS_DIR = ../../../projects/

#-----------------------------------------------------------------------
# source files
#
CXX_SRCS = $(wildcard tuto*.cpp)

## library name
STKPP_LIB = $(LIB_DIR)/$(LIB_STKPP_A)

#-----------------------------------------------------------------------
# program files
CXX_PROGS = $(CXX_SRCS:%.cpp=$(BIN_DIR)%)

#-----------------------------------------------------------------------
# Targets
#
.PHONY: all
all: tutoprograms

tutoprograms: $(CXX_PROGS)

#-----------------------------------------------------------------------
# Objects compilation rules
#
$(BIN_DIR)%.o: %.cpp
	$(CXX) ) $< -c -o $@

#-----------------------------------------------------------------------
# program compilation rules
$(BIN_DIR)tuto%: tuto%.cpp $(STKPP_LIB)
	$(CXX) $< $(STK_CPPFLAGS) $(STK_CXXFLAGS) -I$(INC_DIR) -I$(PROJECTS_DIR) $(STKPP_LIB) -o $@ -lm
	$@ > tuto$*.out

#-----------------------------------------------------------------------
# clean test programs 
clean:
	$(RM) $(BIN_DIR)tuto*
