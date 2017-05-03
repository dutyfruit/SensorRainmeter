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
  unsigned int NbAuget;
  NbAuget = 0;
  unsigned int tempe,CRC;
  char Trame[4] ={0,1,2,3};
  //******************************************************************************


  //******************************************************************************
  // WRITE ON LCD
  //init_Lcd ();
  //Lcd_Image (Bateau);
  //Lcd_Writext ("````LACROIX`ROUGE`BREST``",2,0);
  //_delay_ms(1000);
  //Lcd_clear ();
  init_Lcd ();
  Lcd_Writext ("````PLUVIOMETRIE`",1,0);
  Lcd_Writext ("````LACROIX`ROUGE`BREST``",2,0);
  Lcd_Writext ("````PRECIPITATION`",3,0);
  Lcd_Writext ("`",4,0);

  init_timer0();
    
  //Lcd_WriteInt (0x09,5,20,2,2);
  NbAuget = HEX_BCD(N_AUGET()); // convertir la vitesse en valeur decimale
  nPrecipitation = NbAuget * 2;// recupere la valeur des prï¿½cipitation
  Lcd_WriteInt (HEX_BCD(nPrecipitation),5,30,3,1);
  Lcd_Writext ("`microM;H`",5,60);
  //Lcd_data (((nPrecipitation>>4)&0x0f)+0x30); // convertir la dizaine en ASCII puis afficher sur LCD
  //Lcd_data ((nPrecipitation&0x0f)+0x30); // convertir l'unit?  en ASCII puis afficher sur LCD
  //******************************************************************************


  //******************************************************************************
  //(-,njjjjjjjjjjjjjjjjjjjjjjjjù^bghjFV>LY./09UYVV0l)ôc ^'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''=c x$)<^9BN999GFFFFFFFFFF7INIT EMETTEUR RADIO
  //GPIO ();
  //INIT_ALPHA_MODULE ();
  //while (1){
    //Wake_up (0x164);
    //CRC = CRC16 (4);
   // INIT_ALPHA_MODULE ();
   // Send_FSK_DATA (1,2,nPrecipitation);
 // }
  //******************************************************************************
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
