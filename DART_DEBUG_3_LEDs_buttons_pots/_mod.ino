void mouse_control () 
{
/*
  if (chan == minvalue[mouse_mempos] )   {// sezione mouse
  if  (dmxtable[mouse_mempos] == 1){  // 1 = attivazione mouse  
 mousex = 127 + (((valore+1)/64)-8) ; 
 Mouse.move( -(mousex-127), 0, 0);  }
 if (dmxtable[mouse_mempos] == 2) // 2 = attivazione freccette
 {
 if (valore>upper_val) { if (lastbutton[minvalue[mouse_mempos]] != 2) { Keyboard.press(216); lastbutton[minvalue[mouse_mempos]]=2;  }}
 else
 if (valore<lower_val) { if (lastbutton[minvalue[mouse_mempos]] != 0) { Keyboard.press(215); lastbutton[minvalue[mouse_mempos]]=0;  }}
 else { if (lastbutton[minvalue[mouse_mempos]] != 1) { Keyboard.release(215); Keyboard.release(216);  lastbutton[minvalue[mouse_mempos]]=1;}
 } 
 }
 }
 

   if (chan == maxvalue[mouse_mempos])  {
   if  (dmxtable[mouse_mempos] == 1) { 
   mousey = 127 + (((valore+1)/64)-8) ;
  Mouse.move( 0 , -(mousey-127), 0); }
  
 if (dmxtable[mouse_mempos] == 2)
 {
 if (valore>upper_val) { if (lastbutton[maxvalue[mouse_mempos]] != 2) { Keyboard.press(218); lastbutton[maxvalue[mouse_mempos]]=2;  }}
 else
 if (valore<lower_val) { if (lastbutton[maxvalue[mouse_mempos]] != 0) { Keyboard.press(217); lastbutton[maxvalue[mouse_mempos]]=0;  }}
 else { if (lastbutton[maxvalue[mouse_mempos]] != 1) { Keyboard.release(218); Keyboard.release(217);  lastbutton[maxvalue[mouse_mempos]]=1;}
 } 
 }
}
*/
}


void beam()  /////////////////////////////////////////// BEAM SENSOR
{

lightable[distance_mempos] 
 // beamValue 
  = constrain( map(valore, minbeam, maxbeam, 0, 127) , 0 , 127)  ;

  if ( qwertyvalue[chan] == 0 ) // se impostato su POT mode
  {

    if (valore > minbeam)  { // 119 a threshold to eliminate sensor's noise

      noteOn(typetable[chan + (page)], valuetable[chan + (page)], map(lightable[distance_mempos] , 0, 127, minvalue[chan], maxvalue[chan] ), 1); // MIDIUSB.flush();
   //   DmxSimple.write(dmxtable[chan], lightable[distance_mempos] *2);

      beamefx();

      shifterwrite = 1;
      lastbutton[distance_mempos] = 1;
    }

    else if (lastbutton[distance_mempos] == 1) {

      ledrestore(page);
      shifterwrite = 1;
      lastbutton[distance_mempos] = 0;
    }

  }

  else     /////////////
   if ( qwertyvalue[chan] == 1 )
  {                                                            // imppostazione note trigger
    if (valore > 300 && lastbutton[chan] == 1)  {
      lastbutton[chan] = 0;

      noteOn((typetable[chan + (page)]), valuetable[chan + (page)], lightable[distance_mempos] , 1 ); // MIDIUSB.flush();
      buttonefx = 5;
      buttonefxu = 5;
      buttonefxd = 8;
    }
    if (valore < 270 && lastbutton[chan] == 0) {
      noteOn((typetable[chan + (page)]), valuetable[chan + (page)], 0, 1 ); //  MIDIUSB.flush();
      lastbutton[chan] = 1;
    }

  }
  else //--------------------------------------------------- beam scale
 {
   if (beam_counter == 0 ){
    at = map(lightable[distance_mempos] , 0, 127, minvalue[chan], maxvalue[chan] );
    if ( beam_scala_buffer != at) // se è diverso dal precedente sgnale inviato - evitare doppioni e note ripetute
    {
  //if (dmxtable[contoencoder] == 2)
 // scala_learn = scala[((page/max_modifiers)*2)]; // se dmxtable è su 3 allora verrà usata la scala_learn
      if  ( bitRead(scala_learn, (at)-((at/12)*12)) == 1)  // scala_learn
      {
       beam_scale_send ();
      }
       else 
       {
        while ( bitRead(scala_learn, (at)-((at/12)*12)) == 0) 
        {
       // encoder_pot_calcolo(numero);
        at++;
        if ( at > 126) break;
       }
          if ( beam_scala_buffer != at) { beam_scale_send ();
    
        }
        }
     } 
 }


       beam_counter++;
 // if (mouse_wheel_speed_counter > abs(minvalue[contoencoder]-32)) mouse_wheel_speed_counter =0;
 if (beam_counter > 5) beam_counter =0;
  // if (cycletimer = 10) { button(typetable[distance_mempos+page],beam_scala_buffer,0 ,0); }
//  if (valore< minbeam || valore > maxbeam) if (beam_scala_buffer != at) { button(typetable[distance_mempos+page],beam_scala_buffer,0 ,0); beam_scala_buffer = at;}

    }

}

 void beam_scale_send ()
 {
            beamefx();
        button(typetable[distance_mempos+page],beam_scala_buffer,0 ,0);
        button(typetable[distance_mempos+page],at,127 ,1);  
        beam_scala_buffer= at;
        if (valore< minbeam || valore > maxbeam)  button(typetable[distance_mempos+page],beam_scala_buffer,0 ,0);
       // cycletimer = 0;
  }

