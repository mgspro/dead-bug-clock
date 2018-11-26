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
int main(void)
{
	char *DiasDaSemana[] = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};
	uint8_t LCDChar[8] = {0x04, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t Segundos, Minutos, Horas, DiaSemana, Dia, Mes, Ano, Brilho, TempH, TempL, PiscarSegMud, PiscarCont, Piscar;
	DDRB = 0b00111100;
	DDRC = 0b00001000;
	DDRD = 0b11100010;
	PORTB = 0b00000011;
	PORTC = 0b01110000;
	PORTD = 0b00000100;
	ADMUX = 0b01000010;		//VCC Ref, ADC2
	ADCSRA = 0b10000001; 	//ADC Enabled, Division Factor = 2
	wdt_enable(WDTO_2S);
	TWIIni();
	LCDIni();
	LCDNewChar(0, LCDChar);
	Brilho = EEPROMRd(0x00);
	Piscar = EEPROMRd(0x01);
	TWIStart();
	TWIWrite(E_ENDW);
	TWIWrite(E_CTRL);
	TWIWrite(0x00);			//1Hz Square-wave output
	TWIWrite(0x00); 		//Clear flag, disable 32kHz output
	TWIStop();
	TWIStart();
	TWIWrite(LM75A_ENDW);
	TWIWrite(LM75A_TEMP);
	TWIStop();
	PiscarSegMud = 0;
	PiscarCont = 0;
	while(1)
	{
		wdt_reset();
		TWIStart();
		TWIWrite(LM75A_ENDR);
		TempH = TWIReadAck();
		TempL = TWIReadNack();
		TWIStop();
		TWIStart();
		TWIWrite(E_ENDW);
		TWIWrite(E_SEGUNDOS);
		TWIStart();
		TWIWrite(E_ENDR);
		Segundos = TWIReadAck();
		Minutos = TWIReadAck();
		Horas = TWIReadAck();
		DiaSemana = TWIReadAck();
		Dia = TWIReadAck();
		Mes = TWIReadAck();
		Ano = TWIReadNack();
		TWIStop();
		if(Piscar)
		{
			if(Segundos != PiscarSegMud)
			{
				PiscarSegMud = Segundos;
				PiscarCont = 60;
			}
			if(PiscarCont > 0)	
				PiscarCont --;
		}
		else
			PiscarCont = 1;
		LCDWr(COMANDO, LINHA1, Brilho);
		LCDString(DiasDaSemana[DiaSemana - 1], LINHA1, 0, Brilho);
		LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, (0b00000011 & (Dia >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Dia) + 48, Brilho);
		LCDWr(TEXTO, '/', Brilho);
		LCDWr(TEXTO, (0b00000001 & (Mes >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Mes) + 48, Brilho);
		LCDWr(TEXTO, '/', Brilho);
		LCDWr(TEXTO, '2', Brilho);
		LCDWr(TEXTO, (0b00000001 & (Mes >> 7)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & (Ano >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Ano) + 48, Brilho);
		LCDWr(COMANDO, LINHA2, Brilho);
		LCDWr(TEXTO, (0b00000011 & (Horas >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Horas) + 48, Brilho);
		if(PiscarCont)
			LCDWr(TEXTO, ':', Brilho);
		else
			LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, (0b00001111 & (Minutos >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Minutos) + 48, Brilho);
		if(PiscarCont)
			LCDWr(TEXTO, ':', Brilho);
		else
			LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, (0b00001111 & (Segundos >> 4)) + 48, Brilho);
		LCDWr(TEXTO, (0b00001111 & Segundos) + 48, Brilho);
		LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, ' ', Brilho);
		LCDWr(TEXTO, (TempH / 10) + 48, Brilho);
		LCDWr(TEXTO, (TempH % 10) + 48, Brilho);
		LCDWr(TEXTO, '.', Brilho);
		if(TempL & 0b10000000)
			LCDWr(TEXTO, '5', Brilho);
		else
			LCDWr(TEXTO, '0', Brilho);
		LCDWr(TEXTO, 0, Brilho);
		LCDWr(TEXTO, 'C', Brilho);
		if((PINC & (1 << PC0)) > 0)
		{
			FMenu();
			Brilho = EEPROMRd(0x00);
			Piscar = EEPROMRd(0x01);
		}
	}
}
//---------------------------------------------------------------------------