///////////////////////////////
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

void printchar(unsigned char);

////////////////////////////////

void setup() {
	*(myCLKPR) = 0x81; //prescale system clock by 2

	//set external memory functions to on and set wait to one cycle
	*(myXMCRA) = 0x84; 
	*(myXMCRB) = 0x00;

	*(myControl) = 0x82; //initializes all registers and modes

	Serial.begin(9600);
}

void loop() {
	printchar(0xFF);
	printchar(0x00);
}

void printchar(unsigned char in) { //simulates the printer function
	while((*(myPortB) & 0x80) != 0x00) {
		*(myPortA) = in;
		delayMicroseconds(3);
		*(myPortC) = 0xFB;
		delayMicroseconds(60);
		*(myPortC) = 0xFF;
		delayMicroseconds(3);
		*(myPortA) = 0x00;
	}
}


