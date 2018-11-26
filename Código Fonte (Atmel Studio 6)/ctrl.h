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
#ifndef ctrl_h
#define ctrl_h
//---------------------------------------------------------------------------
#define ADSC_1	ADCSRA|=(1<<ADSC)
#define ADIF_1	ADCSRA|=(1<<ADIF)
#define ADIF_R	(ADCSRA&(1<<ADIF))
//---------------------------------------------------------------------------
uint8_t FLuz(void);
uint8_t FPwm(uint8_t ILuz);
//---------------------------------------------------------------------------
#endif