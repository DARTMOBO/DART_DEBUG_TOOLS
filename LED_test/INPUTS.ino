
 void AIN()
 { 
for( channel = 0; channel < 8; channel++)    
{ 
if (lastbutton[encoder_mempos[0]] == 64) // 64 = no encoder action - the MAIN spinner has priority over any other action.
{
  virtual_touch_end(0);
    
  if (maxvalue[general_mempos] == 0 ){ PADS();}  
 
  if (dmxtable[general_mempos] == 1)
{  
 senseEncoder_2nd(); 
 updateEncoder(1);
 encoder(1);
}
  //////////////////////////////////////////////////////////////////   
  setPlexer(channel); // all 4051's are set on the channel to be read
 for(plexer = 0; plexer < 5  +boolean(maxvalue[general_mempos]) // si si attivano i pads (maxvalue = 0) l'analogico A5 non viene letto
//  for(plexer = 0; plexer < 5
  ; plexer++) //  plexer 0,1,2,3,4 - the 5th plexer is read at higher speed (pads and 2nd encoder)
  {
    valore = analogRead(plexer);
   if (plexer+1 <= valuetable[general_mempos])  // se valuetabe[general_mempos] è 0, non verrà letto nessun multiplexer
   chan = channel + (plexer * 8) ;                                  // 46 - 48 - second encoder
   else 
   chan = plexer*8;
     ain_nucleo(); 
  }
  /////////////////////////////
 if (minvalue[general_mempos] > 0) 
  { 
    //valore = analogRead(9); 
    valore = 1000*(!digitalRead(9)); 
  if ( valuetable[general_mempos] >= 7) chan = channel + 48; else chan = 48;
  ain_nucleo();  }
  else virtual_touch_end(1); 
  
  }    
   else {
   encoder(0); // midiout 1st encoder
 //lastbutton[encoder_mempos[0]] = 64; // attivare questa riga se si disattiva encoder(0) - per fare test 
   }

   } // end PLEXER
   } // end ain

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   void ain_nucleo()
{
   if ( modetable[chan] == 0) {}
   else if ( modetable[chan] > 0 && modetable[chan]< 11) push_buttons();
   else if (modetable[chan  ] < 17)  pots(); 
   else if (modetable[chan] == 17)   { if (valore < 512) lastbutton[page_mempos] =0; else lastbutton[page_mempos] =1;} // page switch
   else if (modetable[chan] == 18) beam(); 

    mouse_control () ;
}

   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scale_learn(byte pitch)
{
   encodervaluepot[0] = pitch * 8;
   
   if (scala_reset == 1)
   for (byte i =0; i < scala_lenght; i++){
    scala_array[i] = 0;
    scala_learn= 0;
     scala_reset =0;  } 

   if (lastbutton[touch_mempos[0]] == 0 || lastbutton[touch_mempos[1]] == 0)  // se il touch è premuto/toccato
  {scala_array[scala_counter] = (pitch - (pitch/12)*12)+1; // 0 == nessuna nota,
  scala_counter++;
  if (scala_counter >= scala_lenght) scala_counter = 0;
  scala_learn =0;
  for (byte i =0; i< scala_lenght; i++)
  {
  // if (scala_array[i] != 0) 
   if (scala_array[i] >0 ) // 0 = nessuna nota da caricare nella scala
   bitWrite(scala_learn, scala_array[i]-1, 1);
    }
}
  }

   void offgroup (byte canale)
   {
     for (int i = 0; i <56; i++) {
// se i pulsanti sono nello stesso gruppo e sono accesi, spegnere lucetta e memorizzare status toggle

  if (modetable[i// +(page)
  ] == modetable[canale// +(page)
  ] && i!=canale) {

    
 if (
 bit_read(4,i) ==1
 || 
 //bit_read(5,i) ==1
 bit_read(4,i+max_modifiers) ==1
 )   
{

   outnucleo(0,i); // midiOut(typetable[i+(page)],valuetable[i+(page)],0);
   
// DmxSimple.write(dmxtable[i], 0);
 
 }
 
  
  shifter.setPin(lightable[i], 0); 
  
  bit_write(4,i+page,0);
 // bit_write(boolean(page),lightable[i],0);
 bit_write(1,lightable[i]+page,0);

  }
  
  
  
  
  }
}

void setPlexer( byte channel)
{
   // set the selector pins HIGH and LOW to match the binary value of channel
   for(byte bit = 0; bit < 3; bit++)
   {
      byte pin = select[bit]; // the pin wired to the multiplexer select bit
      byte isBitSet =  bitRead(channel, bit); // true if given bit set in channel
      digitalWrite(pin, isBitSet);
   }
}
 