void pageswitch(){ //----------------------------------------------------- PAGE SWITCH
  
  if (lastbutton[page_mempos] > 0  ) {     
  
  if (pagestate==1 ) { 
    page = 0;
//     load_preset_base();
    load_preset(page);
    update_scala(0);
    update_scala(1);
    shifter.setAll(LOW);
    shifterwrite=1;
    ledrestore(page);
  //  incomingByte = boolean(page);

midiOut(typetable[page_mempos],valuetable[page_mempos],minvalue[page_mempos]);
 
    shifterwrite=1;
    pagestate=0;
    
    lower_Xen[0] = max(averageXen[0], readingsXen[indexXen]); // min - serve a dare un ritocco in basso alla soglia del touchsensor.
    lower_Xen[1] = max(averageXen[1],readingsXen2[indexXen]);

    }
  } 
  
  
  if (lastbutton[page_mempos]==0  ){
 
 if (pagestate==0) {
      page = max_modifiers;
 
  midiOut(typetable[page_mempos],valuetable[page_mempos],maxvalue[page_mempos]);

    load_preset(page);
    update_scala(0);
    update_scala(1);
    shifter.setAll(LOW);
   shifterwrite=1;
    ledrestore(page);
   // incomingByte = boolean(page);


    shifterwrite=1;
    
   pagestate=1;
 
       lower_Xen[0] = max(averageXen[0], readingsXen[indexXen]);
    lower_Xen[1] = max(averageXen[1],readingsXen2[indexXen]);
 
  }
}
 }

 void PADS () { 
  { 
     padNum++;
    if (padNum > 3) padNum = 0 ;   
{
setPlexer(padNum*2);
padVal = analogRead(5);
 
if (padVal > 55 && padDecay[padNum] == 0 ) {
for(byte pad = 0; pad < 6; pad++)
  {
 setPlexer(padNum*2);
 padVal2 = analogRead(5);
  if (padVal2 > padVal) padVal = padVal2;
}
padDecay[padNum] =14 //+ (padVal / 40)
;
midiOut(typetable[PADS_mempos+(page)],valuetable[PADS_mempos+(page)]+(padNum*2),constrain(map(padVal,0,1024,0,127),0,127));

  buttonefx = 5;
    // buttonefxu = 5;
   buttonefxd = constrain((padVal/128), 0,3);
}
if (padDecay[padNum] >0) padDecay[padNum] = padDecay[padNum] -1;
   } 
   
    }
}


