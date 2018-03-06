////////////////////////////////
//Pointer Declaration

//avr memories system clock
//enable global interrupts before initializing usart

/////////////////////

volatile unsigned char* myXMCRA = (unsigned char*) 0x74; //initialize special functiona
volatile unsigned char* myXMCRB = (unsigned char*) 0x75; //control wait states

//addresses of the 8255 
volatile unsigned char* myPortA = (unsigned char*) 0xC800;
volatile unsigned char* myPortB = (unsigned char*) 0xC801;
volatile unsigned char* myPortC = (unsigned char*) 0xC802;
volatile unsigned char* myControl = (unsigned char*) 0xC803;

////////////////////////////////

void set_wave();

void myDelay();

////////////////////////////////

void setup() {
  //set external memory functions to on and set wait cycles to 2x for I/O and 1x before new address call
  (*myXMCRA) = 0x88; // 0b(1000)(1000)
  (*myXMCRB) = 0x00;

  myControl = (unsigned char*) 0xC803;
  (*myControl) = 0x82; //initializes all registers and modes
}

void loop() {
  myPortB = (unsigned char*) 0xC801;
  unsigned char temp = *myPortB;

  set_wave(); //if needed initialize TTL wave from other port

  myPortA = (unsigned char*) 0xC800;
  (*myPortA) = temp; //setting output of port A equal to input of port B

  myPortC = (unsigned char*) 0xC802;
  (*myPortC) = temp; //setting output of port C equal to input of port B
}

void set_wave() {

}
