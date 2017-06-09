#include <xc.h>
#include "spi433.h"
#include "spiLCD.h"
#define SPI1_MASTER_ETAT_INIT 0b01000000
#define SPI1_MASTER_MODE_ON 0b00100001
#define CS_LCD PORTCbits.RC2
#define CS_433 PORTBbits.RB4 

void init_SPI (void){
TRISCbits.TRISC5= 0; //SDO1 en sortie
TRISCbits.TRISC4= 1; //SDI1 en entr?e
TRISCbits.TRISC3= 0; //CLK1 en sortie
TRISCbits.TRISC2= 0; // /CS1 en sortie
SSP1STAT = SPI1_MASTER_ETAT_INIT; // etat inittial du SPI
SSP1CON1 = SPI1_MASTER_MODE_ON; // SPI1 en mode master avec horloge F/16
CS_433 = 1;
CS_LCD = 1;
}

unsigned char Send_SPI8( unsigned char data_out )
{  CS_433 = 1;
    CS_LCD=0;
  
  SSP1BUF = data_out; 
  while( !SSP1STATbits.BF );
  CS_LCD=1;
  return ( SSP1BUF ); 
    
}

unsigned int Send_SPI16( unsigned int data_out ){
  unsigned int data_in;
  CS_433 = 1;
  CS_LCD=0;
  SSP1BUF = data_out>>8; 
  while( !SSP1STATbits.BF );
  data_in =SSP1BUF;
  SSPBUF = data_out; 
  while( !SSP1STATbits.BF );
  data_in =(data_in <<8)|SSPBUF;
  return ( data_in );   
}