void touch_sensors() {
  if (decaysensor[0] > 0) decaysensor[0]--;
  if (decaysensor[1] > 0) decaysensor[1]--;

 // readingsXen[indexXen]  = cs_4_2.capacitiveSensorRaw(2);   // pin7
 // readingsXen2[indexXen] = cs_4_3.capacitiveSensorRaw(2); // pin9
 if (readingsXen[indexXen] > 20000)  readingsXen[indexXen] = 20000;
  if (readingsXen2[indexXen] > 20000)  readingsXen2[indexXen] = 20000;


  indexXen++; if (indexXen == 3) indexXen = 0;
  
  //totalXen[0]=  constrain (readingsXen[0] + readingsXen[1] +readingsXen[2], 0, 60000);
  totalXen[0]=  readingsXen[0] + readingsXen[1] + readingsXen[2];
  totalXen[1]= readingsXen2[0] + readingsXen2[1]+ readingsXen2[2];  
                     
  averageXen[0] = (totalXen[0] / 3) ;// / 3,2 ;    
  averageXen[1] = (totalXen[1] / 3) ;// / 3,2 ;    
  
test2();
   
 ///////////////////////////////////////////////////////////////////////////////////////////
if (lightable[touch_mempos[0]] == 0) 
touch_execute(0);
////////////////////////////////////////////////////////////////////////////////////////////////
  if (minvalue[general_mempos] == 0 && lightable[touch_mempos[1]] == 0)touch_execute(1); 
}

