#ifndef TRXLALPHAV1_H
#define	TRXLALPHAV1_H
extern void INIT_ALPHA_MODULE (void);
extern void RE_INIT_ALPHA (void);
extern void  End_TX (void);
extern void  GPIO (void);
extern unsigned char  Send_FSK_DATA (char *Trame);
extern void ININT_INTERRUP_INTO (void);
extern void ININT_INTERRUP_TMR1 (void);
extern unsigned int  RECEIVE_FSK_DATA ();
extern void  Wake_up (unsigned int temps_wk);
void  tempo (unsigned char ms);
#define IRQ PORTBbits.RB0
#endif	/* TRX_ALPHA_H */
