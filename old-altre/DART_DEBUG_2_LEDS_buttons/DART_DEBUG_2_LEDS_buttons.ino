

////////////////////////////
//
// DartMobo+Controlboards - Test Sketch - for Leonardo Board
// No preset uploading needed 
// MIDI in - No
// MIDI out - no
// 3xbuttonboards (korova style) can be tested
// 
// Massimiliano Marchese
// Piero pappalardo
// www.dartmobo.com
//
////////////////////////////


//#include <MIDIUSB.h>
// #include "DmxSimple.h"
//#include <EEPROM.h>
#include "Shifter.h"
// #include "CapacitiveSensor.h"
//#include <Mouse.h>
//#include <Keyboard.h>

//midiEventPacket_t rx;
 
//CapacitiveSensor   cs_4_3 = CapacitiveSensor(8,9);    
//CapacitiveSensor   cs_4_2 = CapacitiveSensor(8,7);


///////////////////////////////////////////////////////////////////////
const byte max_modifiers = 60;
const int maxbeam = 520;
const byte minbeam = 220;
///////////////////////////////////////////////////////////////////////

const byte encledtable[16] = { 4,5,6,7, 12,13,14,15, 3,2,1,0, 11,10,9,8,};

const byte  encledtable2[16]  = {11,10,9,8,60,60,60,60,8,9,10,11,0,1,2,3,};

const byte  encledtable3[16]  = {32,32,32,32,4,5,6,7,12,13,14,15,32,32,32,32};

const byte qwertymod[33] = { // da 0 a 24 ci sono i modificatori - da 25 a 32 controlli mouse
   
 0,   // niente 
 194, // f1
 195, // f2
 196, // f3
 
 197, // f4
 198, // f5 
 199, // f6
 200, // f7
 
 201, // f8
 202, // f9
 203, // f10
 204, // f11
 
 205, // f12
 215, // right arrow
 216, // left
 217, // down
 
 218, // up
 128, // left crtl
 129, // left shift
 130, // left alt
 
 178, // backspace
 176, // return
 177, // esc
 212, // delete
 };

const byte input_remap[] = {6,8,4,2,7,1,5,3,};
byte remapper(byte input) {return  ((input_remap[((input)-(((input)/8)*8))]+(((input)/8)*8))) -1;}

//|||||||||||||||||||||||||||||||||
const byte select[] = {4,5,6}; // pins connected to the 4051 input select lines

//|||||||||||||||||||||||||||||||||
byte channel;
byte plexer;
byte chan;
const int upper_val = 600;
const byte lower_val = 400;
int valore; // analog 0-1024 value for 4051 analog readings.
volatile byte potOut;
//||||||||||||||||||||||||||||||
byte mousex;
byte mousey;
// byte mouserall;
//int mouseyacceleration; // 
//int mousexacceleration; // 
byte mouse_wheel_speed_counter;
/////////////////////////////////////////////////////////////
volatile byte encoder_mempos[2];             // da editor si scegli quale sarà la memoryposition dell'encoder - la cosa rende più semplice creare un nuovo layout editor - masta mettere mode su encoder1
volatile byte touch_mempos[2];
byte V_touch_regulator[2] = {1,1};
byte mouse_mempos = 58;
byte PADS_mempos;
byte distance_mempos;
byte page_mempos;
byte general_mempos;
/////////////////////////////////////////////////////////////////////
byte page = max_modifiers ;

byte cycletimer;   /// conteggio di tempo in base ai cicli - serve per regolare effetti visivi led - e per il timing del virtualtouch

boolean openeditor;
byte editorcounter;
byte memoryposition;
byte type;
byte incomingByte;
byte note;
byte velocity;
byte action=2;

volatile byte old_cmd; // midi out doubles-filter, buffer variables 
volatile byte old_pitch;
volatile byte old_velocity;

byte padDecay[4];
byte padNum;
volatile  unsigned int padVal;  // 
volatile  unsigned int padVal2; // 
//////////////////////////////////////////////////////////////////////////////////
unsigned int readingsXen[3];      // the readings from the analog input
unsigned int readingsXen2[3];

const byte decaysensor_value = 8;
byte decaysensor[2]; //= decaysensor_value;
byte indexXen = 0;                  // the index of the current reading
unsigned int totalXen[2];                  // the running total
unsigned int averageXen[2];                // the average
byte lower_Xen[2];           // the average
//////////////////////////////////////////////////////////////////////////////////////


 byte buttonefx = 0; 
 byte buttonefxd = 0;
 byte buttonefxu = 0;
 byte shifterwrite = 1; // led refresh
 int encled; //  used for encoder led animation

//////////////////////////////////////////////////////////////////////////////////////
#define SER_Pin 10 //SER_IN
#define RCLK_Pin 11 //L_CLOCK
#define SRCLK_Pin 12 //CLOCK
#define NUM_REGISTERS 4 // how many registers are in the chain
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS);

//////////////////////////////////////////////////////////////////////////////////////
byte contoencoder;
byte lastEncoded[2] ;
int encodervaluepot[2] ;//sostituita con switchstate[encoder_mempos[numero]]
byte encodervaluepot_buffer[2];
volatile byte MSB[2] ; 
volatile byte LSB[2] ;

