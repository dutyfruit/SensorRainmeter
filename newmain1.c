/* 
 * File:   newmain1.c
 * Author: Duty-Gaming-Coding
 *
 * Created on May 31, 2017, 8:59 AM
 */

#include <xc.h>
#include "TIMER1h.h"
#include "spi433.h"
#include "ALPHATX.h"
//#include "spiLCD.h"
//#include "font.h"
//#include "LCM12864.h"


#pragma config WDTEN = OFF
#pragma config FOSC = HS
#pragma config XINST = OFF
#pragma config STVREN = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF
void Emission (unsigned int Data);

void main(void) {
  //******************************************************************************
  // CONFIGURE VARIABLES
  INIT_ALPHA_MODULE ();
  while(1){
  Emission (6);
  }

}

void Emission (unsigned int Data){
    unsigned long y;
    unsigned int CRC;
    unsigned char Trame[8] = {3,2,0,0,0,0,0,0};
   
    
    Trame[4] = Data<<8;
    Trame[5] = Data;
    CRC = CRC16(Trame,6);
           
    Trame[6] = CRC>>8;
    Trame[7] = CRC;
    //Lcd_WriteInt (HEX_BCD(CRC>>8),6,10,3,1);
    //Lcd_WriteInt (HEX_BCD(CRC&0x00ff),6,60,3,1);
    //Lcd_WriteInt (HEX_BCD(CRC),7,45,5,1);
    Send_FSK_DATA (Trame);
    for(y = 0 ;y < 100000; y++);
 }
