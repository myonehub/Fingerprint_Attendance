/*
 * SCI.c
 *
 *  Created on: Nov 21, 2019
 *      Author: marki
 */

#include "SCI/SCI.h"


SciaRegs.SCICCR.bit.SCICHAR = 8; // 8 bits data
SciaRegs.SCICCR.bit.LOOPBKENA = 0; // disable Loopback
SciaRegs.SCICCR.bit.PARITYENA = 0; // disable Parity
SciaRegs.SCICCR.bit.STOPBITS = 0; // 1 stop bit


