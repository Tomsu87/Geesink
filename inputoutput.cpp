/*
 * inputoutput.cpp
 *
 * Created: 2016-03-06 10:05:22
 *  Author: Tomek
 */ 



union outputs{
	struct{				// bit fielded structure to keep output status at bay, output placement is crucial to proper working, do not change array at will.
		uint8_t out1:1;
		uint8_t out2:1;
		uint8_t out3:1;
		uint8_t out4:1;
		uint8_t out5:1;
		uint8_t out6:1;
		uint8_t out7:1;
		uint8_t out8:1;
		uint8_t out9:1;
		uint8_t out10:1;
		uint8_t out11:1;
		uint8_t out12:1;
		uint8_t led1:1;
		uint8_t led2:1;
		uint8_t led3:1;
		uint8_t led4:1;
	};
	uint16_t collective_data;	// collective 16bit variable storing all statuses.
};


volatile outputs GlobalBitOutputs;		// Data package for keeping port bit statuses.

union inputs{
	struct{						// bit field numbers are sorted to fit hardware, do not change placement without hardware changes!
		uint8_t in8:1;
		uint8_t in7:1;
		uint8_t in6:1;
		uint8_t in5:1;
		uint8_t in4:1;
		uint8_t in3:1;
		uint8_t in2:1;
		uint8_t in1:1;
		uint8_t diag_in8:1;
		uint8_t diag_in7:1;
		uint8_t diag_in6:1;
		uint8_t diag_in5:1;
		uint8_t diag_in4:1;
		uint8_t diag_in3:1;
		uint8_t diag_in2:1;
		uint8_t diag_in1:1;
	};
	uint16_t collective_data;  // collective input data
};

volatile inputs GlobalBitInputs;  // 16bit variable storing all inputs.


uint8_t test, test2;

void Update_Outputs() {					// $$$$$$$$$$$$$$$$$$$$$$$$$  Sending global variable of output registers to hardware  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	
	uint16_t data_to_transfer;
	
	data_to_transfer=GlobalBitOutputs.collective_data;	// storage to avoid destroying global variable;
	
	for(register uint8_t i=16;i>0;i--){
		if (data_to_transfer>=0x8000){				// check highest bit in 16 bit register;
			r595data1;							// send one to shift reg.
			r595clk1;
			} else {
			r595data0;							// send zero to shift reg.
			r595clk1;
		}
		data_to_transfer=data_to_transfer<<1;		// move one bit up.
		r595clk0;
		r595data0;
		
	}
	
	r595latch1;										// latch and set data
	r595clk1;
	r595clk0;
	r595latch0;
	
}


void Update_Inputs() {

	uint8_t normal_inputs=0,diagnostic_inputs=0;
	
	for(register uint8_t i=0;i<8;i++) {
		if ((i<<7)>127) m4051adrA1;
		if ((i<<6)>127) m4051adrB1;
		if ((i<<5)>127) m4051adrC1;
		m4051inh0;
		if m4051input normal_inputs+=1;
		if m4051inputd diagnostic_inputs+=1;
		if (i<7) {
			normal_inputs=normal_inputs<<1;
			diagnostic_inputs=diagnostic_inputs<<1;
		}
		m4051adrA0;										//	 adress reset time
		m4051adrB0;
		m4051adrC0;
		m4051inh1;
	}
	
	GlobalBitInputs.collective_data=diagnostic_inputs;
	GlobalBitInputs.collective_data=GlobalBitInputs.collective_data<<8;   //  move into higher 8bits
	GlobalBitInputs.collective_data+=normal_inputs;
	

}
