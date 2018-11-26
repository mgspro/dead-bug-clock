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
#ifndef lcd_h
#define lcd_h
//---------------------------------------------------------------------------
#define RS_1		PORTD|=(1<<PD5)
#define RS_0		PORTD&=~(1<<PD5)
#define RW_1		PORTD|=(1<<PD6)
#define RW_0		PORTD&=~(1<<PD6)
#define E_1			PORTD|=(1<<PD7)
#define E_0			PORTD&=~(1<<PD7)
#define TEXTO		1
#define COMANDO		0
#define POS_ATUAL	0
#define LINHA1		0x80
#define LINHA2		0xC0
//---------------------------------------------------------------------------
void LCDWr(uint8_t Ins, uint8_t Data, uint8_t ILuz);
void LCDString(char *Buffer, uint8_t Linha, uint8_t Simulador, uint8_t ILuz);
void LCDNum(uint8_t Num, uint8_t ILuz);
void LCDClear(uint8_t ILuz);
void LCDNewChar(uint8_t Pos, uint8_t *Buffer);
void LCDReset(void);
void LCDIni(void);
//---------------------------------------------------------------------------
#endif