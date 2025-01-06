// migliorato dettaglio pitch bend anche via encoders

// sto migliorando il trattamento del pitch bend
// lightable touch > 1 = no touch - niente.

// aggiustato movimento mouse tramite joystick. adesso è abbastanza veloce

// il beam in modalità scale dava problemi ai led e al feedback led. ora risolto

//possibilità di scegliere quanti plexer

//adesso il learn scale funziona correttamente - ancor col beam

// cerco di usare la procedura scale anche per il beam
// associo il valore beam a variabile AT
// scala[numero] avrà numero dell'encoder nel caso degli spinner e numero fisso nel caso del beam

// ho inserito una riga in void setup_mempos che rporta la modetable a blind input, nei pin 45 e 47 se il secondo encoder è attivato.

// sostituisco tutti i "+1" con ++ 

// elimino buttonstate - sostituito con lastbutton[page_mampos]
// gli array BIT_status sono stati ridotti a 4


// ritestato il virtual touch - adesso sembra ok

// vorrei condensare ancora encoder - soprattutto relativamente all'invert - ma non ci sto riuscendo minimamente

// elimino byte scala_counter_speed; sostituita con la mouse_wheel_speed_counter

// ho condensato update_encoder 1 e 2 in una unica void

//testare virtualtouch - 
//reazionalizzare encoder endless mode - ci sono molte ripetizioni

// ho razionalizzato virtualtouch - uso incomingbyte (normalmet usata nel midiIN - come varibile per contenere boolean(page) 
// testare che non ci siano conflitti


// il mouse e le freccette funzionano - da ottimizzare

// inserire una qualche forma di azione che porta la modetable a BLIND 19 se joyx e joyy devono funzionare come freccette - fatto
// perchè si crea un conflitto tra funzionamento analogico e digitale

// ripristinare mouse (eliminate mousex e mousey che erano float) e virtualtouch

//eliminare getvalue -fatto

//semplifico ledcontrol riga 8
//semplifico load preset - riduco i cicli for

// sto razionalizzanto tutta la gestione per BIT in multiarray chiamato bit_status

// bit_ledstatus diventa bit_status - lo faccio diventare un multi-array che ospiterà : ledstatus1 ledstatus2. toggle1 toggle2, feedback1 feedback2;

// cerco di comprimere ledrestore in una unica procedura void - creo quindi un array di array

// ho abbassato l'array dedicato allo scale learn a 6 slot, risparmiando questo poco di memoria le cose vanno un pò meglio

// dopo mille prove ho scoperto che con l'uso della memoria al 90% memoria dinamica- ci sono difficoltà di caricamento del preset all'avvio.

// corretto piccolo errore in pageswitch - la media del touch veniva caricata in modo errato - e il touch non funzionava sulla page2 - ora corretto

//rivedere void beamefx - ho tolto switchvalue[distance ... i sarà qualhe bordellino
// ristabilisco encodervaluepot (byte) al posto di switchstate

// ho notato che la memoria utilizzata da serial1 - per ricevere messaggi via DIN è di circa il 5% - TANTISSIMO

// provo a eliminare switchstate faccio tutto con lastbutton

// sto cercando di far funzionare insieme USB e DIN midi 
// pare che i problemi coincino a comparire uando la memoria dinamica utilizzata supera il 90%
// si potrebbe provare a ridimensionare l'array switchstate o anche eliminarlo
// si potrebbe ridurre modetable a 64 slot - da un breve sguardo pare fattbile


// ved x snellire bit processing con funzioni
// learn scale


// migliorato alcuni elementi del touch sensor... adesso ancora più stabile nella lettura. non ci sono ritorni a zero nella somma, nella media, e nella lettura 


// risolto problem escursione encled, quando si muoveva un pot o uno spinner...
// risolti i problemi con la gestione bit_ di toggle , feedback, e ledstatus

// problema : pagina 1 , b9 in modalità toggle , se b9 è acceso, molto altri pulsanti non accendono
// evidentemente anche con bit_toggle c'è qualche problema

