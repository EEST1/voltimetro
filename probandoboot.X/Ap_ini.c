#include <xc.h>
#include "Ap_Puertos.h"


void pic_ini(void){

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
void Send_Disp(unsigned char NroDisp,unsigned char Dato){

    LATA = 0;           //Borro el dato

    switch(NroDisp){
        case 1:{
            DISP1 = 1;
            DISP2 = 0;
            DISP3 = 0;
            DISP4 = 0;
        }break;
        case 2: {
            DISP1 = 0;
            DISP2 = 1;
            DISP3 = 0;
            DISP4 = 0;
        }break;
        case 3: {
            DISP1 = 0;
            DISP2 = 0;
            DISP3 = 1;
            DISP4 = 0;
        }break;
        case 4: {
            DISP1 = 0;
            DISP2 = 0;
            DISP3 = 0;
            DISP4 = 1;
        }break;
        default :{
            DISP1 = 1;
            DISP2 = 0;
            DISP3 = 0;
            DISP4 = 0;
        }break;
    }
    Dato &= 0x0F;   //borro el nibble superior
    LATA &= 0xF0;   //borro el nibble inferior
    LATA |= Dato;   //copio el nibble inferior de Dato en el puerto A
}