void touch_execute (byte numero) 
{
   {                                                     
 if (    averageXen[numero]<(lower_Xen[numero]
 //+100
 +(minvalue[touch_mempos[numero]]*4)
 
 ) 
 && decaysensor[numero] <= 0 
 && lastbutton[touch_mempos[numero]]==0) { 
 { noteOn(typetable[touch_mempos[numero]+(page)], valuetable[touch_mempos[numero]+(page)], 0,1); // MIDIUSB.flush(); 
decaysensor[numero] = decaysensor_value;
 //scala_learn =0; // resetta la scala che viene memorizzata tramite learn ogni volta che si tocca la wheel
//scala_reset = 1;

 if (typetable[encoder_mempos[numero]+page] < 160) 
 {
 button(typetable[encoder_mempos[numero]+page],encodervaluepot_buffer[numero],0 ,1);  // se encoder impostato su note allora manda il note off on release
 }
 
 if (qwertyvalue[touch_mempos[numero]] == 1)  // touch reset 
 { 
   encodervaluepot[numero] = dmxtable[touch_mempos[numero]]*8;   // se impostato su cc o altro - manda il touch reset
   button(typetable[encoder_mempos[numero]+(page)],valuetable[encoder_mempos[numero]+(page)],dmxtable[touch_mempos[numero]],1); // touch reset normale
 }
 
 

lastbutton[touch_mempos[numero]] = 1; encled=0; shifter.setAll(LOW);  if (page==0) ledrestore(0); else ledrestore(1);  shifterwrite=1; //shifter.write(); 
// opencalibration[1]=LOW;
}

} 


if (    averageXen[numero]> (lower_Xen[numero]
//+120

 +(maxvalue[touch_mempos[numero]]*4)

)  
 && decaysensor[numero] <= 0 
 && lastbutton[touch_mempos[numero]]==1
)
{decaysensor[numero] = decaysensor_value; 
scala_reset = 1;
mouse_wheel_speed_counter=0;
  noteOn(typetable[touch_mempos[numero]+(page)], valuetable[touch_mempos[numero]+(page)], 127,1);  // MIDIUSB.flush();  
lastbutton[touch_mempos[numero]] = 0;  //shifter.setAll(LOW); 
shifter.setPin(4+numero,HIGH); shifterwrite=1;};// opencalibration[1]=HIGH;
   } 
 
 }


 //----------------------------------------------------------------------------------------------------------------------------------
 void virtual_touch_end(byte numero)
{
  
      if (cycletimer == 10) 
      { 
      encled=0;
      shifter.setAll(LOW); 
      // utilizzo inomingbyte (boolean(page) - è na variabile normalmente utilizzata per il midi-in, per on creare nuove variabili la riutilizzo
      if (V_touch_regulator[numero] == 0 
      && lightable[touch_mempos[numero]] == 1)         // la casella lightable si usa per decidere se attivare o no il touch
      {midiOut(typetable[touch_mempos[numero]+page]+1,valuetable[touch_mempos[numero]+page],0);        // il virtual touch viene emesso - su un canale maggiorato di 1 rispetto al touch normale
              if (qwertyvalue[touch_mempos[numero]] == 1)  // 
              {encodervaluepot[numero] = dmxtable[touch_mempos[numero]]*8;  // posiziono encodervaluepot sulla giusta posizione da 0a1024
              button(typetable[encoder_mempos[numero]+page],valuetable[encoder_mempos[numero]+page],dmxtable[touch_mempos[numero]],0); 
              // se la modetable del touch è in toggle, avremo un virtual-touch-reset sul valore definito da DMXtable del touch.
                                }
     V_touch_regulator[numero]= 1; }
      
 
     ledrestore(page);  shifterwrite=1; // se l'encoder non gira più bisogna fare ledrestore
      }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
/*void encoder(byte numero) // 0= primary enc
{
 //    if (encoderValue == 0)
  if (lastbutton[encoder_mempos[numero]] != 64)
    { 
// previousMillis3 = currentMillis +140;
cycletimer = 0;

 if (V_touch_regulator[numero] == 1 &&  lightable[touch_mempos[numero]] != 0){ // spiegazione : switchstate[touch serve come regolatore anti-doppioni, lightable[touch serve come attivatore-disattivatore da editor, quando non si desidera la funzione virtual-touch
 midiOut(typetable[touch_mempos[numero]+page]+1,valuetable[touch_mempos[numero]+page],127); } // invio del virtual touch 

V_touch_regulator[numero] = 0; // lastbutton encoder 1 e 2 mempos si possono usare ...
      
 //contoencoder = 43+numero+(page); // per determinare a quale memory position fare riferimento
 contoencoder = encoder_mempos[numero] ;
 //-------------------------------------------------------------------------------------------------------------------------------
 
   if (dmxtable[contoencoder] > 1  )  // la dmxtable definisce la modalità - 0 e 1 endless - 2 e 3 pot e scale
 {  
  if (qwertyvalue[contoencoder]==0) encoder_pot_mode(numero);
  else if (lastbutton[touch_mempos[numero]]  ==0)    encoder_pot_mode(numero);                        // touch stop  
 }
 else                                                                                           // poly at, cc, pc, at 

 //-------------------------------------------------------------------------------------------------------------------------------
 // dmx : 0,1  =endless; 2= pot
 // qwerty: touchstop - 0 spento; 1=acceso; (non esiste touchstop virtuale)
 // min: speed e inversione - il valore va da 0 a 64 - 32 sarebe lo zero.
 // max: usato per trasferimento scale
 //-------------------------------------------------------------------------------------------------------------------------------
 { 
    if (minvalue[contoencoder] >= 32) { // normall or inverted?
    
    if (dmxtable[contoencoder]==0)      // modalità endless<63 >65
    // if (qwertyvalue[encoder_mempos[numero]] == 0) // touch stop no 
    {   button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
        lastbutton[encoder_mempos[numero]],0); }  
    else {button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
          constrain((lastbutton[encoder_mempos[numero]]-63)*64, 0,127),0);   }    
    encled = encled - (lastbutton[encoder_mempos[numero]]-64)*8 ; } // endless mode 0-127
   
  else{  // - minvalue sotto 32 inverte il funzionamento ----------------------------------------------------
    
  if (dmxtable[contoencoder]==0)     // modalità endless<63 >65
  {   button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
      -(lastbutton[encoder_mempos[numero]]-64)+64, 0);  } 
  else { 
   button(typetable[contoencoder+(page)]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+(page)], 
   constrain(-(lastbutton[encoder_mempos[numero]]-64)*127, 0,127),0);}
   encled = encled + (lastbutton[encoder_mempos[numero]]-64)*8; }
 }
//-------------------------------------------------------------------------------------------------------------------------------

   if (valuetable[mouse_mempos+page] == 1 ) {//Mouse.move(0,0,(encoderValue[numero]-64)); // l'encoder funziona come mouse wheel
   if (mouse_wheel_speed_counter == 0) Mouse.move(0,0,(lastbutton[encoder_mempos[numero]]-64)); // l'encoder funziona come mouse wheel
   mouse_wheel_speed_counter++;
   if (mouse_wheel_speed_counter ==  constrain (map(minvalue[contoencoder+page],0,8,32,1),1,32)) {
   mouse_wheel_speed_counter=0;
   }
   } 
led_enc_exe();
lastbutton[encoder_mempos[numero]] = 64; // 
} 
}
*/


void encoder(byte numero) // 0= primary enc
{

  if (lastbutton[encoder_mempos[numero]] != 64)
    { 
// previousMillis3 = currentMillis +140;
cycletimer = 0;

 if (V_touch_regulator[numero] == 1 &&  lightable[touch_mempos[numero]] == 1){ // spiegazione : switchstate[touch serve come regolatore anti-doppioni, lightable[touch serve come attivatore-disattivatore da editor, quando non si desidera la funzione virtual-touch
 midiOut(typetable[touch_mempos[numero]+page]+1,valuetable[touch_mempos[numero]+page],127); } // invio del virtual touch 

V_touch_regulator[numero] = 0; // lastbutton encoder 1 e 2 mempos si possono usare ...
      
 //contoencoder = 43+numero+(page); // per determinare a quale memory position fare riferimento
 contoencoder = encoder_mempos[numero] ;
 //-------------------------------------------------------------------------------------------------------------------------------
 
   if (dmxtable[contoencoder] > 1  )  // la dmxtable definisce la modalità - 0 e 1 endless - 2 e 3 pot e scale
 {  
  if (qwertyvalue[contoencoder]==0) encoder_pot_mode(numero);
  else if (lastbutton[touch_mempos[numero]]  ==0)    encoder_pot_mode(numero);                        // touch stop  
 }
 else                                                                                           // poly at, cc, pc, at 

 //-------------------------------------------------------------------------------------------------------------------------------
 // dmx : 0,1  =endless; 2= pot
 // qwerty: touchstop - 0 spento; 1=acceso; (non esiste touchstop virtuale)
 // min: speed e inversione - il valore va da 0 a 64 - 32 sarebe lo zero.
 // max: usato per trasferimento scale
 //-------------------------------------------------------------------------------------------------------------------------------
 { 
    if (minvalue[contoencoder] >= 32) { // normall or inverted?
    
    if (dmxtable[contoencoder]==0)      // modalità endless<63 >65
    // if (qwertyvalue[encoder_mempos[numero]] == 0) // touch stop no 
    {   button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
        lastbutton[encoder_mempos[numero]],0); }  
    else {button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
          constrain((lastbutton[encoder_mempos[numero]]-63)*64, 0,127),0);   }    
    encled = encled - (lastbutton[encoder_mempos[numero]]-64)*8 ; } // endless mode 0-127
   
  else{  // - minvalue sotto 32 inverte il funzionamento ----------------------------------------------------
    
  if (dmxtable[contoencoder]==0)     // modalità endless<63 >65
  {   button(typetable[contoencoder+page]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+page], 
      -(lastbutton[encoder_mempos[numero]]-64)+64, 0);  } 
  else { 
   button(typetable[contoencoder+(page)]+boolean(qwertyvalue[encoder_mempos[numero]])*lastbutton[touch_mempos[numero]],valuetable[contoencoder+(page)], 
   constrain(-(lastbutton[encoder_mempos[numero]]-64)*127, 0,127),0);}
   encled = encled + (lastbutton[encoder_mempos[numero]]-64)*8; }
 }
