#ifndef __spi433_H
#define __spi433__H

extern void init_SPI433 (void);
extern unsigned char Send_SPI4338( unsigned char data_out );
extern unsigned int Send_SPI43316( unsigned int data_out );
extern unsigned int CRC16 (unsigned char * Modbus,unsigned int n_octets);  // Calcul crc16;  // Calcul crc16
#define CS_433 PORTBbits.RB4
#define CS_LCD PORTCbits.RC2
#endif
