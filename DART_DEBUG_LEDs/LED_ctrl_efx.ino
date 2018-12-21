void ledControl (byte stat)   // stat significa status 1 = acceso 0 = spento
{
 // if( chan < max_leds)
  {  if (stat >0 ) 
   buttonefx = 5; // ampiezza dell'effetto
   buttonefxd = lightable[chan]; // centro dell'effetto 
    shifter.setPin(lightable[chan], stat); 


 bit_write(1,lightable[chan]+page,stat);

 }
}

void led_enc_exe ()
{

   if (encled <0) { encled = 255 ; 
  shifter.setPin(encledtable[0], 0);
  shifter.setPin(encledtable[1], 0);
 } 


if (encled >255) { encled = 0; 
 shifter.setPin(encledtable[15], 0); 
  shifter.setPin(encledtable[14], 0); 
 } 
 //shifter.setAll(LOW);
 // if (previousMillis3 > currentMillis) {shifter.setPin(encledtable[constrain(encled/16,0,15)] , HIGH);  }
 if (cycletimer <  10) {shifter.setPin(encledtable[constrain(encled/16,0,15)] , 1);  }
 
 //if (encled > 64 ) 
 shifter.setPin((encledtable[(encled/16) -2] ), 0); 
if (encled < 240 ) shifter.setPin((encledtable[(encled/16) +2] ), 0);

// if ( lastsensor[numero]==0 ) shifterwrite=HIGH;
  shifterwrite=1; // on viene ripetuto ad ogni ciclo, ma solo quando vene mosso l'encoder
  
  }

  
 void buttonledefx()
 
 {
 //  buttonefx = 5; // ampiezza dell'effetto
 //  buttonefxd = lightable[chan]; // centro dell'effetto 
 
  if (buttonefx > 1) 

  if (cycletimer == 2) 
  {
    
    if (buttonefxd > 11 && buttonefxd < 16)
    {
    {

      shifter.setPin(encledtable3[(buttonefx + buttonefxd - 5 )-4], HIGH) ; 
      shifter.setPin(encledtable3[abs(5 - buttonefx + buttonefxd)-4 ], HIGH) ;}
}
      else 
      
   if (buttonefxd > 3 && buttonefxd < 8 // || buttonefxd > 11 && buttonefxd < 16  
   )
    { 
      
    {
      shifter.setPin(encledtable3[constrain(buttonefx + buttonefxd - 5,-1,16)], HIGH) ; 
    shifter.setPin(encledtable3[constrain(5 - buttonefx + buttonefxd,0,16)], HIGH) ; }
}
      else 
    
    
    if (buttonefxd > 7 && buttonefxd < 12 ) {   
      shifter.setPin(encledtable2[buttonefx + buttonefxd - 5], HIGH) ; 
      shifter.setPin(encledtable2[abs(5 - buttonefx + buttonefxd)], HIGH) ; 
    }
      
    else 
    if (buttonefxd < 4 ) 
    {  
      shifter.setPin(encledtable2[buttonefx + buttonefxd - 5 +12], HIGH) ; 
      shifter.setPin(encledtable2[abs(5 - buttonefx + buttonefxd +12)], HIGH) ; 
  }
    
 shifterwrite=1;
     //  previousMillis=(currentMillis + 30 ) ; //  fra 30 mmillisecondi previusmillis sarà nuovamente < currentmilllis ma ccon ampiezza diminuita.
      cycletimer = 0; 
      buttonefx = (buttonefx -1);
    if (buttonefx==2) buttonefxu = 5; // a un certo punto si da il via alla fase di spegnimento - buttonefxu è come buttonfx, scala da 5 a zero ogni 30 millisecondi
}
    
     if (buttonefxu > 1 )
  //   if(previousMillis2<currentMillis) 
  if (cycletimer == 3)
     {
 
      
        byte calcoloLED =  buttonefxu + buttonefxd - 6 ;
       byte calcoloLED2 =  6- buttonefxu + buttonefxd ; 
 
  if (buttonefxd > 11 && buttonefxd < 16) // basso sinistra
       {      // ok 
         shifter.setPin(encledtable3[ calcoloLED-4], LOW) ; 
         shifter.setPin(encledtable3[calcoloLED2-4 ], LOW) ;    }
   
    
    else 
    
if (buttonefxd > 3 && buttonefxd < 8 )  // basso destra
       {           shifter.setPin(encledtable3[ calcoloLED], LOW) ; 
         shifter.setPin(encledtable3[calcoloLED2 ], LOW) ;      }
    
   else 
    
    if (buttonefxd > 7 && buttonefxd < 12 ) // alto sinistra
    {    shifter.setPin(encledtable2[calcoloLED], LOW) ;    
      shifter.setPin(encledtable2[calcoloLED2], LOW) ;             }
     
   else                    
     if (buttonefxd < 4)  
    {  
      shifter.setPin(encledtable2[buttonefxu + buttonefxd +6], LOW) ; // verso sinistra  
      shifter.setPin(encledtable2[calcoloLED2+12], LOW) ; // ok verso destra
    } 
    
    shifterwrite=1; 
       //  previousMillis2=(currentMillis+30); 
         cycletimer = 0 ;
         buttonefxu = (buttonefxu -1) ; 
   

    
   if (buttonefxu==1) { shifter.setAll(LOW); //shifter.write(); 
 ledrestore(page); shifterwrite=1; }
 

 
   }
   
   }


    void beamefx()
 {
  shifter.setAll(LOW);
   byte beamValueLED = map(constrain(lightable[distance_mempos]  / 15, 0, 8),1,8,8,1) ;
   shifter.setPin(encledtable3[(beamValueLED)+3 ], HIGH);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ledrestore (boolean numero) { // riscrive sullo shifter la pagina 1 con luci accese o spente

  for(int led = 0; led < max_modifiers; led++) 
{ // feedop = led/8;
// shifter.setPin(led, ledstatus[led]);
// shifter.setPin(led, bitRead(bit_status[numero][feedop], led-(feedop*8)) );
shifter.setPin(led, bit_read(1,led+(numero*max_modifiers)) );
} 
  }