//-------------------------------------------------------------------------------------------------------------------------------

/*   if (  //valuetable[mouse_mempos+page] > 0 && 
   valuetable[mouse_mempos+page] == numero+1) {// l'encoder scelto funziona come mouse wheel - valuetable[mouse_mempos] sarà 0 = spento, 1 = mousewheel su main encoder, 2 = mousewheel su encoder secondario.
   if (mouse_wheel_speed_counter == 0)  //  mouse_wheel_speed_counter è un rallentatore
   Mouse.move(0,0,(lastbutton[encoder_mempos[numero]]-64)); // l'encoder funziona come mouse wheel
   
   mouse_wheel_speed_counter++;
   if (mouse_wheel_speed_counter ==  constrain (map(minvalue[contoencoder+page],0,8,32,1),1,32)) {
   mouse_wheel_speed_counter=0;
   }
   } */
led_enc_exe();
lastbutton[encoder_mempos[numero]] = 64; // 
} 
}

 
  void encoder_pot_mode (byte numero) {
 {  
  if (typetable[contoencoder+page] > 223 )  // pitch bend 
  {
    encoder_pot_calcolo(numero);
     noteOn(typetable[contoencoder + (page)], (encodervaluepot[numero] - ((encodervaluepot[numero] / 8) * 8)) * 16,  encodervaluepot[numero] / 8 , 1) ;
    }
  else if (typetable[contoencoder+page] > 159 )   // sotto il 160 sono note on e off
  {encoder_pot_calcolo(numero);
  button(typetable[contoencoder+page],valuetable[contoencoder+page],encodervaluepot[numero]/8 ,1);} // //
  else
  if (mouse_wheel_speed_counter == 0) // mouse_wheel_speed_counter
  {
    encoder_pot_calcolo(numero);
    at = encodervaluepot[numero]/8;
    
    if ( encodervaluepot_buffer[numero] != at) // se è diverso dal precedente sgnale inviato - evitare doppioni e note ripetute
    {
      
  if (dmxtable[contoencoder] == 2) scala_learn = scala[numero+((page/max_modifiers)*2)]; // se dmxtable è su 3 allora verrà usata la scala_learn
     if (scala_learn != 0) { if  ( bitRead(scala_learn, (at)-((at/12)*12)) == 1)  // scala_learn
      {
        button(typetable[contoencoder+page],encodervaluepot_buffer[numero],0 ,0);
        button(typetable[contoencoder+page],encodervaluepot[numero]/8,127 ,1);  
        encodervaluepot_buffer[numero]= at;
      }
       else 
       {
        while ( bitRead(scala_learn, (at)-((at/12)*12)) == 0) 
        {
        encoder_pot_calcolo(numero);
        at = encodervaluepot[numero]/8;
        if (at == 0 || at == 127) break;
       }
               button(typetable[contoencoder+page],encodervaluepot_buffer[numero],0 ,0);
        button(typetable[contoencoder+page],encodervaluepot[numero]/8,127 ,1);  
        encodervaluepot_buffer[numero]= at;
        }
    }
     } 
  }
  mouse_wheel_speed_counter++;
  if (mouse_wheel_speed_counter > abs(minvalue[contoencoder]-32)) mouse_wheel_speed_counter =0;

  encled = abs((encodervaluepot[numero]/4)-255);
 }
  }


 void encoder_pot_calcolo(byte numero)
 {
if (minvalue[contoencoder] >=32)  // inversione
encodervaluepot[numero] //encodervaluepot[numero]               
= (constrain(encodervaluepot[numero] + (lastbutton[encoder_mempos[numero]]-64)*abs(minvalue[contoencoder]-32), 0, 1023));  // byte encoderValue[2]- lastbutton[encoder_mempos[numero]]
else encodervaluepot[numero]
= (constrain(encodervaluepot[numero] - (lastbutton[encoder_mempos[numero]]-64)*abs(minvalue[contoencoder]-32), 0, 1023)); // - maxvlue sotto 127 inverte il funzionamento - minvalue è un moltiplicatore di ampiezza dello spostamento.
 }

 
