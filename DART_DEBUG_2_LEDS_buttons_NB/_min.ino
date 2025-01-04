
  void midifeedback ()
  {
  
  {
    // read the incoming byte:
    

      if (incomingByte==241){  // this message opens the editor upload mode
      openeditor= !openeditor;
      if (openeditor == 1) 
      {
        editorcounter=0;

      } else {    
       load_preset_base();
       load_preset(page);        // load preset from eerom memory after upload     
    for(int led = 0; led < 8; led++)    {   
    bit_status[4][led]=0; bit_status[5][led]=0;
    bit_status[0][led]=0; bit_status[1][led]=0;    } // all leds and toggles off
    shifter.setAll(0); shifterwrite =0;
     }
     }
     
    else ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (   incomingByte>= 128 && incomingByte<= 191)
    {   action=1;
        type=incomingByte;
        if (openeditor==0){ 
           byte note_off_case; // se ricevo un note off devo farlo comportare come un note on velocity zero.
           if (incomingByte < 144 ) note_off_case =16; else  note_off_case =0;
           for(byte ledA = 0; ledA < max_modifiers*2; ledA++)   bit_write(2,ledA,(type+note_off_case==(typetable[ledA]))); 
           }
     }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
   /*       else if (incomingByte>= 160 && incomingByte<= 175){ // l'eftertouch serve per i LED!!!  32, come valore fuori range, per avere effetto ZERO.
      action=1;
      type=incomingByte;
      }*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////  
       else  if ( (action==0)&&(note==255) ){ // do nothing
      action=2;  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    else  if ( action==1 && note==255 ) { //  wait for the note (databyte)
      note=incomingByte;
      if (openeditor==0) 
      for( byte ledA = 0; ledA < max_modifiers*2; ledA++)        {       
          if (valuetable[ledA]== note ) bit_write(3,ledA,bit_read(2,ledA)); }
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
    else if ( (action==1)&&(note!=255) ){ // ...and then the velocity
    velocity=incomingByte;
///////////////////////////////////////////////////////////////////////////////////////////////////////////    
    if ( openeditor == 1 ) 
     eeprom_write();
     //-----------------------------------------------------------------------
     
 
 if (velocity!=0 && openeditor == 0)
 {
  if (type < 160) scale_learn(note); 
 
for(int ledD = 0; ledD < max_modifiers; ledD++) { // shifter.setPin(led, ledstatus2[led]);
    
if (valuetable[ledD]==note && bit_read(3,ledD) == 1   )  {
      bit_write(1, lightable[ledD], 1);  
     
      if (page==0) { shifter.setPin(lightable[ledD],1); shifterwrite=1; 
     // DmxSimple.write(dmxtable[ledD], velocity);
      }
      if (cycletimer < 3 ) {    // ogni volta che viene premuto pulsante previousmillis viene aggiornato... quindi il feedback funziona 30ms dopo che un pulsante è stato premuto
                            bit_write(4,ledD,1);      
                            if (modetable[ledD] >0 && modetable[ledD] < 11)   lastbutton[ledD]=1; } } // nb: lastbutton viene usato in modo diverso per pulsanti o pot! 
 
if (valuetable[ledD+max_modifiers]==note && bit_read(3,ledD+max_modifiers) == 1)  { 
      bit_write(1, lightable[ledD]+max_modifiers, 1);
     
      if (page!=0) { shifter.setPin(lightable[ledD],1); shifterwrite=1; 
    //  DmxSimple.write(dmxtable[ledD], velocity); 
      } 
      if (cycletimer < 3 ) {   //  delay for midi feedback-loops - avoids prblems with midi loops and doubled messages
                            bit_write(4,ledD+max_modifiers,1);
                            if (modetable[ledD] >0 && modetable[ledD] < 11)   lastbutton[ledD]=1;} }
  }  
 } 
 
 
if (velocity==0 && openeditor == 0){
      for(int ledE = 0; ledE < max_modifiers; ledE++) { // shifter.setPin(led, ledstatus2[led]);
      
if (valuetable[ledE]==note && bit_read(3,ledE) ==1    )    {   
   bit_write(1, lightable[ledE], 0); // ledstatus
   bit_write(3,ledE,0);              // feedback2
   if (page==0) { shifter.setPin(lightable[ledE],0); shifterwrite=1;}
      bit_write(4,ledE,0);              // toggletable
      if (modetable[ledE] >0 && modetable[ledE] < 11) lastbutton[ledE]=1;   } 
  
if (valuetable[ledE+max_modifiers]==note && bit_read(3,ledE+max_modifiers) ==1    )   {
   bit_write(1, lightable[ledE]+max_modifiers, 0); 
   bit_write(3,ledE+max_modifiers,0);  
   if (page!=0) { shifter.setPin(lightable[ledE],0); shifterwrite=1;  } //DmxSimple.write(dmxtable[ledE], 0);
      bit_write(4,ledE+max_modifiers,0);
      if (modetable[ledE] >0 && modetable[ledE] < 11)  lastbutton[ledE]=1; }    
      }      
    }     
      note=255; // out of range (0,127) value
      action=0;  
    }
    else{
      // nothing
    }   
  }  
  } 
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_preset_base() {
    for (int i = 0; i <max_modifiers; i++) {
  //typetable[i] = EEPROM.read(i);
//  valuetable[i] = EEPROM.read(i+64);
 // typetable[i+max_modifiers] = EEPROM.read(i+(512));
 // valuetable[i+max_modifiers] = EEPROM.read(i+64+(512));
 // lightable[i] = EEPROM.read(i+448);
 }
}

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     void load_preset(boolean numero) // numero is the page to load  - 0 1 
  {
     shifter.setAll(HIGH); shifter.write();
// if (numero > 0) numero = 1;

   for (byte i = 0; i <max_modifiers; i++) {
  //  modetable[i]= EEPROM.read(i+128+(numero*512));
    setup_mempos(i);
 // dmxtable[i]= EEPROM.read(i+192+(numero*512));
  if (i == mouse_mempos) {
 //   minvalue[i] = remapper(EEPROM.read(i+256+(numero*512))-1); 
 //   maxvalue[i] = remapper(EEPROM.read(i+320+(numero*512))-1);
    if (dmxtable[i] != 0) // quando vengono attivate le funzioni MOUSE, XY del joystick vengono impostate su BLIND INPUT - in tal modo si evitano conflitti
    {modetable[minvalue[mouse_mempos]] = 19;
    modetable[maxvalue[mouse_mempos]] = 19;}
  }
  else {
  //  minvalue[i]= EEPROM.read(i+256+(numero*512)); // if (dmxtable[mouse_mempos] == 2)
  //  maxvalue[i] =EEPROM.read(i+320+(numero*512));
  }
  
  // quando da editor si specifica la posizione su ircuito degli assi x e y - viene usato il remap da numerazione semplificata a numerazione normale
 //  if (i == mouse_mempos) maxvalue[i] = remapper(EEPROM.read(i+320+(numero*512))-1); else  maxvalue[i] =EEPROM.read(i+320+(numero*512));
// qwertyvalue[i] =EEPROM.read(i+384+(numero*512));
 

 }

    delay(5);
     shifter.setAll(LOW); shifter.write();
     test1();
       if ( general_mempos == 0)  aux_preset();
  }
  
  void update_scala(byte numero)
  {
    
  for (byte i = 0; i< 7; i++) {
bitWrite(scala[numero],i,  bitRead(valuetable[encoder_mempos[numero]] ,i)   );
bitWrite(scala[numero+2],i,  bitRead(valuetable[encoder_mempos[numero]+max_modifiers] ,i)   );
}
for (byte i = 0; i< 5; i++) {
bitWrite(scala[numero],i+7,  bitRead(maxvalue[encoder_mempos[numero]] , i)    );
bitWrite(scala[numero+2],i+7,  bitRead(maxvalue[encoder_mempos[numero]+max_modifiers] , i)    );
}

  }

  void setup_mempos (byte i)
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
  if ( modetable[i] == 26) general_mempos = i; 
  if (dmxtable[general_mempos] == 1) { modetable[45] = 19; modetable[47] =19;}
  
  }

 
 void aux_preset() // preset di base caricato all'avvio soltanto se il preset sulla eeprom non è valido. 
 {
   for (byte i = 0; i <max_modifiers; i++) {
    modetable[i]=1;
    valuetable[i+page]=60+i; // di default, tutte le note emesse sono uguali. in questo modo, se non si montano multiplexers,  ogni in triggera otto note, che essendo tutte uguali verranno filtrate dal midiout in una solo nota.
    minvalue[i]=0;
    maxvalue[i]=127;
    typetable[i]=144;
    }
 

// old boards
/*
   for (byte a = 0; a <4; a++) {
   for (byte i = 0; i <4; i++) {
   modetable[remapper(i+(a*8))]=0;   // non ci sono pot
   typetable[remapper(i+(a*8))]=176;}
   }
   */

 for (byte a = 0; a <8; a++) 
 {
  modetable[remapper(a+8)]=0;
  modetable[remapper(a+24)]=0;
  typetable[remapper(a+8)]=176;
  typetable[remapper(a+24)]=176;
  }

   
    general_mempos = 60;
    page_mempos=55;
    mouse_mempos = 59;
    encoder_mempos[0] = 57;
    dmxtable[encoder_mempos[0]] = 0; // no 2nd encoder
    encoder_mempos[1] = 56;
    lastbutton[encoder_mempos[0]] = 64;
    typetable[encoder_mempos[0]] = 176;
    touch_mempos[0] = 58;
    touch_mempos[1] = 59;
    maxvalue[general_mempos] = 1; // no pads
    valuetable[general_mempos] = 7; // multiplexers active!
    minvalue[general_mempos] = 0; // no extraplex
    dmxtable[general_mempos] = 0; // no 2nd encoder
    lightable[touch_mempos[0]] = 0; // no virtual touch
    lightable[touch_mempos[1]] = 0;
    dmxtable[mouse_mempos]= 0;
 }

 void eeprom_write()
 {
  {   
     switch (editorcounter) 
     {      
     case 0 : 

      
      if ( velocity < 56 ) memoryposition = remapper(velocity); 
      else if ( velocity < 64 ) memoryposition = velocity;
      else if ( velocity < 120 )memoryposition = remapper(velocity); 
      else  memoryposition = velocity;
    
       if (memoryposition < 64) {

       // i messaggi vengono posizionati in eeprom in tale ordine:
       // 0-65 = type   512
       // 64-128 = value  576
       // 128-192 = toggle mode 640
       // 192-256 = DMX  704
       // 256-320 = min 768
       // 320-384 = max 832
       // 384-448 = nel korova viene memorizzatoo il keyboard 896
       // 448-512   -    960 
       
 
   //     EEPROM.write(memoryposition+64,note); // value
       }
       else{
 //       EEPROM.write(memoryposition+512+64-64,note);  // value 2nd
         }
         
       
     break;
     
     
     case 1 :
     if (memoryposition < 64) {
  
   //      EEPROM.write(memoryposition+320,note);  // max
   //     EEPROM.write(memoryposition+256,velocity);     // min
 } else{
  //        EEPROM.write(memoryposition+512+320-64,note);  // max 2nd
 //       EEPROM.write(memoryposition+512+256-64,velocity);     // min 2nd
   }
   
 
    
  
     break;
  
  
     case 2 :
     if (memoryposition < 64) { 
     
 // EEPROM.write(memoryposition+128,note); // MODE
/*
 if (note == 26) // se arriva un general_mempos, mi assicuro che sia l'unico in memoria;

{ // byte anti_doubles;
  for (byte i =0; i< max_modifiers; i++)
{ if (i != memoryposition+128){ // anti_doubles == EEPROM.read(i+128);
// if (anti_doubles == 26) EEPROM.write(i+128,19);
if (EEPROM.read(i+128) == note) EEPROM.write(i+128,19);}  }
   }*/
  
// EEPROM.write(memoryposition+128+512-64,note);
 // EEPROM.write(memoryposition+192,velocity); // dmx memoryposition
//   Serial.print("-memorypos-scrivo-dmx1-");Serial.println(memoryposition);
//  Serial.print("-velocity-scrivo-dmx1-");Serial.println(velocity);
 // EEPROM.write(memoryposition+448,type-128); //     LED
 
 } else{
   
 
   
   
  
 //  EEPROM.write(memoryposition+128+512-64,note); // MODE 2ND

//  EEPROM.write(memoryposition+192+512-64,velocity); // dmx 2nd
//   Serial.print("-velocity-scrivo-dmx2-");Serial.println(velocity);
  // EEPROM.write(memoryposition+896,type-128); //              led
   }
     break;
   
   
     case 3 : 
     if (memoryposition < 64) {

 // EEPROM.write(memoryposition,type-176+(velocity*16)+144); // type // velocity è il miditype proveniente dall'editor numerato da 0 a 6 - viene moltiplicato per 16 e sistemato da 144 in poi a seconda del canale
 // type contiene ovviamente anche l'informazione del canale
  //   EEPROM.write(memoryposition+384,note); //    memorizzato a partire dalla posizione 384
 } else{


     //  EEPROM.write(memoryposition+512-64,type-176+(velocity*16)+144);  // type 2nd
       
  // EEPROM.write(memoryposition+384+512-64,note); //  trying not to cross memory limit - wertyvalue stored 64 memory slots before
 }
 
     break;
 
   }
     

     editorcounter++;
     if (editorcounter > 3) editorcounter = 0;
     
     shifter.setAll(HIGH); shifter.write();
     delay(5);
     shifter.setAll(LOW); shifter.write();
     }
 }
