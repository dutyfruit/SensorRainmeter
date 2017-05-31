/* 
 * File:   LCM12864.h
 * Author: thong
 *
 * Created on 30 mars 2017, 14:07
 */

#ifndef LCM12864_H
#define	LCM12864_H
extern void init_Lcd (void);
extern void Lcd_commande(unsigned char commande);
extern void Lcd_data(unsigned char data) ;
extern void Lcd_all (void);
extern void Lcd_Writext (unsigned char *chaine,unsigned char row,unsigned char col);
extern void Lcd_WriteInt (int N,char row,char col,char N_Chiffre,char Taille);
extern void Lcd_WriInvertext (unsigned char *chaine,unsigned char row,unsigned char col);
extern unsigned char HEX_BCD(unsigned char HEX);
extern void _delay_ms(unsigned int ms1); //delay of 10ms *
extern void Lcd_clear (void);
#endif	/* LCM12864_H */

