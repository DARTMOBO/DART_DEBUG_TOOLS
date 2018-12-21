
void loop () {

if (cycletimer < 250 ) cycletimer++;
                                                  // USB MIDI in
   
  {

 for (byte i = 0; i < 16; i++) 
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
  }
   
   for (byte a = 0; a < 2; a++){
   for (byte i = 4; i < 8; i++) 
 {
  shifter.setPin(lightable[remapper(i+32+a*8)], 1);
  shifter.write();
  delay(100);
  }}
    
     for (byte a = 0; a < 2; a++){
   for (byte i = 4; i < 8; i++) 
 {
  shifter.setPin(lightable[remapper(i+32+a*8)], 0);
  shifter.write();
  delay(100);
  }}
  

// if (shifterwrite ==1) 
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
