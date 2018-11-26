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
void LCDWr(uint8_t Ins, uint8_t Data, uint8_t Brilho)
{
	if(Ins)
		RS_1;
	else
		RS_0;
	PORTB = ((Data >> 4) & 0x0F) << 2;
	E_1;
	E_0;
	PORTB = (Data & 0x0F) << 2;
	E_1;
	E_0;
	FPwm(Brilho);
}
//---------------------------------------------------------------------------
void LCDString(char *Buffer, uint8_t Linha, uint8_t Simulador, uint8_t Brilho)
{
	uint8_t Atraso;
	if(Linha == POS_ATUAL)
	{
		while(*Buffer)
		{
			Atraso = *Buffer + 50;
			LCDWr(TEXTO, *Buffer++, Brilho);
			if(Simulador)
			{
				while(Atraso)
				{
					wdt_reset();
					FPwm(Brilho);
					FPwm(Brilho);
					Atraso--;
				}
			}
		}
	}
	if(Linha == LINHA1)
		LCDWr(COMANDO, LINHA1, Brilho);
	else if(Linha == LINHA2)
		LCDWr(COMANDO, LINHA2, Brilho);
	while(*Buffer)
	{
		Atraso = *Buffer + 50;
		LCDWr(TEXTO, *Buffer++, Brilho);
		if(Simulador)
		{
			while(Atraso)
			{
				wdt_reset();
				FPwm(Brilho);
				FPwm(Brilho);
				Atraso--;
			}
		}
	}
}
//---------------------------------------------------------------------------
void LCDNum(uint8_t Num, uint8_t Brilho)
{
	LCDWr(TEXTO, (Num / 10) + 48, Brilho);
	LCDWr(TEXTO, (Num % 10) + 48, Brilho);
}
//---------------------------------------------------------------------------
void LCDClear(uint8_t Brilho)
{
	uint8_t Temp;
	LCDWr(COMANDO, 0x01, Brilho); //Clear LCD
	Temp = 200;
	while(Temp)
	{
		FPwm(Brilho);
		Temp--;
	}
}
//---------------------------------------------------------------------------
void LCDNewChar(uint8_t Pos, uint8_t *Buffer)
{
	uint8_t Count;
	if(Pos < 8)
	{
		LCDWr(COMANDO, 0x40 + (Pos * 8), 0);
		for(Count = 0; Count < 8; Count++)
             LCDWr(TEXTO, Buffer[Count], 0);
	}
 
}
//---------------------------------------------------------------------------
void LCDReset()
{
	PORTB = 0x0F << 2;
	_delay_ms(20);
	PORTB = 0x03 << 2;
	E_1;
	E_0;
	_delay_ms(10);
	PORTB = 0x03 << 2;
	E_1;
	E_0;
	_delay_ms(1);
	PORTB = 0x03 << 2;
	E_1;
	E_0;
	_delay_ms(1);
	PORTB = 0x02 << 2;
	E_1;
	E_0;
	_delay_ms(1);
}
//---------------------------------------------------------------------------
void LCDIni()
{
	LCDReset();
	LCDWr(COMANDO, 0x28, 0); //4-bit mode, 2 lines, 5x7 font
	LCDWr(COMANDO, 0x0C, 0); //No cursor, no blink
	LCDWr(COMANDO, 0x06, 0); //Automatic Increment, no Display shift
}
//---------------------------------------------------------------------------