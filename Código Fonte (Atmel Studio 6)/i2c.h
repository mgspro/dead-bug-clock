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
#ifndef i2c_h
#define i2c_h
//---------------------------------------------------------------------------
#define E_CTRL 			0x0E
#define E_CTRL_STATUS	0x0F
#define E_SEGUNDOS 		0x00
#define E_MINUTOS 		0x01
#define E_HORAS 		0x02
#define E_DIASEMANA		0x03
#define E_DIA	 		0x04
#define E_MES	 		0x05
#define E_ANO	 		0x06
#define E_ENDW 			0b11010000
#define E_ENDR			0b11010001
#define LM75A_ENDW		0b10011110
#define LM75A_ENDR		0b10011111
#define LM75A_TEMP		0b00000000
//---------------------------------------------------------------------------
void TWIIni(void);
void TWIStart(void);
void TWIStop(void);
void TWIWrite(uint8_t);
uint8_t TWIReadAck(void);
uint8_t TWIReadNack(void);
uint8_t TWIStatus(void);
//---------------------------------------------------------------------------
#endif