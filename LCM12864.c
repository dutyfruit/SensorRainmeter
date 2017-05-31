/*
 * File:   LCM12864.c
 * Author: thong
 *
 * Created on 30 mars 2017, 11:11
 */


#include <xc.h>
#include "spi.h"
#include "LCM12864.h"
#include "font.h"
#define A0 PORTCbits.RC0
#define RST PORTCbits.RC1 
static unsigned char page_affiche[1024];
void Lcd_all (void){
    unsigned char i,j;
    unsigned int x;
    for (i=0;i<8;i++) 
    {     
         Lcd_commande (0xb0|i);// pointer ? la page
         Lcd_commande (0x00);
         Lcd_commande (0x10);
         for (x=0;x<128;x++)
          {Lcd_data(page_affiche[x+i*128]);
          }
    }
}
           

void init_Lcd (void){
    TRISCbits.TRISC0= 0;
    TRISCbits.TRISC1=0;
   // ANCON0bits.PCFG4=1;
    RST =0;
    _delay_ms(1);
    RST =1;
    _delay_ms(1);
    init_SPI ();
    Lcd_commande (0xa3);//biais 7
    Lcd_commande (0xa0);//affichage horizontal
    Lcd_commande (0xC8);//vertical reverse
    Lcd_commande (0xa0);//affichage horizontal
    Lcd_commande (0x50);//resistor
    Lcd_commande (0x2f);//power controle
    Lcd_commande (0x81);//volume mode
    Lcd_commande (30);//valeur de division R2/R1
    Lcd_commande (0x40);//START linge 0
    
    Lcd_commande (0xaf);//Lcd on
    
    
}

void  Lcd_commande(unsigned char commande){
    A0=0;
    Send_SPI8( commande);
}

void Lcd_data(unsigned char data) {
    A0=1;
    Send_SPI8(data);
}
            
            
void _delay_ms(unsigned int ms1){//delay of 10ms * x
  unsigned int ms,idx;
  for(ms=0; ms<ms1; ms++)
    {for(idx=0; idx<1000; idx++);}
}

void  Lcd_Writext (unsigned char *chaine,unsigned char row,unsigned char col){
    unsigned int index;
    unsigned char val,i;
    index=row*128+col;
    while (*(chaine)!=0)
    {
        i=0;
        val = *(chaine++)-48 ; 
        while (i<Font[val][0])
        {
            page_affiche[index+i]=Font[val][i+1];
            i++;
            //index=index+Font[val][0];   
        }
        index=index+Font[val][0];  
    }
    Lcd_all ();
}
void Lcd_WriteInt (int N,char row,char col,char N_Chiffre,char Taille)
{
    char i,j,N1;
    unsigned int index;
    index=row*128+col;
    for (i=0;i<N_Chiffre;i++)
    {
        j=0;
        N1=(N>>((N_Chiffre-(i+1))*4))&0x0f;
        if (Taille==1)
        {
            while (j<Font[N1][0])
            { page_affiche[index+j]=Font[N1][j+1];
                j+=1;}
            index=index+Font[N1][0];
            
        }
        else 
        {
            while (j<Font8x5[N1][0])
            {
                page_affiche[index+j]=Font8x5[N1][j+1];
                j++;
            }
            index=index+Font8x5[N1][0];
        }    
    }
     Lcd_all ();
}   

void Lcd_WriInvertext (unsigned char *chaine,unsigned char row,unsigned char col){
    unsigned int index;
    unsigned char val,i,j;
    index=row*128+col;
    page_affiche[index]=0xff;
    index++;
    i=0;
    while (i<sizeof(chaine))
    {
        j=0;
        val = *(chaine)-48 ; 
        while (j<Font[val][0])
        {
            page_affiche[index+j]=Font[val][j+1]^0xff;
            j+=1;
            index=index+Font[val][0];
            i+=1;
        }
    }
}

 unsigned char HEX_BCD(unsigned char HEX){
    unsigned int H;
    H+=((HEX>>4)&0x000f)*10;
    H+=HEX&0x000f;
    return H;
 }
 
void Lcd_Image (unsigned char *image){
    unsigned int i;
    for (i=0;i<256;i++)
    {
        Lcd_data(*(image++)) ;
    }
}
void Lcd_clear (void){
    int i;
    for (i=0;i<1024;i++)
    {page_affiche[i]=0;}    
}
