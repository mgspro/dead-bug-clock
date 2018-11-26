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
void TWIIni(void)
{
    TWSR = 0x00; //Prescaler = 1
    TWBR = 0x01; //333Khz @ 8Mhz
}
//---------------------------------------------------------------------------
void TWIStart(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
//---------------------------------------------------------------------------
void TWIStop(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}
//---------------------------------------------------------------------------
void TWIWrite(uint8_t u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}
//---------------------------------------------------------------------------
uint8_t TWIReadAck(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}
//---------------------------------------------------------------------------
uint8_t TWIReadNack(void)
{
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}
//---------------------------------------------------------------------------
uint8_t TWIStatus(void)
{
    uint8_t Status;
    Status = TWSR & 0xF8;
    return Status;
}
//---------------------------------------------------------------------------