// ho notato che cycletimer torna indietro periodicamente. quando raggionge 255 riparte da 0

// il virtualtouch continua a creare problemi - se da editor tengo premuto un modificatore per testare il feedback, dopo qualche secondo, oltre al led giusto...
// si accende un led sbagliato alrove

// CONTROLLARE OFFGROUP - HO CAMBIATO IL FOR - partiva da 1 e non da 0

// max_feedback adesso si può aumentare fino a 60 64// 
// il feedback led non funziona sul pulsante b10 - ok il problema era che molti FOR in MIDI_IN partivano da 1 e non da 0 - RISOLTO

// c'è qualche problema con il virtualtouch... il pulsante b10 (position 6 - che diventa 0) manda un segnale ripetuto a scatti... 
// ripetuto col timing del cycletimer
// er il virtualtouch2 che stava attivato e non essendo definito nell'editor... faceva riferimento alla posizione 0 - quindi il primo pulsante

// imposto l'attivazione del virtual touch per essere controllata per ogni spinner dal valore di lightable

// nella void offgroup il for arriva a 49 massimo - ricontrollare

// sto sostituendo toggletable2 e toggletable2a con _bit_toggle e bit_toggle2 - 
//sostituisco toggletable[distance_mempos] con lightable[distance_mempos]  nelle funzioni beam.

// riga 307 e simili - forse c'è un errore nella formuletta per il bit_feedback - controllare

// possibile usare tabella LEDS per selezionare il numero di multiplexers usati- 
// oppure si sposta l'attivazione del virtual touch dalla tabela value_general alla tabella led_touch

// in ain nucleo sezione pot - ripristino ma possibilità di avere un'uscita midi raw, se non c'è nulla nella EEPROM - ma solo sul primo multiplexer.

// ho limitato il remapping degli input (sezione midi IN - comunicazione ccon eeditor) a 55
// quindi da 0 a 55 gli input vengono rimappati... poi vengono assegnati normalmente - per esempio 56 = 56 , 59 = 59.

// problema . spuntano dei dati indesiderati insieme a quelli dovuti - cambiando la pagina... non dipende dal touchsensor
// il problema viene dal touch_real...

// ho messo un limitatore a ledcontrol. in modo che oltre il range di max_leds non succede nulla

// aumentando lastbutton da 60 a 64 la cosa si è risolta... non ho capito perche

// problema: i tasti posteriori arcade, collegari agli ultimi posti 53 54 55 56, sulla pagina 1 mandano in tilt il controller provocando un flusso continuo di dati in uscita
// questo flusso ha come riferimento il pot 16 (ccc 40) e il pulsante b10 (nota 69) 
// ho escluso il beam, il virtualtouch, il secondo encoder, i pads, il touch


// ho corretto il range di messaggi che possono entrare in midi in, c'erano difficoltaà con certi valori di LED

// virtualtouch si attiva con valutable[general_mempos] > 0 - altrimenti rimane disattivato.
// ho razionalizzato jogtouch (touch real) con una void unica
// ved se possibile razionalizzare touch_real - creando una void unica per i due touchsensors

// minvalue[general_mempos] > 0 attiva il plexer extra.
// dmxvalue[general_mempos] >0 attiva l'encoder secondario. - bisogna fare attenzione a mettere i relativi input 44 e 46 in MODE.BLIND_INPUT
// maxvalue[general_mempos] > 0 attiva la funzione PADS; 
// funziona come la vecchia speedA5 - 0 significa pads attivati, 1 significa pads disattivati e plexer normale
// 

// dichiaro "channel" che è la variabile utilizzata dal FOR della procedura AIN, - adesso è una variabile generale
// sto separando il secondo encoder dai pads... in procedure void separate.
// 26a - cerco di razionalizzare AIN 

// ho modificato jog_touch - semplificata e razionalizzata . la media average trale varie letture adesso è più precisa
// ho inserito una prima calibrazione delle lower_values dei youch sensors all'avvio - ogni volta che si cambia pagina, le lower values vengono ricalibrate



