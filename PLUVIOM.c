/*
 * File:   PLUVIOM.c
 * Author: GOYAT JULIEN
 *
 * Created on 05 April 2017, 13:12
 */

#include <xc.h>
#include "LCM12864.h"
#include "TIMER1h.h"
#include "spi433.h"
#include "ALPHATX.h"
#include "spiLCD.h"


#pragma config WDTEN = OFF
#pragma config FOSC = HS
#pragma config XINST = OFF
#pragma config STVREN = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF

void main(void) {
  //******************************************************************************
  // CONFIGURE VARIABLES
  unsigned int i;
  unsigned int nPrecipitation;
  unsigned int nPrecipitation1;
  unsigned int nPrecipitation2;
  unsigned int nPrecipitation21;
  unsigned int nPrecipitation3;
  unsigned int nPrecipitation31;
  unsigned long NbAuget;
  NbAuget = 0;
  unsigned int tempe,CRC;
  void Emission (unsigned int Data);

  //******************************************************************************
  // WRITE ON LCD
  //init_Lcd ();
  //Lcd_Image (Bateau);
  //Lcd_Writext ("````LACROIX`ROUGE`BREST``",2,0);
  //_delay_ms(1000);
  //Lcd_clear ();

  init_Lcd ();
  Lcd_clear ();
  
  Lcd_Writext ("````PLUVIOMETRIE`",0,0);
  Lcd_Writext ("````LA`CROIX`ROUGE`BREST`",1,0);
  Lcd_Writext ("````PRECIPITATION`",3,0);

  while(1){
    init_timer0();
    NbAuget = N_AUGET(); // convertir la vitesse en valeur decimale//
    nPrecipitation = NbAuget * 2;// recupere la valeur des prï¿½cipitations
    nPrecipitation1 = nPrecipitation % 10;// valeur 10 ^-1
    nPrecipitation2 = (nPrecipitation % 10); 
    nPrecipitation21 = (nPrecipitation - nPrecipitation2) / 10;//valeur des unités 1
    nPrecipitation3 = (nPrecipitation %100);
    nPrecipitation31 = (nPrecipitation - nPrecipitation3) / 100;// valeur des dizaines 10
    
    Lcd_WriteInt (HEX_BCD(nPrecipitation31),5,15,1,1);
    Lcd_WriteInt (HEX_BCD(nPrecipitation21),5,26,1,1);
    Lcd_Writext ("<",5,34);
    Lcd_WriteInt (HEX_BCD(nPrecipitation1),5,42,1,1);
    Lcd_Writext ("`MM;H`",5,50);// en minute dans le projet pour le test 
    //Lcd_WriteInt (HEX_BCD(NbAuget),6,20,5,1);
    Emission (nPrecipitation);
    }
  }

  //******************************************************************************
  //*****************************************************************************
void Emission (unsigned int Data){
    unsigned long y;
    unsigned int CRC;
    unsigned char Trame[8] = {3,2,0,0,0,0,0,0};
    INIT_ALPHA_MODULE ();
    Trame[4] = Data<<8;
    Trame[5] = Data;
    CRC = CRC16(Trame,6);
    Trame[6] = CRC>>8;
    Trame[7] = CRC;
    //Lcd_WriteInt (HEX_BCD(CRC>>8),6,10,3,1);
    //Lcd_WriteInt (HEX_BCD(CRC&0x00ff),6,60,3,1);
    //Lcd_WriteInt (HEX_BCD(CRC),7,45,5,1);
    Send_FSK_DATA (Trame);
    for(y = 0 ;y < 600000; y++);
 }