void senseEncoder_2nd ()
{
switch (channel) { //// 2nd enc scanning
case 0 : { // MSB2 = map(getValue(5,5), 0 ,1024, 0, 2);//MSB = map(getValue(1,5), 0 ,1024, 0, 2);
setPlexer(5); //analogRead(multiplexer);
MSB[1] = map(analogRead(5), 0 ,1024, 0, 2);
};
case 2 : {  // LSB2 = map(getValue(7,5), 0, 1024, 0, 2);
setPlexer(7);
LSB[1] = map(analogRead(5), 0, 1024, 0, 2);
};

case 4 : { // MSB2 = map(getValue(5,5), 0 ,1024, 0, 2);
setPlexer(5); //analogRead(multiplexer);
MSB[1] = map(analogRead(5), 0 ,1024, 0, 2); };

case 6 : {//LSB2 = map(getValue(7,5), 0, 1024, 0, 2);
  setPlexer(7);
LSB[1] = map(analogRead(5), 0, 1024, 0, 2);

};
}

}





void lettura_enc_principale()
{
   MSB[0] = digitalRead(2); //MSB = most significant bit
   LSB[0] = digitalRead(3); //LSB = least significant bit
   updateEncoder(0);
}
  
void updateEncoder(byte numero)
{
    byte encoded = (MSB[numero] << 1) |LSB[numero]; //converting the 2 pin value to single number
    byte sum  = (lastEncoded[numero] << 2) | encoded; //adding it to the previous encoded value

    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) { 
    lastbutton[encoder_mempos[numero]]++;}
    if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) { 
    lastbutton[encoder_mempos[numero]]--;}

    lastEncoded[numero]= encoded; //store this value for next time
}