// nella modalità 63-65 non è implementata la velocità ma solo il numero 63 o 65

// ho relativizzato la lettura della PAGE all'accensione

//sostituzioni variabili per rsparmio memoria:
// byte encoderValue[2] ;  //sostituisco ccon lastbutton[encoder_mempos[numero]]
// int encodervaluepot[2] ; sostituita con switchstate[encoder_mempos[numero]]
// boolean beamstate2; // sostituisco con lastbutton[distance_mempos]


// gli array utilizzati per pot e pulsanti devono essere tanti quanti gli input utilizzati dal dart (56) 
// gli array utilizzati anche per funzioni speciali (virtual touch usa switchstate e lastbutton) devono essere tanti quanti sono i modificatori massimi accessibili da editor e memorizzabili su eeprom - cioè 64
// ma dato che anche min max qwerty e altro, vengono usete per funzioni speciali... tutto va portato a 64... o comunque oltre il 56, per dare spazio a funzioni speciali 
// se non si utilizzano ledstatus e feedbacktable per funzioni specciali... possono  restare limitate a 56
// lastbutton e switchstate vanno portate a 64


// ho messo touch_mempos e encoder_mempos in forma di array in modo che si possano selezionare tramite "numero"
// tutta la sezione virtual touch va relativizzata // provo a usare switchstate

// ho sostituito lastsensor 1 e 2 con - lastbutton[touch1_mempos] 1 e 2



//perchè ledstatus arriva solo 51 ??
// perchè feedbacktable arriva a 96? risale ai 48 elementi del dart one?

// tutti gli array sono 0 indexed - tutto va riscritto meglio per  non sprecare bytes iniziali - sia nel midi in - sia nella lettura da memoria di ain nucleo

// ved se possibile unire ledrestore 1 e 2
// aumentare capienza delle variabili array - a livello korova - 
// capire una volta per tutte gli spazi vuoti sugli array - se si scrive a partire da 0 o da 1

// ho rimappato la memorizzazione dei preset- adesso si usa la numerazione semplificata

// non c'è attività midi quando non c'è preset
// c'è un grosso problema nella memorizzazione dei preset- relativamente ai led! - risolto --  la seconda pagine caricata da editor andava a scrivere oltre il 2014


// assicurarsi che se touch e encoders non vengono specificati nell'editor, non succeddano casini... tutti i loro settaggi vanno a finire su posizione memory 0 - 
// inizializzo le variabili tutte su 64 ...
////                 se il dart non ha touch sensors - in teoria le procedure void non vengono triggerate - quindi no problem
////                  se il dart non ha encoders , in teoria le vvoi dell'encoder non vengono triggerate - 

// aggiunte modalità centercurve 
// relativizzato page e beam

// relativizzato encoders 12 e touch 12
// add ctrl alt shift - modalità modifiers

// cambio beam section - adesso si sceglie tramite qwertyvalue e non tramite modetable - se deve funzionare come pot o pulsante - quindi libero modetable, per migliorare coerenza editor
// in beam() riga 9 naturalmente lasci chan - come riferimanto - così si possono usare molti distance sensors.

// è possibile disattivare scegliere se il sesto multiplexer (analog in A5) deve essere dedicato a funzioni speciali (pads - encoder) oppure a normali input


// aggiunta riga 61 nell'efditor per accettare anche aftertouch, utile nel caso vengano ricavuti messaggi LED fuori range, per avere effetto ZERO
// aggiungo codica in load preset e MIDIIN per memorizzare mappatura LED output. 
// migiorato il dettaglio pot in ain nucleo - la soglia ddi differenza con lastbutton è 10 adesso... pare stabile.


// ved qwerty send
// ved dettaglio pot
// lo spazio di memoria del mouse nel korova era 58 - nel one e speciale porting va definito! scelgo il 47
// aggiungo riga per mandare mousewheel in void encoder 
// ho notato che all'avvio qualcosa non va... bisogna smuovere la levetta page... ok c'era un page=64... doveva esssere page=48

