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
#include"Robello.h"     //funciones personalizadas prof Robello


# define _XTAL_FREQ  20000000   //para ser usado con la macro __delayms()


void main(void) {
    //Aquí debemos declarar todas las variables:
    unsigned char a=0,b=1;          //las variables locales deben de ser carga_
    unsigned char faon=0,faoff=0;   //das con un valor inicial, de lo contrario
    unsigned char fbon=0,fvel=0;    //contendrán valores aleatorios.
    unsigned int  velocidad = 100;
    
    pic_ini13();                    //inicializa las ent/salidas del shield 1.3
    timer_ini13();                  //inicializa el timer para habilitar
                                    //el multiplexado de displays
    //di();                         //descomente esta línea para inhabilitar
                                    //todas las interrupciones

    
    INTCONbits.GIE = 1;    //comente esta línea para inhabilitar todas las int
    ei();                  //alternativa para habilitar interrupciones
    T0CONbits.TMR0ON = 1;  //enciendo el time0

//
    while(1){   
    /* El siguiente es un programa de ejemplo, que utiliza la interrupción
     * de TIMER0 para multiplexar el display de 7 segmentos y eliminar el 
     * rebote de los pulsadores. Adicionalmente se observa el uso de la 
     * función Send_4Disp, que nos permite enviar información sin preocu
     * parnos de como esta luego llega al display.
     * Tener en cuenta que para que funcione el ejemplo deben de estar ha_
     * bilitadas las interrupciones, y se debe de inicializar el Timer tal cual
     * se muestra en timer_ini13.
     * */

        Send_4Disp(a,b,3,4);    //envía los cuatro números al display


     //lo siguiente es una prueba de botones 1 y 2
        if(!BOT1 && a < 9 && faon ==0 && !bot_tout){
            a++;
            faon = 1;
            bot_tout = BOT_REL;
        }
        if(BOT1 && faon == 1 && !bot_tout){
            faon=0;
            bot_tout = BOT_REL;
        }
        if(!BOT2 && a > 0 && faoff ==0 && !bot_tout){
            a--;
            faoff = 1;
            bot_tout = BOT_REL;
        }
        if(BOT2 && faoff == 1 && !bot_tout){
            faoff=0;
            bot_tout = BOT_REL;
        }
//Aquí se pruebam los Botones 3 y 4 mediante una secuiencia de LEDS
        if(!BOT3 && fbon ==0 && !bot_tout){
            b = ~b&(0x01);
            fbon = 1;
            bot_tout = BOT_REL;
        }
        if(BOT3 && fbon == 1 && !bot_tout){
            
            fbon=0;
            bot_tout = BOT_REL;
        }
        if(!BOT4 && fvel ==0 && !bot_tout){
            velocidad = velocidad + 100;
            fvel = 1;
            bot_tout = BOT_REL;
        }
        if(BOT4 && fvel == 1 && !bot_tout){

            fvel=0;
            bot_tout = BOT_REL;
        }

        if(b == 0x01) leds(velocidad);

        if(PORTBbits.RB4 == 0) velocidad =100;   
        
        //escriba el código aqui
    }
}

void __interrupt myISR(void){
    /*Aquí se ejecuta el código de las interrupciones que hayan sucedido,
     *por defecto el XC8 entra siempre en esta interrupción denominada de
     *Alta prioridad
     *NO OLVIDES DESCOMENTAR ei(), PARA HABILITAR LAS INTERRUPCIONES
     *
     */
    //el siguiente código verifica que el flag de TIMER0 esté habilitado
#ifdef AP_INI_H
        if(TMR0IF){
            INTCONbits.TMR0IF = 0;  //borra el flag de la interrupción de timer
            TMR0L = 209;           //reinicia el time
            TMR0H = 0xFF;
        #ifdef  LEMOS_H
            tic_timer0();           //llama a la función tic_timer
        #endif
        }
        #ifdef ROBELLO_H
            if(MEMDIG == 1)
                mux_display();
                TMR0IF = 0; //borra el flag de la interrupción de timer
            return;                     //termina el código de interrupción
        #endif

#endif
}
/*

void interrupt low_priority myLoIsr(void){
     *Aquí se ejecuta el código de las interrupciones que hayan sucedido,
     *si las mismas están marcadas como de BAJA prioridad, por ejemplo si
     *se ejecutan dos interrupciones se atenderá primero la de alta prioridad
     *NO OLVIDES DESCOMENTAR ei(), PARA HABILITAR LAS INTERRUPCIONES
     *    
    return;  
}
*/