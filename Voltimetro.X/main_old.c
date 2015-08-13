/*
 * File:   main.c
 * Author: Esteban Lemos
 * Created on 5 de febrero de 2014, 20:49
 * En caso de necesitar el proyecto completo ingresar en
 * https://github.com/EEST1/Ap_template
 */
/*
 *Los LEDS  del shield están designados de izquierda a derechacomo LED1, LED2,
 *LED3 y LED4.
 *Los pulsadores de izquierda a derecha como BOT1, BOT2, BOT3, BOT4.
 *Para habilitar los displays de izquierda a derecha DISP1, DISP2, DISP3 y DISP4.
 *Para escribir un dato en el diplay se debe de escirbir en el nible menos
 *significativo del puerto A o usar la función Send_Disp(Nrodedisp , Dato)
 *El punto se controla con la variable DOT.
 */

#include <xc.h>
#include "confbits.h"   //no se debe de modificar este archivo para
                        //garantizar el funcionamiento del BOOTLOADER
#include"Ap_ini.h"      //define nombres para la entradas salidas del
                        //shield
#include"Lemos.h"       //funciones personalizadas Prof Lemos
#include <math.h>


# define _XTAL_FREQ  20000000   //para ser usado con la macro __delayms()


void main(void) {
    unsigned char valor_ad=0,cen,dec,uni;
    pic_ini13();                    //inicializa las ent/salidas del shield 1.3
    timer_ini13();                  //inicializa el timer para habilitar
    INTCONbits.GIE = 1;    //comente esta línea para inhabilitar todas las int
    ei();                  //alternativa para habilitar interrupciones
    T0CONbits.TMR0ON = 1;  //enciendo el time0

    while(1){   
        Send_4Disp(10,cen,dec,uni);    //envía los cuatro números al display
        //configurar el AD converter
        valor_ad = obtener_ADC8();
        cen=valor_ad/100;
        dec=(valor_ad%100)/10;
        uni=(valor_ad%100)%10;
        
        
        //Volver a configurar los puertos
    }
}

void __interrupt myISR(void){

#ifdef AP_INI_H
        if(TMR0IF){
            INTCONbits.TMR0IF = 0;  //borra el flag de la interrupción de timer
            TMR0L = 209;           //reinicia el time
            TMR0H = 0xFF;
            tic_timer0();           //llama a la función tic_timer

        }
#endif
}