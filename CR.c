#include <xc.h>
#include "LCM12864.h"

unsigned int calculCRC (char *Trame, char n_octet)
{unsigned int CRC;
char i,j;
CRC = 0xFFFF;
 for (i=0;i<n_octet;i++)
    {CRC= CRC ^ *Trame;
    for (j=0;j<8;j++)
        {if ((CRC&0x0001)==1)
            CRC=(CRC>>1) ^ 0xA001;
        else CRC>>= 1;
        }
    Trame++;
    }
 
 CRC=((CRC>>8)|(CRC<<8));
return (CRC);

}
