#include <xc.h>
#include "Ap_Puertos.h"


void pic_ini13(void){

    //Borrado de todos los puertos
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;

    //LEDS y pulsadores

    TRISD = 0xF0;       //RD0 a RD3 salidas RD4 a RD7 entradas
    TRISCbits.RC6 = 0;  //RC6 y RC7 salidas
    TRISCbits.RC7 = 0;

    //Display

    CMCON = 0x07;       //comparadores de entrada deshabilitados
    ADCON1 = 0x0F;      //Conversores AD deshabilitados
    TRISA = 0xC0;       //RA1 a RA5 salidas
    TRISE = 0x00;       //RE0 a RE2 salidas el resto no está implementado
}

void timer_ini13(){
    T0CONbits.TMR0ON = 0;   //apago el timer
    T0CONbits.T08BIT = 1;   //selecciono el timer en 8 bits
    T0CONbits.T0CS = 0;     //el timer cuenta fosc/4
    T0CONbits.PSA = 0;      //habilito el preescales
    T0CONbits.T0PS0 = 0;    //cargo el preescales con 128
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS2 = 1;
    TMR0L = 0xD9;           //el timer contará 39 fosc/4 * 128 = 4992 * 0,2us
    TMR0H = 0xFF;           //en total aprox 0.9984ms  casi 1ms
    INTCONbits.TMR0IE = 1;  //Habilita la interrupción de timer 0
}
void leds(unsigned int velocidad){
    static unsigned char i=1;


    switch(i){
        case 1:if(!led_tout){
            LED1=~LED1;
            led_tout = velocidad;
            i++;
        }
        break;
        case 2:if(!led_tout){
            LED2=~LED2;
            led_tout = velocidad;
            i++;
        }
        break;
        case 3:if(!led_tout){
            LED3=~LED3;
            led_tout = velocidad;
            i++;
        }
        break;
        case 4:if(!led_tout){
            LED4=~LED4;
            led_tout = velocidad;
            i++;
        }
        break;
        default : {
            led_tout = 1000;
            i=1;
        }

    }

}
void Send_Disp(unsigned char NroDisp,unsigned char Dato){

    LATA = 0;           //Borro el dato

    DISP1 = 0;
    DISP2 = 0;
    DISP3 = 0;
    DISP4 = 0;

    switch(NroDisp){
        case 1:{
            DISP1 = 1; 
        }break;
        case 2: {
            DISP2 = 1;      
        }break;
        case 3: {
            DISP3 = 1;
        }break;
        case 4: {
            DISP4 = 1;
        }break;
        default :{
            DISP1 = 1;
        }break;
    }
    Dato = Dato & 0x0F;   //borro el nibble superior
    LATA = LATA & 0xF0;   //borro el nibble inferior
    LATA = LATA | Dato;   //copio el nibble inferior de Dato en el puerto A
}

void Send_4Disp(unsigned char Umil,unsigned char Cent,unsigned char Dec,unsigned char Uni){

    static unsigned char Nro_Disp=1;

    switch(Nro_Disp){
        case 1:{
            if(!mux_tout){
                Send_Disp(1,Umil);
                mux_tout = MUX_SET;
                Nro_Disp = 2;
            }
        }
        break;
        case 2:{
            if(!mux_tout){
                Send_Disp(2,Cent);
                mux_tout = MUX_SET;
                Nro_Disp = 3;
            }
        }
        break;
        case 3:{
            if(!mux_tout){
                Send_Disp(3,Dec);
                mux_tout = MUX_SET;
                Nro_Disp = 4;
            }
        }
        break;
        case 4:{
            if(!mux_tout){
                Send_Disp(4,Uni);
                mux_tout = MUX_SET;
                Nro_Disp = 1;
            }
        }
        break;
        default :{
            mux_tout = MUX_SET;
            Nro_Disp = 1;
        }
    }
}
void tic_timer0(void){
    if(mux_tout)mux_tout--;
    if(bot_tout)bot_tout--;
    if(led_tout)led_tout--;
}