//---------------------------------------------------------------------------------------------------------------
  void push_buttons()
  {
    {


    if (valore < lower_val                            ///// button pushed
        && lastbutton[chan] == 1    
        ) {
      lastbutton[chan] = 0;
      if (modetable[chan] >= 3) offgroup(chan);
            if (bit_read(4,page+chan)==0)       
            { // something happens only if the button is off in the toggletable
            HOT_keys(chan,1);      
            outnucleo (1,chan);
            if (typetable[chan+page] < 160) scale_learn(valuetable[chan+page]);       
            ledControl(1);
            ledrestore(page);
         //   test3();     
            }
      cycletimer = 0;
      shifterwrite = 1;
    }

    
    if (valore > upper_val && lastbutton[chan] == 0)
    {
      lastbutton[chan] = 1;
 // test3(); 
     //  if (page == 0) 
      {
        if (modetable[chan] >= 2) { // se il pulsante Ã¨ in toggle o in uno dei gruppi
             if (bit_read(4,page+chan) == 1) { // se il pulsante è in toggle ed è acceso
             HOT_keys(chan,0);
             outnucleo (0,chan);
             ledControl(0);
             }      
          bit_write(4,chan+page,!bit_read(4,page+chan));        }  
             else {  // se il pulsante NON Ã¨ in toggle o in uno dei gruppi
             HOT_keys(chan,0);
             outnucleo (0,chan);
             ledControl(0);}
                    }

    /*  if (page != 0) {
        if (modetable[chan] >= 2) {
          if ( bit_read(4,max_modifiers+chan) == 1 ) {   
          HOT_keys(chan,0);
          outnucleo (0);
          ledControl(0); 
          }
          bit_write(4,max_modifiers+chan,!bit_read(4,max_modifiers+chan));   }
        else {
        HOT_keys(chan,0);
        ledControl(0);     }
      }*/
      shifterwrite = 1;
    }

   //  lastbutton[chan] = valore / 4;

  }  ////////////////////////////// PUSH BUTTON SECTION END
  }



//---------------------------------------------------------------------------------------------------------
 void HOT_keys (byte canale, byte pressione) // se un modificatore Ã¨ impostato su messaggio NOTA, il valore di minvalue (non utile per il note off) viene utilizzato per selezionare i modificatori qwerty 

