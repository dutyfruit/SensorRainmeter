#include <xc.h>
#include "spi433.h"
#include "ALPHATX.h"

#define	TRX_ALPHA_H
#define CONF_TRX_433   0x80D8 // Valider TX RX REG 433
#define  PMC_INIT   0x8201 // INIT TX ET RX
#define CENTER_F  0xA640 // 434 MHz
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
enum {
     TXSYN1, TXSYN2,TXHEAD,TXLENGH,TXINTH,TXINTL,TXCRC1,TXCRC2,TXDONE,TXFIN,TXWAKUP
};

void End_TX (void);
void tempo (unsigned char ms);
void ININT_INTERRUP_INTO (void);
void ININT_INTERRUP_TMR1 (void);


static  volatile unsigned char rxstate;
static volatile unsigned char Flag;
static  volatile unsigned char Hdr;
static volatile unsigned char VALH;
static volatile unsigned char VALL;
static  volatile unsigned char Lengh;
static volatile unsigned char CCR1;
static  volatile unsigned char CCR2;
//******************************************************************************
// Interruption program at 0x08
//void high_isr (void);
//#pragma code high_vector=0x08
//void interrupt_at_high_vector(void)
//{
//_asm GOTO high_isr _endasm
//}



//******************************************************************************
// CONFIGURES ALPHA MODULE

void INIT_ALPHA_MODULE (void){

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
  //Send_SPI16 (STATUS_RX);
  //Send_SPI16 (PMC_INIT);
}

//******************************************************************************
unsigned char  Send_FSK_DATA (char H,char L, unsigned int VAL){

 unsigned int CRC;
 rxstate=0;

 //Send_SPI43316 (PMC_INIT);

 Send_SPI43316 (PMC_TXEN);
 Send_SPI43316 (PMC_TXEN_SYNTHEN);
 Hdr= 1;
 Lengh= 2;
 VALH=VAL >>8;
 VALL=VAL ;
 //CRC=CRC16 (H,L, VAL) ;
 CCR1=CRC>>8 ;
 CCR2=CRC ;

//ININT_INTERRUP_INTO ();
//ININT_INTERRUP_TMR1 ();
Send_SPI43316 (STATUS_RX);
ININT_INTERRUP_INTO ();
/*End_TX ();
Send_SPI43316(TX_2D);
End_TX ();
Send_SPI43316(TX_D4);
End_TX ();
Send_SPI43316 (0xB800|Head);
End_TX ();
Send_SPI43316 (0xB800|Lengh);
 End_TX ();
Send_SPI43316 (0xB800|(VAL>>8));
 End_TX ();
 Send_SPI43316 (0xB800|VAL);
 End_TX ();
 Send_SPI43316 (TX_AA);
 End_TX ();*/
//Send_SPI43316 (STATUS_RX);
//Send_SPI43316 (PMC_INIT);
 //Send_SPI43316 (STATUS_RX);
while (rxstate!=10);
 return (Flag);
}

//******************************************************************************
void  End_TX (void)
{//Send_SPI43316 (STATUS_RX);
 //while ((Send_SPI43316 (STATUS_RX)&0x8000)==0);
while (IRQ);
}
//******************************************************************************
void  GPIO (void){
 WDTCONbits.DEVCFG=1;
 ANCON0bits.PCFG4= 1;
 WDTCONbits.DEVCFG=0;
 TRISAbits.TRISA4=0;
 TRISBbits.TRISB0=1;
 RST = 0;
 tempo (100);
 RST=1;
 tempo (100);
 init_SPI433 ();
}
//******************************************************************************
void  Wake_up (unsigned int temps_wk)
{
 RST=0;
 tempo (50);
 RST=1;
 tempo (50);
 Send_SPI43316 (STATUS_RX);
 Send_SPI43316 (PMC_INIT);
 Send_SPI43316 (WAKUP_COMMAND);
 Send_SPI43316 (TIME_WAKUP|temps_wk);
 ININT_INTERRUP_INTO ();
 rxstate=TXWAKUP;
 while (rxstate!=TXSYN1);

}

//******************************************************************************
void  tempo (unsigned char ms){
unsigned char i;
for (i=0;i<ms;i++);
}

//******************************************************************************
unsigned int  RECEIVE_FSK_DATA (){

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


//******************************************************************************
//Init_Interrup INT0 falling Edge
void ININT_INTERRUP_INTO (void){
  RCONbits.IPEN=1;
  INTCON2bits.INTEDG0=0;
  INTCONbits.GIEH=1;
  INTCONbits.INT0IE=1;
  INTCONbits.INT0IF=0;
}

//******************************************************************************
//Init_Interrup INT0 falling Edge
void ININT_INTERRUP_TMR1 (void){
 RCONbits.IPEN=1;
 INTCONbits.GIEH=1;
 PIE1bits.TMR1IE=1;
 PIR1bits.TMR1IF=0;
 T1CON= 0b10110001;
 TMR1H=100;
 TMR1L = 200;
 T1CONbits.TMR1ON=1;
}
