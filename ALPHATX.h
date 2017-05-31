#ifndef TRX_ALPHA_H

extern unsigned char  Send_FSK_DATA (char H,char L, unsigned int VAL);
extern void INIT_ALPHA_MODULE (void);
extern void  Wake_up (unsigned int temps_wk);
extern void  GPIO (void);
extern  unsigned int  RECEIVE_FSK_DATA ();

#define IRQ PORTBbits.RB0

#endif	/* TRX_ALPHA_H */
