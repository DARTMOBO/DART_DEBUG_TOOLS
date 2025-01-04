void noteOn(int cmd, int pitch, int velocity, byte filter) {
if (filter ==1){  if (cmd != old_cmd || pitch != old_pitch || velocity != old_velocity){

midiOut(cmd,pitch,velocity);
  
old_cmd = cmd; 
old_pitch =  pitch ;  
old_velocity = velocity;

} }
else midiOut(cmd,pitch,velocity);
}

void midiOut(int cmd, int pitch, int velocity) {

 Serial.write(cmd);
 Serial.write(pitch);
 Serial.write(velocity);

  //MIDIEvent noteOnn = {((cmd-144)/16)+9, cmd, pitch, velocity};
  //MIDIUSB.write(noteOnn);

//  midiEventPacket_t event = {((cmd-144)/16)+9, cmd, pitch, velocity};
//  MidiUSB.sendMIDI(event);
 // MidiUSB.flush();

}

void button (int cmd, int pitch, int velocity, byte filterr)
{
switch ((cmd-144)  /16)
{
 case 0 :   noteOn(cmd,pitch,velocity,filterr); break; // note
 case 1 :   noteOn(cmd,pitch,velocity,filterr); break; // poly AT
 case 2 :   noteOn(cmd,pitch,velocity,filterr); break; // cc
 case 3 :   noteOn(cmd,velocity,0,filterr); // pc
 case 4 :   noteOn(cmd,velocity,0,filterr);  break; // channel AT
 case 5 :  { noteOn(cmd,velocity,velocity,filterr); }
}
}


void outnucleo (byte onoff, byte chan_)
{
switch (onoff)
{
 case 1:
 if (qwertyvalue[chan_] == 0 )  {button(typetable[chan_+page],valuetable[chan_+page],maxvalue[chan_],1);
// DmxSimple.write(dmxtable[chan_], maxvalue[chan_]*2);
 }// 
 //    else if (qwertyvalue[chan_] < 25 ) Keyboard.press(qwertymod[qwertyvalue[chan_]]);  // qwertymod serve per mandare vari caratteri ascii che superano la soglia del 127 - si attivano con qwertyvalue sotto il 25 - tabella qwertymod
   //  else if (qwertyvalue[chan_] > 31 ) Keyboard.press(qwertyvalue[chan_]); // normale tabella ascii 
   //  else if (qwertyvalue[chan_] != 31 ) Mouse.press(qwertyvalue[chan_]-24);
     break;
     
 case 0: 
   if (qwertyvalue[chan_] == 0 ) { button(typetable[chan_+page],valuetable[chan_+page],minvalue[chan_],1); 
  // DmxSimple.write(dmxtable[chan_], minvalue[chan_]*2); 
   }
  //   else if (qwertyvalue[chan_] < 25 ) Keyboard.release(qwertymod[qwertyvalue[chan_]]); 
  //   else if (qwertyvalue[chan_] > 31 ) Keyboard.release(qwertyvalue[chan_]);
   //  else  if (qwertyvalue[chan_] != 31 ) Mouse.release(qwertyvalue[chan_]-24);   
     break;
  }
  
  }
