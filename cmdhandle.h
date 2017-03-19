
// ################################################## Commands handling file #######################################################



void Comm_get_command(){
	
	if (!USART_get_data()) return;
	
	
	if ((Usart_buffer.data[0]=='c')&&(Usart_buffer.data[1]=='t')) {                 // ctXX handling.
		Usart_command_buffer.name[0]='o';
		Usart_command_buffer.name[1]='k';
		Usart_command_buffer.val1=Usart_buffer.data[3];
		Usart_command_buffer.val2=Usart_buffer.data[2];
		UART_send_command();
	}
	
	
	if ((Usart_buffer.data[0]=='o')&&(Usart_buffer.data[1]=='n')) {                 // onXX handling.
		uint16_t buffer;
		buffer=1;
		buffer=buffer<<Usart_buffer.data[3];
		if (Usart_buffer.data[2]) buffer=buffer<<10;
		GlobalBitOutputs.collective_data |= buffer;
		Update_Outputs();
		Usart_command_buffer.name[0]='o';
		Usart_command_buffer.name[1]='k';
		Usart_command_buffer.val1=Usart_buffer.data[3];
		Usart_command_buffer.val2=Usart_buffer.data[2];
		UART_send_command();
	}
	
	if ((Usart_buffer.data[0]=='o')&&(Usart_buffer.data[1]=='f')) {                 // ofXX handling.
		uint16_t buffer;
		buffer=1;
		buffer=buffer<<Usart_buffer.data[3];
		if (Usart_buffer.data[2]) buffer=buffer<<10;
		GlobalBitOutputs.collective_data &= ~buffer;
		Update_Outputs();
		Usart_command_buffer.name[0]='o';
		Usart_command_buffer.name[1]='k';
		Usart_command_buffer.val1=Usart_buffer.data[3];
		Usart_command_buffer.val2=Usart_buffer.data[2];
		UART_send_command();
	}
	
	
	if ((Usart_buffer.data[0]=='g')&&(Usart_buffer.data[1]=='i')) {                 // giXX handling.
		uint16_t buffer;
		buffer=1;
		
		Update_Inputs();
		
		
		Usart_command_buffer.name[0]='o';
		Usart_command_buffer.name[1]='k';
		buffer=GlobalBitInputs.collective_data;
		buffer/=256;
		buffer=buffer>>8;
		Usart_command_buffer.val1=buffer;
		buffer=GlobalBitInputs.collective_data;
		buffer=buffer<<8;
		buffer=buffer>>8;
		Usart_command_buffer.val2=buffer;
		UART_send_command();
	}
	
	
}
