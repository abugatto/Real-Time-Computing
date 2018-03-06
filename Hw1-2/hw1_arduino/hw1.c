////////////////////////////////
//Pointer Declaration

//avr memories system clock
//enable global interrupts before initializing usart

/////////////////////

volatile unsigned char* myCLKPR = (unsigned char*) 0x61; //prescaler for system clock 

volatile unsigned char* myXMCRA = (unsigned char*) 0x74; //initialize special functiona
volatile unsigned char* myXMCRB = (unsigned char*) 0x75; //control wait states

//addresses of the 8255 
volatile unsigned char* myPortA = (unsigned char*) 0xC800;
volatile unsigned char* myPortB = (unsigned char*) 0xC801;
volatile unsigned char* myPortC = (unsigned char*) 0xC802;
volatile unsigned char* myControl = (unsigned char*) 0xC803;

////////////////////////////////

void setup() {
	*(myCLKPR) = 0x81; //prescale system clock by 2

	//set external memory functions to on and set wait to one cycle
	*(myXMCRA) = 0x84; 
	*(myXMCRB) = 0x00;

	*(myControl) = 0x82; //initializes all registers and modes
}

void loop() {
	unsigned char temp = *(myPortB);

	*(myPortA) = temp; //setting output of port A equal to input of port B
	*(myPortC) = temp; //setting output of port C equal to input of port B
}