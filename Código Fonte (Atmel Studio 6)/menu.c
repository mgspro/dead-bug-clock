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
void FMenu(void)
{
	char *DiasDaSemana[] = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};
	uint8_t MesQtdDias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	uint8_t Minutos, Horas, DiaSemana, Dia, Mes, Ano, AnoTemp1, AnoTemp2, Cent, Temp, Prox, Brilho, Piscar;
	uint16_t Atraso;
	wdt_reset();
	Brilho = EEPROMRd(0x00);
	Piscar = EEPROMRd(0x01);
	TWIStart();
	TWIWrite(E_ENDW);
	TWIWrite(E_MINUTOS);
	TWIStart();
	TWIWrite(E_ENDR);
	Minutos = TWIReadAck();
	Horas = TWIReadAck();
	DiaSemana = TWIReadAck();
	Dia = TWIReadAck();
	Mes = TWIReadAck();
	Ano = TWIReadNack();
	TWIStop();	
	FPwm(Brilho);
	Temp = 10 * (0b00001111 & (Minutos >> 4));
	Temp += (0b00001111 & Minutos);
	Minutos = Temp;
	Temp = 10 * (0b00000011 & (Horas >> 4));
	Temp += (0b00001111 & Horas);
	Horas = Temp;	
	Temp = 10 * (0b00000011 & (Dia >> 4));
	Temp += (0b00001111 & Dia);
	Dia = Temp;
	Temp = 10 * (0b00000001 & (Mes >> 4));
	Temp += (0b00001111 & Mes);
	Mes = Temp;
	Cent = 0b00000001 & (Mes >> 7);
	Temp = 10 * (0b00001111 & (Ano >> 4));
	Temp += (0b00001111 & Ano);
	Ano = Temp;
	AnoTemp1 = Ano / 10;
	AnoTemp2 = Ano % 10;
	wdt_reset();
	LCDClear(Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Config e ajustes", LINHA1, 1, Brilho);
	if(!Brilho)
		LCDString("Brilho: Auto", LINHA2, 1, Brilho);
	else
	{
		LCDString("Brilho: ", LINHA2, 1, Brilho);
		LCDNum(Brilho / 10, Brilho);
	}
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Brilho < 100)
				Brilho += 10;
			else
				Brilho = 0;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, LINHA2 + 8, Brilho);
			LCDString("    ", LINHA2 + 8, 0, Brilho);
			LCDWr(COMANDO, LINHA2 + 8, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			if(!Brilho)
				LCDString("Auto", POS_ATUAL, 1, Brilho);
			else
				LCDNum(Brilho / 10, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	if(!Brilho)
		LCDString("Brilho: Auto", LINHA1, 0, Brilho);
	else
	{
		LCDString("Brilho: ", LINHA1, 0, Brilho);
		LCDNum(Brilho / 10, Brilho);
	}
	LCDWr(COMANDO, 0x0F, Brilho);
	if(Piscar)
		LCDString("Piscar (:): Sim", LINHA2, 1, Brilho);
	else
		LCDString("Piscar (:): Nao", LINHA2, 1, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Piscar)
				Piscar = 0;
			else
				Piscar = 1;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			if(Piscar)
				LCDString("Sim", POS_ATUAL, 1, Brilho);
			else
				LCDString("Nao", POS_ATUAL, 1, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	if(Piscar)
		LCDString("Piscar (:): Sim", LINHA1, 0, Brilho);
	else
		LCDString("Piscar (:): Nao", LINHA1, 0, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Horas: ", LINHA2, 1, Brilho);
	LCDNum(Horas, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Horas < 23)
				Horas++;
			else
				Horas = 0;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			LCDNum(Horas, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Horas: ", LINHA1, 0, Brilho);
	LCDNum(Horas, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Minutos: ", LINHA2, 1, Brilho);
	LCDNum(Minutos, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Minutos < 59)
				Minutos++;
			else
				Minutos = 0;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			LCDNum(Minutos, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Minutos: ", LINHA1, 0, Brilho);
	LCDNum(Minutos, Brilho);
	//Salva horas e minutos
	Temp = (Horas / 10) << 4;
	Temp += Horas % 10;
	Horas = Temp;
	Temp = (Minutos / 10) << 4;
	Temp += Minutos % 10;
	Minutos = Temp;
	TWIStart();
	TWIWrite(E_ENDW);
	TWIWrite(E_MINUTOS);
	TWIWrite(Minutos);
	TWIWrite(Horas);
	TWIStop();
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Mes: ", LINHA2, 1, Brilho);
	LCDNum(Mes, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Mes < 12)
				Mes++;
			else
				Mes = 1;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			LCDNum(Mes, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;	
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Mes: ", LINHA1, 0, Brilho);
	LCDNum(Mes, Brilho);
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Dia da semana:", LINHA2, 1, Brilho);
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Dia da semana:", LINHA1, 0, Brilho);
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString(DiasDaSemana[DiaSemana - 1], LINHA2, 1, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(DiaSemana < 7)
				DiaSemana++;
			else
				DiaSemana = 1;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDString("                ", LINHA2, 0, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			LCDString(DiasDaSemana[DiaSemana - 1], LINHA2, 1, Brilho);
			Atraso = 500;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString(DiasDaSemana[DiaSemana - 1], LINHA1, 0, Brilho);
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Dia do mes: ", LINHA2, 1, Brilho);
	if(Dia > MesQtdDias[Mes])
		Dia = MesQtdDias[Mes];
	LCDNum(Dia, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Dia < MesQtdDias[Mes - 1])
				Dia++;
			else
				Dia = 1;
			LCDWr(COMANDO, 0x0C, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			LCDWr(COMANDO, 0x0F, Brilho);
			LCDNum(Dia, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Dia do mes: ", LINHA1, 0, Brilho);
	LCDNum(Dia, Brilho);
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho); 
	LCDString("Ano: 2", LINHA2, 1, Brilho);
	LCDWr(TEXTO, Cent + 48, Brilho);
	LCDWr(COMANDO, 0x10, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(Cent)
				Cent = 0;
			else
				Cent = 1;
			LCDWr(TEXTO, Cent + 48, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;	
	}
	while((PINC & (1 << PC0)) > 0)
		FPwm(Brilho);
	LCDWr(COMANDO, 0x14, Brilho);
	LCDWr(TEXTO, AnoTemp1 + 48, Brilho);
	LCDWr(COMANDO, 0x10, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(AnoTemp1 < 9)
				AnoTemp1++;
			else
				AnoTemp1 = 0;
			LCDWr(TEXTO, AnoTemp1 + 48, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;	
	}
	while((PINC & (1 << PC0)) > 0)
		FPwm(Brilho);
	LCDWr(COMANDO, 0x14, Brilho);
	LCDWr(TEXTO, AnoTemp2 + 48, Brilho);
	LCDWr(COMANDO, 0x10, Brilho);
	Prox = 0;
	while(!Prox)
	{
		FPwm(Brilho);
		wdt_reset();
		if((PINC & (1 << PC1)) > 0)
		{
			if(AnoTemp2 < 9)
				AnoTemp2++;
			else
				AnoTemp2 = 0;
			LCDWr(TEXTO, AnoTemp2 + 48, Brilho);
			LCDWr(COMANDO, 0x10, Brilho);
			Atraso = 800;
			while(Atraso)
			{
				FPwm(Brilho);
				Atraso--;
			}
		}
		if((PINC & (1 << PC0)) > 0)
			Prox = 1;	
	}
	LCDWr(COMANDO, 0x0C, Brilho);
	LCDClear(Brilho);
	LCDString("Ano: 2", LINHA1, 0, Brilho);
	LCDWr(TEXTO, Cent + 48, Brilho);
	LCDWr(TEXTO, AnoTemp1 + 48, Brilho);
	LCDWr(TEXTO, AnoTemp2 + 48, Brilho);
	LCDWr(COMANDO, LINHA2, Brilho);
	LCDWr(COMANDO, 0x0F, Brilho);
	LCDString("Voltando...", LINHA2, 1, Brilho);
	Temp = (Dia / 10) << 4;
	Temp += Dia % 10;
	Dia = Temp;
	Temp = (Mes / 10) << 4;
	Temp += Mes % 10;
	Mes = Temp;
	Mes += Cent << 7;
	Ano = AnoTemp1 << 4;
	Ano += AnoTemp2;
	TWIStart();
	TWIWrite(E_ENDW);
	TWIWrite(E_DIASEMANA);
	TWIWrite(DiaSemana);
	TWIWrite(Dia);
	TWIWrite(Mes);
	TWIWrite(Ano);
	TWIStop();
	EEPROMWr(0x00, Brilho);
	EEPROMWr(0x01, Piscar);
	LCDWr(COMANDO, 0x0C, Brilho);
}
//---------------------------------------------------------------------------
