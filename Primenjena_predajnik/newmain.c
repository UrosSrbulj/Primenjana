#include <stdio.h>
#include <stdlib.h>
#include<p30fxxxx.h>

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int broj1,broj2,komanda,i;

void initUART1(void)
{
    U1BRG=0x0040;//ovim odredjujemo baudrate

    U1MODEbits.ALTIO=0;//biramo koje pinove koristimo za komunikaciju osnovne ili alternativne

    IEC0bits.U1RXIE=1;//omogucavamo rx1 interupt

    U1STA&=0xfffc;

    U1MODEbits.UARTEN=1;//ukljucujemo ovaj modul



    U1STAbits.UTXEN=1;//ukljucujemo predaju
}

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;

} 

/*********************************************************************
* Ime funkcije      : WriteUART1                                     *
* Opis              : Funkcija upisuje podatak u registar 			 *
* 					  za slanje podataka U1TXREG,   				 *
* Parametri         : unsigned int data-podatak koji treba poslati   *
* Povratna vrednost : Nema                                           *
*********************************************************************/

void WriteUART1(unsigned int data)
{
	  while(!U1STAbits.TRMT);

    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    initUART1();
       ADPCFGbits.PCFG0 = 1;
   ADPCFGbits.PCFG1 = 1;
   ADPCFGbits.PCFG2 = 1;
   ADPCFGbits.PCFG3 = 1;
   ADPCFGbits.PCFG4 = 1;
   ADPCFGbits.PCFG9 = 1;
   ADPCFGbits.PCFG10 = 1;
   ADPCFGbits.PCFG11 = 1;
   ADPCFGbits.PCFG12 = 1;
   ADPCFGbits.PCFG5 = 1;
   ADPCFGbits.PCFG8 = 1;
   
   
   TRISBbits.TRISB0 = 1;
   TRISBbits.TRISB1 = 1;
   TRISBbits.TRISB2 = 1;
   TRISBbits.TRISB3 = 1;
   TRISBbits.TRISB4 = 1;
   TRISBbits.TRISB5= 1;
   TRISBbits.TRISB8 = 1;
   TRISBbits.TRISB9 = 1;
   TRISBbits.TRISB10 = 1;
   
   
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;


	while(1)
	{

        if(  PORTBbits.RB4 ==1 && PORTBbits.RB5 == 1 && PORTBbits.RB8 == 1 && PORTBbits.RB9 == 1 && PORTBbits.RB10 == 1 ){
        komanda = 0;
      
    
       
        }
        
for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++);


        if ( PORTBbits.RB4 == 0 ){
        LATBbits.LATB11 = 1;
        
       
       komanda = 1;
       }
        else
        {
            LATBbits.LATB11 = 0;
        }
          for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++);
            
            
              if ( PORTBbits.RB8 == 0 ){
        LATBbits.LATB12 = 1;
        komanda = 2;
       } 
         else{
             LATBbits.LATB12 = 0;
         }
            
        for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++);
            
            
            if( PORTBbits.RB10 == 0 ){
        LATDbits.LATD2 = 1;
        komanda = 3;
       }

   else{
         LATDbits.LATD2 = 0;
   }
     for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++);
            
            
            if( PORTBbits.RB9 == 0 ){
        LATDbits.LATD3 = 1;
        komanda = 4;
      }
 
   else{
        LATDbits.LATD3 = 0;
   }
            
          for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++);  
            
            
            
            if ( PORTBbits.RB5 == 0 ){
                
        LATDbits.LATD3 = 1;
          LATDbits.LATD2 = 1;
            LATBbits.LATB12 = 1;
            LATBbits.LATB11 = 1;
        komanda = 5;
      }
    else{
          LATDbits.LATD3 = 0;
           LATDbits.LATD2 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB11 = 0;
    }
            
            for(broj1=0;broj1<500;broj1++)
            for(broj2=0;broj2<1000;broj2++); 
        
            
            
        if (komanda == 5 )   {
           
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            for(i=0; i<1000; i++);
            WriteUART1('t');
            WriteUART1('t');
            WriteUART1('t');
            WriteUART1('t');
            WriteUART1('t');
    
            for(i=0; i<1000; i++); 
        }
     //od whilea
        
        else if(komanda == 1)
        {   
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
       
            for(i=0; i<1000; i++);
            WriteUART1('p');
            WriteUART1('p');
            WriteUART1('p');
            WriteUART1('p');
            WriteUART1('p');
           
            for(i=0; i<1000; i++);  
    }
        
        
        else if(komanda == 2)
        {       
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
          
            for(i=0; i<1000; i++);
            WriteUART1('r');
            WriteUART1('r');
            WriteUART1('r');
            WriteUART1('r');
            WriteUART1('r');
         
            for(i=0; i<1000; i++);  
    }
        
              else if(komanda == 3)
        {  
            WriteUART1('0');    
            WriteUART1('0');
           WriteUART1('0');
           
            WriteUART1('0');
            WriteUART1('0');
            for(i=0; i<1000; i++);
            WriteUART1('l');
            WriteUART1('l');
            WriteUART1('l');
            WriteUART1('l');
            WriteUART1('l');
           
            for(i=0; i<1000; i++);  
    }
       
        
              else if(komanda == 4)
        {   
           
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            for(i=0; i<1000; i++);
            WriteUART1('d');
            WriteUART1('d');
            WriteUART1('d');
            WriteUART1('d');
            WriteUART1('d');
            for(i=0; i<1000; i++);  
    }
        
        
              else if(komanda == 0)
        {     
                 
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            WriteUART1('0');
            for(i=0; i<1000; i++);
            WriteUART1('n');
            WriteUART1('n');
            WriteUART1('n');
            WriteUART1('n');
            WriteUART1('n');
           
        
    }
        
    }
                      return (EXIT_SUCCESS);

}