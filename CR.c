#include <xc.h>
#include "LCM12864.h"

unsigned int calculCRC (char *Trame, char n_octet)
{unsigned int CRC;
char i,j;
CRC = 0xFFFF;
//Lcd_WriteInt (HEX_BCD(Trame[0]),6,5,4,1);
//Lcd_WriteInt (HEX_BCD(Trame[1]),6,35,4,1);
//Lcd_WriteInt (HEX_BCD(Trame[2]),6,65,4,1);
//Lcd_WriteInt (HEX_BCD(Trame[3]),6,95,4,1);
for (i=0;i<n_octet;i++){
    CRC= CRC ^ *Trame;
    for (j=0;j<8;j++){
        if ((CRC&0x0001)==1)
            CRC=(CRC>>1) ^ 0xA001;
        else CRC>>= 1;
    }
    Trame++;
}
 
CRC=((CRC>>8)|(CRC<<8));
//Lcd_Writext ("CRC`=",7,5);
//Lcd_WriteInt (HEX_BCD(CRC),7,25,4,1);
return (CRC);
}
