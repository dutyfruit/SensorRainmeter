#include <xc.h>


unsigned int CRC16 ( unsigned int DAT )  { // Calcul crc16
static  volatile unsigned char  i,j,k;
unsigned int C;
static  volatile  unsigned char Trame[4];
 Trame[0] = DAT>>8;
 //Trame[3]=DAT;
 i=0;
 C = 0xFFFF;
 //for (i=0;i<4;i++)
    //{//C ^=Trame[];
 C = Trame[i];
 for (j=0;j<8;j++){
   if ((C&0x0001)==1)
     C=(C>>1)^0xA001;
   else C>>=1;
  //  }
 }
 return ((C>>8)|(C<<8));
}
