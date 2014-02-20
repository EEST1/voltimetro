/*
 * File:   main.c
 * Author: Esteban Lemos
 *
 * Created on 5 de febrero de 2014, 20:49
 */


#include <xc.h>
#include "confbits.h"//archivo pruebaaaaaaaaaa

    

void main(void) {
    unsigned char flag = 0;
    TRISB = 0xFF;

    TRISDbits.RD0 = 0;
    LATDbits.LATD0 = 1;
while(1){
    if (PORTBbits.RB4 == 0 && flag == 0){
        if(LATDbits.LATD0 == 1)LATDbits.LATD0 = 0;
        else LATDbits.LATD0 = 1;
    flag =1;
    }
    if (PORTBbits.RB4 && flag == 1)flag = 0;
    
}

    return;
}
