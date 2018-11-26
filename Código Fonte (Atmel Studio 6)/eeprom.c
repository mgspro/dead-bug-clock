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
#include "DBClock.h"
//---------------------------------------------------------------------------
void EEPROMWr(uint16_t Addr, uint8_t Data)
{
	wdt_reset();
	while(EECR & (1 << EEWE));
	EEAR = Addr;
	EEDR = Data;
	EECR |= (1 << EEMWE);
	EECR |= (1 << EEWE);
}
//---------------------------------------------------------------------------
uint8_t EEPROMRd(uint16_t Addr)
{
	wdt_reset();
	while(EECR & (1 << EEWE));
	EEAR = Addr;
	EECR |= (1 << EERE);
	return EEDR;
}
//---------------------------------------------------------------------------