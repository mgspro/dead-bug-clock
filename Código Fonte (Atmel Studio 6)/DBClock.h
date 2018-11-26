/*
	Copyright (c) 2018 Marcelo G. Salviano
	
	This file is part of DBClock.
	
	DBClock is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DBClock is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DBClock. If not, see <https://www.gnu.org/licenses/>
*/
#ifndef DBClockFW_1_h
#define DBClockFW_1_h
//---------------------------------------------------------------------------
#define F_CPU	8000000UL
#define LED_1	PORTC|=(1<<PC3)
#define LED_0	PORTC&=~(1<<PC3)
//---------------------------------------------------------------------------
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <string.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include "eeprom.h"
#include "i2c.h"
#include "lcd.h"
#include "ctrl.h"
#include "menu.h"
//---------------------------------------------------------------------------
#endif

