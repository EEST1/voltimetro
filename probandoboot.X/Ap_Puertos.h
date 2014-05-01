/*
 * File:   Ap_Puertos.h
 * Author: Esteban Lemos
 *
 * Created on 27 de abril de 2014, 16:04
 */

#ifndef AP_PUERTOS_H
#define	AP_PUERTOS_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* AP_PUERTOS_H */

#define LED5    PORTDbits.RD0
#define LED6    PORTDbits.RD1
#define LED1    PORTDbits.RD2
#define LED2    PORTDbits.RD3
#define LED3    PORTCbits.RC6
#define LED4    PORTCbits.RC7

#define BOT1    PORTDbits.RD4
#define BOT2    PORTDbits.RD5
#define BOT3    PORTDbits.RD6
#define BOT4    PORTDbits.RD7

#define DISP1   PORTAbits.RA4
#define DISP2   PORTAbits.RA5
#define DISP3   PORTEbits.RE0
#define DISP4   PORTEbits.RE1
#define DOT     PORTEbits.RE2
#define MUX_SET 10;          //multiplicador de mux_tout
#define BOT_REL 100;         //multiplicador de BOT_REL

void pic_ini13(void);
void timer_ini13(void);
void Send_Disp(unsigned char NroDisp,unsigned char Dato);
void Send_4Disp(unsigned char Umil,unsigned char Cent,unsigned char Dec,unsigned char Uni);
void leds(unsigned int velocidad);
void tic_timer0(void);


unsigned char mux_tout,bot_tout;
unsigned int    led_tout;