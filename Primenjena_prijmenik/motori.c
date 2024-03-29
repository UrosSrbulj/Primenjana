
#include <stdio.h>
#include <stdlib.h>
#include "motori.h"
#include <outcompare.h>
#include "timer.h"

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

void kretanje_nazad()
{
    IN1 = 0;
    IN2 = 1;
    IN3 = 0;
    IN4 = 0;
    ENA = 1;
    ENB = 0;
    OC1RS = 280;
    OC2RS = 0;
}

void kretanje_levo(){
    IN1 = 1;
    IN2 = 0;
    IN3 = 0;
    IN4 = 1;
    ENA = 1;
    ENB = 1;
    OC1RS = 280;
    OC2RS = 1800;
}

void kretanje_desno(){
    IN1 = 1;
    IN2 = 0;
    IN3 = 1;
    IN4 = 0;
    ENA = 1;
    ENB = 1;
    OC1RS = 280;
    OC2RS = 1800;
}

void kretanje_turbo(){
    IN1 = 1;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
    ENA = 1;
    ENB = 0;
    OC1RS = 330;
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