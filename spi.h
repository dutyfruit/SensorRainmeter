#ifndef __spi_H
#define __spi__H

extern void init_SPI (void);
extern unsigned char Send_SPI8( unsigned char data_out );
extern unsigned int Send_SPI16( unsigned int data_out );

#endif 


