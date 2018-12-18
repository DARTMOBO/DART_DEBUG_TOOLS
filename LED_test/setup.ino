void setup()
{
 // Mouse.begin();
 
 // DmxSimple.usePin(13);
 
 
  

  for(byte bit = 0; bit < 3; bit++) pinMode(select[bit], OUTPUT);  // set the three select pins to output
  
  pinMode(2, INPUT); 
  pinMode(3, INPUT); 
  pinMode(7, INPUT); 

  digitalWrite(2, HIGH); //turn pullup resistor on // encoder
  digitalWrite(3, HIGH); //turn pullup resistor on // encoder

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, lettura_enc_principale, CHANGE); 
  attachInterrupt(1, lettura_enc_principale, CHANGE);
  
  
 // cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
//   cs_4_3.set_CS_AutocaL_Millis(0xFFFFFFFF); 
     
 // cs_4_2.set_CS_Timeout_Millis(2) ;
 // cs_4_3.set_CS_Timeout_Millis(2) ;
   
   
//   ------------------------------------------- setting lower values fot touch sensors
   for ( byte i = 0; i < 6; i++) 
   {
   touch_sensors();
   delay(5);
   }
   lower_Xen[0] = averageXen[0];
   lower_Xen[1] = averageXen[1];
  //  -----------------------------------------
    

      
    pinMode(0, INPUT);                             // ------------ midi over DIN settings
    digitalWrite(0, HIGH);
  //  Serial.begin(31250); // midi specific baud rate
  
    buttonefx = 5; 
    buttonefxd = 8;
 
 /*   load_preset_base();
    load_preset(0);
  */

    
 //max_plexers = constrain((valuetable[general_mempos] //+constrain(maxvalue[general_mempos],0,1)-1
 //) , 0 ,6);

 // max_plexers viene usata all'interno di AIN - con questa formula avrà sempre un valore da 0 a 6 
 // senza niente nella eeprom il valore sarà 0 - quindi AIN funzionerà come se non ci fossero multiplexers attivati
 // for(int led = 0; led < 25; led++) {ledstatus[led]=0; ledstatus2[led]=0;}
   
 //  max_plexers_read = 5+ constrain(maxvalue[general_mempos],0,1); // usata al'interno del FOR principale di AIN - legge tutti gli input analogici, 
 // se i PADS sono attivati (maxvalue[general]>0  il conteggio arriferà a 6 - e la lettura degli input analogoci arriverà da A0 ad A5
  
  /////////////////////////////////////////////////////////////////////

 /* setPlexer((page_mempos)-((page_mempos/8)*8)); lastbutton[page_mempos] = map(analogRead((page_mempos/8)), 0 ,1024, 0, 2); // read page switch state.

  
  if (lastbutton[page_mempos] == 1  )  {page = 0;  // pagestate=0; 
  load_preset(0); //ledrestore(); // levetta a destra caricamento preset eeprom pagina 1
 }
 else 
 {page= max_modifiers;   //pagestate=1; 
 load_preset(1);  //ledrestore2(); // levetta a sinistra preset 2
 } 
 */


 openeditor = 0;
 note = 255;  // out of range (0-127) value

// test1();

  for(byte led = 0; led < max_modifiers; led++) { lastbutton[led]=HIGH; }
  lastbutton[encoder_mempos[0]] = 64;
  //  EEPROM.write(58+192,37);
}
