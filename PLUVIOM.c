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
#include "CR.h"


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
  unsigned int nPrecipitation3;
  
  unsigned int NbAuget;
  NbAuget = 0;
  unsigned int tempe,CRC;
  char Trame[4] = {0,1,2,3};
  //******************************************************************************


  //******************************************************************************
  // WRITE ON LCD
  //init_Lcd ();
  //Lcd_Image (Bateau);
  //Lcd_Writext ("````LACROIX`ROUGE`BREST``",2,0);
  //_delay_ms(1000);
  //Lcd_clear ();
  
  init_Lcd ();
  Lcd_Writext ("````PLUVIOMETRIE`",0,0);
  Lcd_Writext ("````LA`CROIX`ROUGE`BREST`",1,0);
  Lcd_Writext ("````PRECIPITATION`",3,0);
  while(1){
  init_timer0();
 
  NbAuget = HEX_BCD(N_AUGET()); // convertir la vitesse en valeur decimale
  nPrecipitation = NbAuget * 2;// recupere la valeur des prï¿½cipitation
  
  nPrecipitation1 = nPrecipitation % 10;// valeur dizaine ^-1 
  nPrecipitation2 = (nPrecipitation % 100) / 10; //valeur des unités
  nPrecipitation3 = (nPrecipitation%1000) /100;//valeur des dizaines ^1
  
  Lcd_WriteInt (HEX_BCD(nPrecipitation3),5,20,1,1);
  Lcd_Writext ("`<`",5,34);
  Lcd_WriteInt (HEX_BCD(nPrecipitation2),5,27,1,1);
  Lcd_WriteInt (HEX_BCD(nPrecipitation1),5,38,1,1);
  Lcd_Writext ("`MM;H`",5,45);
  }
  //******************************************************************************


  //*****************************************************************************
  //GPIO ();
  //INIT_ALPHA_MODULE ();
  //while (1){
    //Wake_up (0x164);
    //CRC = CRC16 (4);
   // INIT_ALPHA_MODULE ();
   // Send_FSK_DATA (1,2,nPrecipitation);
 // }
  //******************************************************************************
  while(1);
}