////////////////////////////////////////////////////////////////////////////////  
volatile byte lastbutton[64]; // used to record the previous state of a button - debounce
volatile byte lightable[65] // ho provato a scendere a 64 - ma si creavano stranissimi problemi di conflitto memoria con buttonled_efx - messaggi midi disordinati etc etc
               //la vecchia lightable era fissa.
 = { //40,
  0,1,2,3,4,5,6,7,
// 40,40,40,40,40,40,40,40,
//0,1,2,3,4,5,6,7,
40,40,40,40,40,40,40,40,
8,9,10,11,12,13,14,15,
40,40,40,40,40,40,40,40,
40,40,40,40,40,40,40,40,
40,40,40,40,40,40,40,40,
};


volatile byte bit_status[4][max_modifiers/4]; // bit_status è un multiarray che contiene le vecchie tabelle di riferimento per far funzionare il toggle, il feedback e i led

 // 1 - ledstatus 1 e 2
 // 2 - feedback_bit1
 // 3 - feedback_bit2
 // 4 - bit_toggle 1 e 2


volatile byte  valuetable[max_modifiers*2] ;
volatile byte  typetable[max_modifiers*2] ;
volatile byte  minvalue[max_modifiers] ;
volatile byte  maxvalue[max_modifiers] ;
volatile byte  modetable[max_modifiers] ; // 
volatile byte  qwertyvalue[max_modifiers];
volatile byte  dmxtable[max_modifiers];

 byte feedop2 (byte input) { // used in midi feedback bit operations
 return input/8; }

 byte bit_write(byte array_, byte posizione, byte stato)
 {  bitWrite(bit_status[array_-1][feedop2(posizione)],posizione-(feedop2(posizione)*8),stato); }

  byte bit_read( byte array_,byte posizione)
  { return bitRead(bit_status[array_-1][feedop2(posizione)],posizione-(feedop2(posizione)*8));  }
 //  byte scrivi_bool (boolean numero) {  Serial.print(numero);  }
  
///////////////////////////////////////////////////////////////////////////
byte pagestate = 0;
///////////////////////////////////////////////////////////////////////////

byte at; // serve per lo scale player
byte beam_scala_buffer;
byte beam_counter;
int scala[4];
int scala_learn;
byte scala_array[6];
const byte scala_lenght = 6;
byte scala_counter;
byte scala_reset;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void loop () {

if (cycletimer < 250 ) cycletimer++;
                                                  // USB MIDI in
/*  do {                                         
    rx = MidiUSB.read();
    if (rx.header != 0) {
 incomingByte  = rx.byte1; midifeedback();
 incomingByte  = rx.byte2; midifeedback();
 incomingByte  = rx.byte3; midifeedback();
    }
  } while (rx.header != 0);*/
                                                  // DIN MIDI in
 /* if (Serial.available() > 0) { 
  incomingByte = Serial.read();
  midifeedback();  } 
  else */
      
  //if (openeditor != 1)    
  {
   AIN();
 ///  buttonledefx();  
 //  pageswitch();     
 //  touch_sensors();
/* for (byte i = 0; i < 16; i++) 
 {
  shifter.setPin(encledtable[i], 1);
  shifter.write();
  delay(100);
  }
   for (byte i = 0; i < 16; i++) 
 {
  shifter.setPin(encledtable[i], 0);
  shifter.write();
  delay(100);
  }*/

 if (shifterwrite ==1) 
 {shifter.write(); shifterwrite=0;}
  }
 
}



 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////



void test1() // startup test code
{
// Serial.println(readingsXen[indexXen]); //
//delay (1000);
/*
    for(byte i =0; i < 60; i++)
{
  Serial.print(i);Serial.print("--");Serial.println(modetable[i]);
}
Serial.println("--");

*/
}

void test2() // touchsensors test code
{
//    Serial.print(averageXen[0]); Serial.print("--");  Serial.println(readingsXen[indexXen]); //delay (5);

// Serial.println(averageXen[0]); delay (5);
}

void test3() // on button pressure test code
{
 // if (chan == 0) {Serial.print(valore); Serial.println("--");}
   
   
   // Serial.print(averageXen[0]); Serial.print("--");  Serial.println(readingsXen[indexXen]); //delay (5);

//delay (1000);

 /*  for(byte i =0; i < 60; i++)
{
  Serial.print(i);
  Serial.print("m   ");
  Serial.print(modetable[i]);
  Serial.print("   :dmx");
  Serial.print(dmxtable[i]);
  Serial.print("   :eep   ");
  Serial.print(EEPROM.read(i+192));
    Serial.print("   :eep2   ");
  Serial.println(EEPROM.read(i+192+512));
}
  Serial.print("-----   ");
  */
  
//Serial.print("-encoder_mempos-");Serial.println(encoder_mempos[0]);
//Serial.print("eeprom-dmx-1--");Serial.println(EEPROM.read(58+192));
//Serial.print("eeprom-dmx-2--");Serial.println(EEPROM.read(58+192+512));

}
