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
  bool loop = false;
  while(!loop) {
    unsigned char input = 0x41; //'A' in ASCII 
  
    Serial.print("\nTEST\n");
  
    printchar(input);

    loop = true;
  }
}

void printchar(unsigned char in) {
  bool check = true;

  Serial.print("\n\nBEGIN...");

  while(check) {
    if(*(myPortB) == 0x00) { //check if busy at PB7
      *(myPortA) = in; //set input character to output
      *(myPortC) = 0x04; //set STROBE to high at PC3

      Serial.print("...STROBE_HIGH...BUSY_HIGH...\n");

      check = false;
    } else {
      //for(int i = 0; i < 10000; i++) {} //delay loop

      *(myPortB) = 0x00; //set BUSY to 0

      Serial.print("...BUSY_LOW...\n");
    }
  }

  *(myPortC) = 0x00; //set STROBE to low at PC3

  Serial.print("...STROBE_LOW...DONE\n\n");
}

