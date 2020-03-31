void setup()
{
 // Mouse.begin();

  #if (DMX_active == 1  && stratos == 0)
  DmxSimple.usePin(13);
  DmxSimple.maxChannel(64);
  #endif
  
   #if (stratos == 0)
   for(byte bit = 4; bit < 7; bit++) pinMode(bit, OUTPUT);  // set the three select pins to output  // 4051
   #endif
   
  // Serial.println("stratos" );
   
   for(byte bit = 0; bit < 64; bit++) lastbutton[bit]=1;


  #if (stratos == 0 ) 
    pinMode(2, INPUT);                             // ------------ encoder input settings
    pinMode(3, INPUT); 
    // pinMode(12, OUTPUT); 
    digitalWrite(2, HIGH); //turn pullup resistor on // encoder
    digitalWrite(3, HIGH); //turn pullup resistor on // encoder
    
    pinMode(0, INPUT);                             // ------------ midi over DIN settings
    digitalWrite(0, HIGH);
    #endif

 #if (pullups_active == 1)
 
  
  #if defined (__AVR_ATmega32U4__)
 #if (stratos == 0)
  // dartmobo pullups
  
{ digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);
  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
}

#endif
#if (stratos == 1)
// stratos pullups
{
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH); 
      
     digitalWrite(20, HIGH); // enc 2 // in analogici
    digitalWrite(21, HIGH);  
       digitalWrite(2, HIGH); // enc 1
    digitalWrite(3, HIGH); 

  
    pinMode(14, OUTPUT);    
    pinMode(15, OUTPUT); 
       pinMode(16, OUTPUT); 

    //  digitalWrite(8, HIGH);
   // digitalWrite(9, HIGH);   
}
#endif
  
  
  #endif

  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) 
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  #endif
  
 #endif

   
    #if defined (__AVR_ATmega32U4__)
    #if (stratos == 0)  
    Serial1.begin(31250); // midi specific baud rate
    
    #endif
    
    #endif
    
    #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) 
    Serial.begin(31250); // midi specific baud rate
    #endif
    

    
   attachInterrupt(0, lettura_enc_principale, CHANGE); 
   attachInterrupt(1, lettura_enc_principale, CHANGE);

 //#if (stratos == 1)
 //attachInterrupt(2, lettura_enc_principale2, CHANGE); 
 //attachInterrupt(3, lettura_enc_principale2, CHANGE);
 // #endif

   
//   ------------------------------------------- setting lower values fot touch sensors

/*
 #if (capacitivesensor_active == 1)
     
     
   for ( byte i = 0; i < Xenlimit; i++) 
   {
   touch_sensors();
   delay(5);
   }
    #endif
   
   lower_Xen[0] = averageXen[0];
   lower_Xen[1] = averageXen[1];
*/
   
  //  -----------------------------------------

 // aux = 0;
 //  maxvalue[general_mempos] = 10;

// page = 0;

#if (stratos == 0)
    load_preset_base();
    load_preset(0);
    #endif

   #if (stratos == 1)
  aux_preset();
  #endif


  
  /////////////////////////////////////////////////////////////////////

#if (stratos == 0 )
if (eeprom_preset_active == 1 && page_mempos > 0) // 1 = c'è un preset nella eeprom // eeprom_preset_active
{
  setPlexer((page_mempos)-((page_mempos/8)*8)); 
  lastbutton[page_mempos] = map(analogRead((page_mempos/8)), 0 ,1024, 0, 2); // read page switch state.

  
  if (lastbutton[page_mempos] == 1  )  {page = 0;  // pagestate=0; 
  load_preset(0); //ledrestore(); // levetta a destra caricamento preset eeprom pagina 1
 }
 else 
 {page= max_modifiers;   //pagestate=1; 
 load_preset(1);  //ledrestore2(); // levetta a sinistra preset 2
 } 

}

else 
 page = 0;
#endif



