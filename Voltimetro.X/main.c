#include <xc.h>
#include <adc.h>
#include <delays.h>
#include "Ap_ini.h"
#include "Lemos.h"
#include "confbits.h"

#define select_ADC(ch) { ADCON0 &= 0b11000011;  ADCON0 |= (ch<<2); }

unsigned int ADC_read(unsigned char ADC_channel)
 {
  unsigned int ad_res;
	   
  SetChanADC(ADC_channel);
  Delay10TCYx(5);
  ConvertADC();
  while(BusyADC());
  ad_res = ReadADC();
  return ad_res;
}

unsigned int ADC_read2(unsigned char ch){
    unsigned int ad_res;
    unsigned char   guardo_porta,guardo_trisa;

  //agregado por mi
    guardo_porta = PORTA;
    guardo_trisa = TRISA;
    
    TRISAbits.RA0=1;        //RA0 se transforma en AN0
 //   ADCON1 = 0x0E;          //selección de entradas analógicas
                            //canal 0 por defecto
 //   ADCON2 = 0x2D;
 //   ADCON0bits.ADON=1;
    select_ADC(ch);                                //SetChanADC(ADC_channel);
    Delay10TCYx(5);
    ADCON0bits.GO=1;                               //ConvertADC();
    while(ADCON0bits.GO);                          //while(BusyADC());  
    ad_res =ADRESH; ad_res<<=8; ad_res+=ADRESL;    //ad_res = ReadADC();  
  
  
  //ADCON1 = 0x0F;
    LATA = guardo_porta;
    TRISA = guardo_trisa;
  
    return ad_res;
}

unsigned int ADC_read2b(unsigned char ch)
 {
  unsigned int ad_res;
  unsigned char   guardo_porta,guardo_trisa;

  //agregado por lemos
    guardo_porta = PORTA;
    guardo_trisa = TRISA;
    
    TRISAbits.RA0=1;        //RA0 se transforma en AN0
 //   ADCON1 = 0x0E;          //selección de entradas analógicas
                            //canal 0 por defecto
 //   ADCON2 = 0x2D;
 //   ADCON0bits.ADON=1;
  
  
  
  select_ADC(ch);                                //SetChanADC(ADC_channel);
  Delay10TCYx(2);
  ADCON0bits.GO=1;                               //ConvertADC();
  while(ADCON0bits.GO);                          //while(BusyADC());  
  ad_res =ADRESH; ad_res<<=8; ad_res+=ADRESL;    //ad_res = ReadADC();  
  
  //ADCON1 = 0x0F;
  LATA = guardo_porta;
  TRISA = guardo_trisa;
  
  return ad_res;
}


void main(void) 
  {
    unsigned long fil=0,res2,res;           //variables para el filtrado
    unsigned char unimil=0,cen,dec,uni;     //variables para el display
    char cont=0;            //variable para el filtrado         
    pic_ini13();            //inicializa las ent/salidas del shield 1.3
    timer_ini13();          //inicializa el timer para habilitar
    INTCONbits.GIE = 1;     //comente esta línea para inhabilitar todas las int
    ei();                   //alternativa para habilitar interrupciones
    T0CONbits.TMR0ON = 1;   //enciendo el time0

//Configuracion del conversor AD-----------------------------------
    
    OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST,ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS,
            ADC_0ANA);
    
//primera lectura del conversor AD---------------------------------    
    
    res=ADC_read2b(0);      //lee los 10 bits y los coloca en un LONG
    
    while(1)
        {
  
  //FILTRADO-----------------------------------------------FILTRADO
        
        if(cont<200){
            fil=fil+ADC_read2b(0);
            //Delay10TCYx(10);
            cont++;
        }
        else {
        res=fil/200;
 //Conversion a milivolts------------------------------------------
        res2=res*5000;
        res=res2/1023;
        fil=0;
        cont=0;
        }
                  
        Send_4Disp(unimil,cen,dec,uni); //envía los cuatro números al display
        
//CONVERSION A BCD--------------------------------------------BCD--        
        
        unimil=res/1000;
        cen=(res%1000)/100;
        dec=(res%100)/10;
        uni=(res%10);
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