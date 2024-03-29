#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>

#include "timer.h"



#define IN1 LATBbits.LATB9
#define IN2 LATBbits.LATB10
#define IN3 LATBbits.LATB11
#define IN4 LATBbits.LATB12
#define ENA LATDbits.LATD0
#define ENB LATDbits.LATD1


_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int broj1,broj2,brojac,i,k,j;
unsigned char ulazni_niz[10];
unsigned int napred=0;
unsigned int nista = 0;
unsigned int pocetno_napred = 0;
unsigned int pocetno_nista;


void __attribute__((__interrupt__)) _T2Interrupt(void)
{
 TMR2 =0;
 IFS0bits.T2IF = 0;
}
void __attribute__((__interrupt__)) _T3Interrupt(void)
{
 TMR3 =0;
 IFS0bits.T3IF = 0;
}


void initUART1(void)
{
    U1BRG=0x0040;//ovim odredjujemo baudrate

    U1MODEbits.ALTIO=0;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    IEC0bits.U1RXIE=1;//omogucavamo rx1 interupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//ukljucujemo ovaj modul

    U1STAbits.UTXEN=1;//ukljucujemo predaju
}


void pwmInit(void) {
//T2CONbits.TON = 0;//timer omogu?en
TRISDbits.TRISD0 = 0; //izlaz RD0(OC1) na ENA
TRISDbits.TRISD1 = 0; //izlaz RD1(OC2) na ENB
 //OC1CONbits.OCTSEL=0;// selektovanje TIMER2 za OC1
/*OC1CONbits.OCM=0b110; //PWM mod za OC1
OC2CONbits.OCTSEL = 0; //selektovanje TIMER2 za OC2
OC2CONbits.OCM = 0b110; //PWM mod za OC2*/

PR2 = 400;
OC1CON = OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE& T2_PS_1_1;//konfiguracija pwm-a
OC2CON = OC_IDLE_CON & OC_TIMER2_SRC & OC_PWM_FAULT_PIN_DISABLE& T2_PS_1_1;//konfiguracija pwm-a
OC1R=1000; //inicijalizacija faktora ispune 1
OC1RS=1000; //vrednost faktora ispune 1 na po?etku
OC2R = 1000; // inicijalizacija faktora ispune 2
OC2RS = 1000;// vrednost faktora ispune 2 na po?etku
T2CONbits.TON = 1;// timer onemogu?en
}



void kretanje_napred()
{
    IN1 = 1;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
    ENA = 1;
    ENB = 0;
    OC1RS = 280;
    OC2RS = 0;
}



void nema_kretanja(){
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
    ENA = 0;
    ENB = 0;
    OC1RS = 0;
    OC2RS = 0;
}





void upravljanje(void){
 if(pocetno_napred >= 3){
 napred = 1;
 pocetno_napred = 0;
 }
 else{
 napred = 0;
 }


 if(pocetno_nista >= 3){
 nista = 1;
 pocetno_nista = 0;
 }
 else
 nista = 0;
}


void __attribute__((__interrupt__)) _U1RXInterrupt(void) {
 tempRX=U1RXREG;

 ulazni_niz[brojac] = tempRX;


 brojac++;
 if(brojac >= 10){

 for(i = 0; i < brojac; i++){

    switch(ulazni_niz[i])
 {
 case 'p': //pravo
 pocetno_napred++;
 ulazni_niz[i] = 0;
 break;

 case 'n': //nista
 pocetno_nista++;
 ulazni_niz[i] = 0;
 break;

 default: //sum
 ulazni_niz[i] = 0;
 break;
 }
 }

 upravljanje();
 brojac = 0;

}

 IFS0bits.U1RXIF = 0;
}


void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;

}


int main(int argc, char** argv) {


    initUART1();
    pwmInit();
    ADPCFGbits.PCFG9 = 1;
    ADPCFGbits.PCFG10 = 1;
    ADPCFGbits.PCFG11 = 1;
    ADPCFGbits.PCFG12 = 1;

     TRISBbits.TRISB9 = 0; //IN1
    TRISBbits.TRISB10 = 0;  //IN2
     TRISBbits.TRISB11 = 0;  //IN3
    TRISBbits.TRISB12 = 0;  // IN4

    TRISDbits.TRISD0 = 0; //ENA
TRISDbits.TRISD1 = 0; // ENB


    while(1){
 if(napred == 1){
 kretanje_napred();
 }

 if(nista == 1){
 nema_kretanja();
 }


 }




   return (EXIT_SUCCESS);
}