/*
delay(5);
readingsXen[0] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
readingsXen[1] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
readingsXen[2] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
delay(50);
readingsXen[0] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
delay(50);
readingsXen[1] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
delay(50);
readingsXen[2] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
*/
/*
for (byte i = 0 ; i < 200; i++)
{

 lettura = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
  delay(2);
  }
  readingsXen[0] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
   delay(2);
readingsXen[1] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);
 delay(2);
readingsXen[2] = (cs_4_2.capacitiveSensorRaw(limit_touch)/2);

*/
#if (stratos == 1)
 page = 0; // provvisorio
 #endif


 if (maxvalue[general_mempos] == 0 ){  // se i pads sono attivi bisogna togliere la pullup
 
 #if (stratos == 0)
  #if defined (__AVR_ATmega32U4__) 
  digitalWrite(23, LOW);
  #endif
  #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) 
  digitalWrite(19, LOW);
  #endif
 #endif

}  

if (valuetable[general_mempos] != 0) {
 digitalWrite(12, LOW);
  digitalWrite(11, LOW);
   digitalWrite(10, LOW);
}

// if (minvalue[general_mempos] > 0) digitalWrite(9, HIGH); // extraplex

 openeditor = 0;
 note = 255;  // out of range (0-127) value

 lastbutton[encoder_mempos[0]] = 64;

 
 
 }


 
 ////////////////////////////////////////////////////////////////////////////////////////////////



 void load_preset_base() {       //carica le variabili che devono restare in memoria indipendentemnte per le due pagine, per gestire il feedback. 
   
  for (int i = 0; i <max_modifiers; i++) {
  typetable[i] = EEPROM.read(i);
  valuetable[i] = EEPROM.read(i+64);
  typetable[i+max_modifiers] = EEPROM.read(i+(512));
  valuetable[i+max_modifiers] = EEPROM.read(i+64+(512));
  }
 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   void load_preset(boolean numero)
     
     // numero is the page to load  - 0 1 
     // carica le variabili dalla EEPROM alla memoria esecutiva, 
     ///secondo la pagina in cui ci si trova.
  {
    #if (shifter_active == 1 && stratos == 0)
     if (valuetable[general_mempos] == 0 ) {shifter.setAll(HIGH); shifter.write();} // flash di luci quando viene caricato il preset
    #endif
// if (numero > 0) numero = 1;

eeprom_preset_active = 0;

   for (byte i = 0; i <max_modifiers; i++) {
    
    modetable[i]= EEPROM.read(i+128+(numero*512));
    setup_mempos(i);                                // dopo aver caricato la modetable facciamo il settaggio macchina
    
  dmxtable[i]= EEPROM.read(i+192+(numero*512));
  if (i == mouse_mempos && mouse_mempos > 0) {
    minvalue[i] = remapper(EEPROM.read(i+256+(numero*512))-1); 
    maxvalue[i] = remapper(EEPROM.read(i+320+(numero*512))-1);
    
    if (dmxtable[i] != 0) // quando vengono attivate le funzioni MOUSE, XY del joystick vengono impostate su BLIND INPUT - in tal modo si evitano conflitti
    {modetable[minvalue[mouse_mempos]] = 27;
    modetable[maxvalue[mouse_mempos]] = 27;}
  }
  else {
    minvalue[i]= EEPROM.read(i+256+(numero*512)); // if (dmxtable[mouse_mempos] == 2)
    maxvalue[i] =EEPROM.read(i+320+(numero*512));
    if (modetable[i] == 21) lastEncoded[0] = maxvalue[i];
    if (modetable[i] == 22) lastEncoded[1] = maxvalue[i];
  }
  
  // quando da editor si specifica la posizione su ircuito degli assi x e y - viene usato il remap da numerazione semplificata a numerazione normale
 //  if (i == mouse_mempos) maxvalue[i] = remapper(EEPROM.read(i+320+(numero*512))-1); else  maxvalue[i] =EEPROM.read(i+320+(numero*512));
 qwertyvalue[i] =EEPROM.read(i+384+(numero*512));
 

 }
// if (mouse

    delay(5);
  #if (shifter_active == 1 && stratos == 0)
   if (valuetable[general_mempos] == 0 ) {shifter.setAll(LOW); shifter.write();}
  #endif
  
  
       if ( eeprom_preset_active == 0) // aux viene impostato su 1 dalla void setup_mempos richamata sopra - alla riga 194 - se ÃƒÂ¨ presente un general mempos.
       { aux_preset();
 
   
       }else  {   
        for (byte i = 0; i <max_modifiers; i++)  
       lightable[i] = EEPROM.read(i+448);
       
       }                        
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_mempos (byte i)  // richiamato da load_preset
  {
   
     if ( modetable[i] == 18) distance_mempos = i;
  //____________________________________________________________________________
  if ( modetable[i] == 21) {encoder_mempos[0] = i;update_scala(0);}
  if ( modetable[i] == 22) {encoder_mempos[1] = i;update_scala(1);}
  //______________________________________________________________________________
  if ( modetable[i] == 23) touch_mempos[0] = i;
  if ( modetable[i] == 24) touch_mempos[1] = i;
  if ( modetable[i] == 25) mouse_mempos = i;
  if ( modetable[i] == 20) PADS_mempos = i;
  if ( modetable[i] == 17) page_mempos = i; 
  if ( modetable[i] == 26) {general_mempos = i; eeprom_preset_active = 1;}
  if ( dmxtable[general_mempos] >  1) { modetable[45] = 0; modetable[37] =0;} // disattiva lo scanning sugli input dedicati al secondo encoder
  
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  
 

 #if (stratos == 0) // dart one
 void aux_preset() // preset di base caricato all'avvio soltanto se il preset sulla eeprom non Ã¨ valido. 
 {

   for (byte i = 0; i <max_modifiers; i++) {
    modetable[i]=1;
    valuetable[i+page]=    60+
    (i/8)*8; // di default, tutte le note emesse sono uguali. in questo modo, se non si montano multiplexers,  ogni in triggera otto note, che essendo tutte uguali verranno filtrate dal midiout in una solo nota.
    valuetable[i]=    60+
    (i/8)*8;
    minvalue[i]=0;
    maxvalue[i]=127;
    dmxtable[i]=0;
    qwertyvalue[i]=0;
    typetable[i]=144;
    typetable[i+page]=144;
    lightable[i]=remapper(i);
    }

 
    // nota: i modificatori normali vanno da 0 a 55 nel normale ciclo AIN e nelle tabelle array
    // rimangono solo 4 spazi liberi in teoria
    // ma bisogna considerare che : se l'extraplex è disattivato, tutti gli spazi da 48 a 55 sono disponibili
    // se si attiva il secondo encoder, gli slot di memoria relativi ai pin 46 e 48 (numerazione ciclo AIN) sono disponibili
    // se si attiva l'extraplex il secondo touch non ha bisogno di settaggio

    // nel default preset l'extraplex non viene attivato
   page_mempos=53; 
   mouse_mempos = 54;
   
   encoder_mempos[0] = 55;
   encoder_mempos[1] = 56;
   
    touch_mempos[0] = 57;        
    touch_mempos[1] = 58;
       
    general_mempos = 59;
    
  
    
     
   
    
    dmxtable[mouse_mempos]= 0; // disabilita il mouse
    
   
    dmxtable[encoder_mempos[0]] = 1; // encoder mode
    minvalue[encoder_mempos[0]] = 10;  // speed 
    lastbutton[encoder_mempos[0]] = 64;
    typetable[encoder_mempos[0]] = 176;
    typetable[encoder_mempos[1]] = 176;
    
  
    lightable[touch_mempos[0]] = 0; // no virtual touch
    lightable[touch_mempos[1]] = 0;
    typetable[touch_mempos[0]] = 144;
    typetable[touch_mempos[1]] = 145;
   // qwertyvalue[touch_mempos[0]]=0;
   // qwertyvalue[touch_mempos[1]]=0;
    minvalue[touch_mempos[0]] = 70;
    minvalue[touch_mempos[1]] = 70;
    
    qwertyvalue[general_mempos]=0; // no efx
    maxvalue[general_mempos] = 34; // no pads
    minvalue[general_mempos] = 0; // no extraplex
    dmxtable[general_mempos] = 2; // no 2nd encoder
    dmxtable[mouse_mempos] = 0; // no mouse emulation
    valuetable[general_mempos] = 0; // shifters & multiplexers active.
   
 }
 #endif
