/*
 * Geesink_Norba.cpp
 *
 * Created: 2015-11-25 00:08:20
 *  Author: Tomek
							Sterownik zabudowy G-N.
							12 kana≥Ûw wyjúciowych.
							8 kana≥Ûw wejúciowych.
							Komunikacja ze sterownikiem kabinowym
							RS 232.
							
 
 TODO - odbiÛr danych z 4051
 
 
 Przekaünik zasilajπcy wejúcia - PD6.
 Przekaünik zasilajπcy wyjúcia - PD7.
 
 
 */ 


#define ActivateInputs PORTD |= (1<<PD6)
#define ActivateOutputs PORTD |= (1<<PD7)
#define DeactivateInputs PORTD &= ~(1<<PD6)
#define DeactivateOnputs PORTD &= ~(1<<PD7)



#include <avr/io.h>				// in/out preload.
#include <avr/interrupt.h>


		//			$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Own libraries preload $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

#include <C:\Users\Tomash\Documents\Atmel Studio\7.0\Geesink Norba\Geesink Norba\uarthandling.h>
#include <C:\Users\Tomash\Documents\Atmel Studio\7.0\Geesink Norba\Geesink Norba\inputoutput.h>
#include <C:\Users\Tomash\Documents\Atmel Studio\7.0\Geesink Norba\Geesink Norba\cmdhandle.h>




uint8_t SelfTest(){
	
	DeactivateInputs;
	DeactivateOnputs;
	Update_Inputs();
	if (GlobalBitInputs.collective_data!=0) return 0;
	return 1;
	
}



// ########################################################## Main ###############################################################


int main(void)
{	
	
	DDRB=0xff;
	PORTB=0x00;
	DDRC=0x0F;
	PORTC=0x00;
	DDRD=0xff;
	PORTD=0x00;
	
	






	ActivateInputs;
	ActivateOutputs;
	GlobalBitOutputs.collective_data=0xfF;
	GlobalBitOutputs.led4=0;
	GlobalBitOutputs.led3=1;
	GlobalBitOutputs.led2=0;
	GlobalBitOutputs.led1=1;
	test = GlobalBitOutputs.collective_data;
	test2 = GlobalBitOutputs.collective_data>>8;

    while(1)
    {
		
	GlobalBitOutputs.led1=GlobalBitInputs.in1;
	GlobalBitOutputs.led2=GlobalBitInputs.in2;
	GlobalBitOutputs.led3=GlobalBitInputs.in3;
	GlobalBitOutputs.led4=GlobalBitInputs.in4;
		
	Update_Outputs();	
	Update_Inputs();
	
	Comm_get_command();
	
		
		
        //TODO:: Please write your application code	
		
		
    }
}