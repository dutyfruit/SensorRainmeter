/* 
 * File:   PLUVIOM.c
 * Author: Duty-Gaming-Coding
 *
 * Created on 05 April 2017, 13:12
 */

#include <xc.h>
#include "LCM12864.h"
#include "TIMER1h.h"
#pragma config WDTEN=OFF
#pragma config FOSC=HS
#pragma config XINST=OFF
#pragma config STVREN=OFF

void main(void) {

unsigned int i;
unsigned int nPrecipitation; 
unsigned int NbAuget;
init_Lcd ();
//Lcd_Writext ("BCD",0,64);
//Lcd_clear ();
Lcd_Writext ("````PLUVIOMETRIE`",1,0);
Lcd_Writext ("````LACROIX`ROUGE`BREST``",2,0);
Lcd_Writext ("````PRECIPITATION`",3,0);
Lcd_Writext ("`",4,0);
init_timer0();
//Lcd_WriteInt (0x09,5,20,2,2);
NbAuget = HEX_BCD(N_AUGET()); // convertir la vitesse en valeur decimale
//nPrecipitation = NbAuget*0.2;// recupere la valeur des précipitation
Lcd_WriteInt (NbAuget,5,20,2,1);
Lcd_Writext ("`MM;H`",5,30);

//Lcd_data (((nPrecipitation>>4)&0x0f)+0x30); // convertir la dizaine en ASCII puis afficher sur LCD 
//Lcd_data ((nPrecipitation&0x0f)+0x30); // convertir l'unit?  en ASCII puis afficher sur LCD 
//i=0;
 while (1);
}

//init_Lcd ();
//Lcd_Writext ("BCD",0,64);
//Lcd_clear ();
//Lcd_Writext ("PLUVIOMETRIE`",1,0);
//Lcd_Writext ("BTS`SN`",2,0);
//Lcd_Writext ("PRECIPITATION`",3,0);
//Lcd_Writext ("`",4,0);
//Lcd_Writext ("`",5,0);
//Lcd_Writext ("````````DATA``MM[H`",6,0);
//for (i=0;i<1204;i++)
//{Lcd_data(0xFF) ;}