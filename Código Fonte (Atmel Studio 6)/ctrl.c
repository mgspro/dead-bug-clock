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
uint8_t FLuz(void)
{
	uint16_t Tmp;
	ADSC_1;
	while(!ADIF_R);
	ADIF_1;
	Tmp = ADCW / 8;
	return (uint8_t)Tmp;
}
//---------------------------------------------------------------------------
uint8_t FPwm(uint8_t Brilho)
{
	uint8_t WCont;
	static uint8_t VLuz = 0;
	static uint8_t Atraso = 0;
	wdt_reset();
	if(Atraso < 4)
		Atraso++;
	else
	{
		Atraso = 0;
		if(!Brilho)
			Brilho = FLuz();
		if(Brilho > VLuz)
		{
			if(VLuz < 127)
				VLuz++;
		}
		else
		{
			if(VLuz > 0)
				VLuz--;
		}
	}
	WCont = 0;
	while(WCont < 100)
	{
		if(WCont > VLuz)
			LED_0;
		WCont++;
		_delay_us(1);
	}
	LED_1;
	return VLuz;
}
//---------------------------------------------------------------------------