{
 /*  if (minvalue[canale] > 0) { 
    if (pressione == 1) 
       switch (minvalue[canale]) {
       case 1:
       Keyboard.press(128); // CTRL left
       break;
       case 2:
       Keyboard.press(129); // shift left 
       break;
       case 3: 
         Keyboard.press(130); // alt left 
       break;
        case 4: 
         Keyboard.press(128);  Keyboard.press(129);// ctrl+shift left 
       break;
       case 5 :
         Keyboard.press(128);  Keyboard.press(130);// ctrl+alt left 
       break;
        case 6 :
         Keyboard.press(128);  Keyboard.press(129); Keyboard.press(130);// ctrl+alt left 
       break;
       }
       else 
       {
       switch (minvalue[canale]) {
       case 1:
       Keyboard.release(128); // CTRL left
       break;
       case 2:
       Keyboard.release(129); // shift left 
       break;
       case 3:
         Keyboard.release(130); // alt left 
       break;
        case 4: 
         Keyboard.release(128);  Keyboard.release(129);// ctrl+shift left 
       break;
       case 5 :
         Keyboard.release(128);  Keyboard.release(130);// ctrl+alt left 
       break;
            case 6 :
         Keyboard.release(128); Keyboard.release(130); Keyboard.release(130);// ctrl+alt left 
       break;
       }
       
       }
}
*/
}


void pots ()
{
  {
    
    if (abs((lastbutton[chan] * 4)  - valore) > 10

       )
    {


      if (modetable[chan] ==11) potOut = constrain(map(valore, 63, 960, minvalue[chan], maxvalue[chan]), 0, 127) ;  
      else if (modetable[chan  ] == 12) { potOut = constrain(map(valore, 63, 256, minvalue[chan], maxvalue[chan]), 0, 127) ;shifter.setAll(LOW); }
      else if (modetable[chan  ] == 13) { potOut = constrain(map(valore, 768, 960, minvalue[chan], maxvalue[chan]), 0, 127) ;shifter.setAll(LOW); }
    
     else if (modetable[chan] == 14){ 
       
     if (valore < 448) { potOut = constrain(map(valore, 63, 448, 0, 64), 0, 127) ; }  // hypercurve center
     else 
     if (valore > 576) { { potOut = constrain(map(valore, 576, 960, 64, 127), 0, 127) ; } }
     else potOut= 64;   }  
 
     else if (modetable[chan] == 15){ 
       
     if (valore < 340) { potOut = constrain(map(valore, 63, 448, 0, 64), 0, 127) ; }  // hypercurve center
     else 
     if (valore > 684) { { potOut = constrain(map(valore, 576, 960, 64, 127), 0, 127) ; } }
     else potOut= 64;    }
     
     
      switch ( (typetable[chan + (page)] - 144)  / 16)
      {
        case 0 :   if (chan < 8) noteOn(176, chan,  valore/8, 0) ; break;// note
        case 1 :   noteOn(typetable[chan + (page)], valuetable[chan + (page)],  potOut, 1) ; break; // poly AT
        case 2 :   noteOn(typetable[chan + (page)], valuetable[chan + (page)],  potOut, 1) ; break; // cc
        case 3 :   //noteOn(176, chan,  valore/8, 0) ; break; // pc
        case 4 :   noteOn(typetable[chan + (page)], potOut,  0, 1) ; break; // channel AT
        case 5 :  {
          int valore2 =constrain(map(valore,24,1000, 0,1024),0,1023);
         // valore = constrain(map(valore,24,1000, 0,1024),0,1023);
            noteOn(typetable[chan + (page)], (valore2 - ((valore2 / 8) * 8)) * 16,  valore2 / 8 , 1) ;
          }
          break; // PB
      }

      {

        cycletimer = 0;
        encled = abs( 15 - ((potOut) / 8)) * 16 ;
        led_enc_exe();

      }
   //   DmxSimple.write(dmxtable[chan], constrain( map(valore, 30, 960, 0, 255) , 0, 255));

   

      lastbutton[chan] = valore / 4 ;

    }/////////////////////////////////////////////////



  }
}
