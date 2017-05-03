/* 
 * File:   TIMER.c
 * Author: Duty-Gaming-Coding
 *
 * Created on 22 March 2017, 12:53
 */
#include <xc.h>   // utilisation de la biblioth�que 18F87J11




unsigned int N_AUGET (void)
{
   
   unsigned int NbAuget; // utiliser NbAuget comme variable 16 bits en nombre non sign?*
   NbAuget = 0;
   unsigned int i ;
   
   
   T1CON = 0b00110000; // voir la question Q12
   TMR1H = 0;
   TMR1L = 0; // valeur initiale du registre TMR1L (cr�ation un temps de 1 ms)
   PIR1bits.TMR1IF = 0;  // Mettre l?indicateur de //d�passement du timer 1 � 0
   for (i=0 ;i < 572; i++) // r�p�ter 9 fois
   {
      T1CONbits.TMR1ON = 1; // D�marrage du compteur/timer 1
	  while (PIR1bits.TMR1IF == 0); // tester le passage � 1 du bit //d?indicateur TMR1IF
      T1CONbits.TMR1ON = 0; // arr�t du compteur/timer 1
	  PIR1bits.TMR1IF = 0;  // Remettre l?indicateur de d�passement du //timer 1 � 0
   }
  // T0CONbits.TMR0ON = 0; // arr�t du compteur/timer 0
   TMR1H = 0x89;
   TMR1L = 0x71; 
   T1CONbits.TMR1ON = 1; 
   while (PIR1bits.TMR1IF ==0 ); // tester le passage � 1 du bit //d?indicateur TMR1IF 
   NbAuget = TMR0L;
   NbAuget =TMR0H;
   NbAuget = (NbAuget <<8)|TMR0L;
   return (NbAuget);
} 

void init_timer0 (void){
   TRISAbits.TRISA4 = 1; // 0 pour RA4 en sortie 1 pour RA4 en entr�e
   ANCON0bits.PCFG4 = 1; // PORTB en num�rique
   T0CON = 0b00111000;// initialisation du timer 0
   TMR0H = 0;
   TMR0L = 0;  // valeur initiale du registre TMR0L � 0
   T0CONbits.TMR0ON = 1; // D�marrage du compteur/timer 0
}