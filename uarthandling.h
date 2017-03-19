//			Tomasz Luchowski presents:
//
//			UART handle library. Crafted for ATMega 8 family, portable.
//
//			Part of Hydraulics Controller.
//
//        ##################################################### Transmision protocol ##################################################################


#define baud_rate_value 51     // Sets baud rate value from table, max value 254, working only on UBRRL register.

struct data_buffer{
	uint8_t data[4];
	uint8_t byte_number;
};
volatile data_buffer Usart_buffer;

struct command_buffer{
	uint8_t name[2];
	uint8_t val1;
	uint8_t val2;
};
volatile command_buffer Usart_command_buffer;


void UART_init(){
	
	UBRRH = 0x00;
	UBRRL = baud_rate_value;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	Usart_buffer.byte_number=0;
	
};

ISR (USART_RXC_vect) {
	
	uint8_t recieved_char;
	recieved_char=UDR;
	if (recieved_char==13) { Usart_buffer.byte_number=5; } else
	{
		Usart_buffer.data[Usart_buffer.byte_number]=recieved_char;
		Usart_buffer.byte_number++;
	}
}

void UART_send_byte(uint8_t byte_to_send){
	while (! ( UCSRA& (1<<UDRE))); // poczekaj puki bufor zapchany
	UDR = byte_to_send;
}

//   TODO :   Zmienić sposób wysyłki komend.

void UART_send_command() {
	UART_send_byte(Usart_command_buffer.name[0]);
	UART_send_byte(Usart_command_buffer.name[1]);
	UART_send_byte(Usart_command_buffer.val1);
	UART_send_byte(Usart_command_buffer.val2);
	UART_send_byte(13);
	
}

uint8_t USART_get_data() {
	
	if (Usart_buffer.byte_number!=5) {				// jeżeli bufor nie pełny
		for (uint8_t counter=0;counter<250;counter++){
			for (uint8_t counter2=baud_rate_value; counter2>0; counter2--) {
				if (Usart_buffer.byte_number==5)    // jeżeli bufor się zapełnił
				{ 
					Usart_buffer.byte_number=0; 
					return 1; 
				}
			}
		}
	}
	if (Usart_buffer.byte_number==5)				// jeżeli bufor BYŁ pełny.
	{
		Usart_buffer.byte_number=0;
		return 1;
	}
	return 0;										// jeżeli nie dotarł pakiet
}



