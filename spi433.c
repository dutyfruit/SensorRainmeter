#include <xc.h>
#include "spi433.h"
#include "spiLCD.h"
#include "LCM12864.h"
#define SPI1433_MASTER_ETAT_INIT 0b11000000
#define SPI1433_MASTER_MODE_ON 0b00100000

void init_SPI433 (void){
TRISCbits.TRISC5= 0; //SDO1 en sortie
TRISCbits.TRISC4= 1; //SDI1 en entr?e
TRISCbits.TRISC3= 0; //CLK1 en sortie
TRISBbits.TRISB4= 0; // /CS1 en sortie
SSP1STAT = SPI1433_MASTER_ETAT_INIT; // etat inittial du SPI
SSP1CON1 = SPI1433_MASTER_MODE_ON; // SPI1 en mode master avec horloge F/16
CS_433 = 1;
CS_LCD = 0;
}

unsigned char Send_SPI4338( unsigned char data_out ){ 
  CS_433 = 0;
  SSP1BUF = data_out; 
  while( !SSP1STATbits.BF );
  CS_433 = 1;
  return ( SSP1BUF );   
}

unsigned int Send_SPI43316( unsigned int data_out ){
  unsigned int data_in;
  CS_433=0;
  SSP1BUF = data_out>>8; 
  while( !SSP1STATbits.BF );
	data_in =SSP1BUF;
  SSP1BUF = data_out; 
  while( !SSP1STATbits.BF );
	data_in =(data_in <<8)|SSP1BUF;
  CS_433=1;
  return ( data_in );   
}

unsigned int CRC16 (unsigned char * Modbus,unsigned int n_octets){ // Calcul crc16{
 unsigned char i,j;
 unsigned int C,CRC;
 C =0xFFFF;
 for (i=0;i<n_octets;i++)
    {
     C= C^*(Modbus++);
    for (j=0;j<8;j++)
        {if ((C&0x0001)==1)
            C=(C>>1)^0xA001;
        else C>>=1;
        }
    }
 CRC = ((C>>8)&0x00ff)|((C<<8)&0x00ff);
 Lcd_Writext ("CRC`=",7,5);
 Lcd_WriteInt (HEX_BCD(CRC),7,25,5,1);
 return (CRC);
}
  



