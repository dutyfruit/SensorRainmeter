#include <xc.h>
#include "spi433.h"
#include "ALPHATX.h"
#include "LCM12864.h"
#define	TRX_ALPHA_H
#define CONF_TRX_433   0x80D8 // Valider TX RX REG 433 
#define PMC_INIT   0x8201 // INIT TX ET RX
#define CENTER_F  0xA7D0 // 435 MHz
#define BAUDS  0xC623 // 9600 BAUDS
#define RX_CONTROLE  0x90C0 // Bande reception 67 KHz
#define FILTER_DATA  0xC2AC //Filtre digital
#define FIFO_RST  0xCA83 
#define FIFO_RX  0xCA89 
#define STATUS_RX  0x0000 
#define AFC_COMMAND  0xC483 
#define DEVIATION_COMMAND  0x9820  //DEVIATION 45 KHz 
#define WAKUP_COMMAND  0x8203 
#define TIME_WAKUP  0xE000 
#define DUTY_COMMAND  0xC800 
#define BAT_COMMAND  0xC040 
#define SYNCHRO_COMMAND  0xCED4
#define PMC_RXEN 0x82D9 
#define PMC_TXEN 0x8229 
#define PMC_TX_DIS 0x8208 
#define PMC_TXEN_SYNTHEN 0x8239
#define RX_READ 0xB000
#define TX_AA 0xB8AA
#define TX_2D 0xB82D
#define TX_2D 0xB82D
#define TX_D4 0xB8D4
#define RST    PORTEbits.RE1


void INIT_ALPHA_MODULE (void){ 
 GPIO ();
 Send_SPI43316 (CONF_TRX_433);
 Send_SPI43316 (PMC_INIT);
 Send_SPI43316 (CENTER_F);
 Send_SPI43316 (BAUDS);
 Send_SPI43316 (RX_CONTROLE);
 Send_SPI43316 (FILTER_DATA);
 Send_SPI43316 (FIFO_RST);
 Send_SPI43316 (AFC_COMMAND);
 Send_SPI43316 (WAKUP_COMMAND);
 Send_SPI43316 (DUTY_COMMAND);
 Send_SPI43316 (BAT_COMMAND);	
 Send_SPI43316 (SYNCHRO_COMMAND);	
}

//******************************************************************************
unsigned char  Send_FSK_DATA (char *Trame){ 
       unsigned char i,n;
       // n=sizeof (Trame);
        Send_SPI43316(PMC_RXEN);// #RX powered and crystal on
        while ((Send_SPI43316(0x0000)&0x0001)==1);
        Send_SPI43316(PMC_TXEN) ;//#TX powered and crystal on
        Send_SPI43316(PMC_TXEN_SYNTHEN );// #TX powered and crystal synthetiser on
        Send_SPI43316(0x0000);
        End_TX ();
        Send_SPI43316(0xB82D);
        End_TX ();
        Send_SPI43316(0xB8D4);
        End_TX ();
        for (i=0;i<6;i++) 
        {  Send_SPI43316(0XB800|*(Trame++));
           End_TX ()  ;}    
        Send_SPI43316(0xB8AA);
        End_TX () ;
        Send_SPI43316(PMC_INIT);// # Stanby
        Send_SPI43316(0x0000);
        Send_SPI43316(0x8209);
        Send_SPI43316(0x00);       
}
//******************************************************************************
void  End_TX (void){//Send_SPI16 (STATUS_RX);
 //while ((Send_SPI16 (STATUS_RX)&0x8000)==0);
while (IRQ);
}
//******************************************************************************
void  GPIO (void){
 TRISEbits.TRISE1=0;
 TRISBbits.TRISB0=1;
 

 RST = 0;
 tempo (100);
 RST=1;
 tempo (100);
 init_SPI433();
}

//******************************************************************************
void  tempo (unsigned char ms){
unsigned char i;
for (i=0;i<ms;i++);
}

//******************************************************************************
unsigned int  RECEIVE_FSK_DATA ()
{ 
 unsigned  int dat;
 Send_SPI43316 (PMC_RXEN);
 Send_SPI43316 (FIFO_RX);
 Send_SPI43316 (FIFO_RST);
 Send_SPI43316 (STATUS_RX);
  while (IRQ);
  dat= Send_SPI43316( RX_READ);
  Send_SPI43316 (FIFO_RX);
  Send_SPI43316 (PMC_INIT);
 return (dat);
 
}