// encoderpads aveva un errore- c'èera il "+page" anche in min e maxvalue... sballava la seconda pagina


//porting: metto void midiout direttamente importata da korova.
// in void loop - inserisco le condizioni midi in del korova
// dichiaro variabile MIDIEvent eventomidiUSB;
// dichiaro volatile byte qwertyvalue[65]; ma la limito a 49
// dichiaro qwertymod - copiata da korova - contiene la tabella dei caratteri ulteriori
// in void load preset - inserisco righe per loading qweertyvalue
// inserisco voi modifiers - copiata da korova
// creo voi outnucleo sotto cartella midiout - per facilitare il senout dei modificatori... ved ain nucleo per utilizzo

// tolgo il baudrate midi - solo usb - metto la possibiltà di scegliere all'avvio con B12 - come nel korova
// !!!!! ho avuto molte difficoltà quando quertyvalue[49] veniva caricata fino a 64 valori... faceva sballare i pulsanti!! - fatto
// inserisco possibilità scelta baudrate all'avvio - riga per spegnimeto di tutti i ledstatus, dopo loadpreset , come nel korova
//----------------------

// virtual touch end - void - dmx arrima al massimo a 65 - eliminato "+page"
// la memorizzazione del valore dmx su eeprom partiva da 186, con conseguente accavallamento di valori, possibile... adesso parte normalmente da 192

// corretto bug pages su encoders

// in modalita pot-hypercurve i led si spengono ad ogni ciclo
// migliorato alcune inesattezze e ridondanze buttonledefx
// eliminato le vaiabili long per conteggio millis effetti led... adesso si usa il tempo di esecuzione ciclo per i led

// aggiunta funzione hypercurve - utile per scratching--- imposstando toggletale su 11 in poi si attiva, l'escursione da min a max si riduce, facilitando molte operazioni live 
// se impostato su 12 la curva è ridotta e invertita (nella parte supariore del fader)

// spannato meglio il segnale dei pot da 0 a 127
// corretto tochreset - encodervalueppot *8 !! ricordare he adesso è adesso è 0-1024
// toggletable dei touchsensor == 0 niente, == 1 touchreset normale, == 2 touchreset virtual - a value del touchreset è dmxtable dei touch

// vitual touch viene sparato ffuori insieme al touch normale ha lo stesso setup ma su un canale aumentato di 1
// adesso la velocità  deglli encoder può essere aggiustata al ribasso - va settata diversamente per encoder ottico ed encoder meccanico
// toggletable degli encoder decide se viene sparato ffuori segnale <63 >65 oppure 0-127
// risolto picccolo bug in encoderpads - i pulsanti extra erano impostati ancora con page*48
// encodervaluepot adesso è int

// modificato beamefx - ora più semplice
// possibile mandare dmx da encoder - solo in pot mode

// separato ain nucleo
// aggiunto effetti led pot
// possibilità invertire encoders (maxvalue 43 44 < 127)
// moltiplicatore velocità minvalue 43 44
// aggiunto virtual touch su 45 e 46 - diverso per i due encoders
// page adesso cambia da 0 a 48 - non più 0 e 1 - più facile programmare

// 19 5 2017 - fixed toggle mode number == 2 - groups >3 
// openeditor messagge == 241 system undefined

// Each modifier can now send Note, poly AT, Control Change, Program Change, Channel AT and PitchBend messages
// Touch-reset function for jogwheels j1 and j2 : if set to PithBend, the touch sensors will reset the PitchBending to it's mid position.
// The two pages/presets are now completely indipendent (different type, channel, min/max values, DMX essage, mode, can be set for each modifier for each page)
// Toggle-group mode available.
// A song position message (242,x,x) message is used to open/close the editor-upload procedure.
// Improved midifeedback processing - no feedback loops - it works for both the pages - attenzione: il midifeedback funziona con 0=spento !0=acceso- non tiene conto dei valori mix e max
