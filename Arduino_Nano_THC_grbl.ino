// THC Moritz Rehberg 26.04.2018



/*
Variablen:

	I:	NH

		LimitDown

		zDir

		zPuls

		THCUp

		THCDown

		THCArc

		SpindleEnable

	

	O: 	int PauseProgramm	= #PINNUMMER
		int ArcEnable       = #PINNUMMER
		int zDir            = #PINNUMMER
		int zPuls           = #PINNUMMER

		

	_Var:

		int countSteps = 0;

		int iStep = 0;

		int iVelo = 0;	//mm/min
		
		int iDistRelease = 0;	//mm
		

		TIMER_PROGRAMMIEREN!!!

		
*/
		





/*
Funktionen:

				moveUp();	// per call 1 Step

				moveDown();

*/

//digitalRead



NH			 = NOT digitalRead(Pinx);

LimitDown		 = NOT digitalRead(Pinx);

zDir 			 = NOT digitalRead(Pinx);

zPuls			 = NOT digitalRead(Pinx);

THCUp			 = NOT digitalRead(Pinx);

THCDown			 = NOT digitalRead(Pinx);

THCArc			 = NOT digitalRead(Pinx);

SpindleEnable	         = NOT digitalRead(Pinx);







//IF NH, THEN Ausgaenge aus, PauseProgramm (1s Impuls)



IF NH {

	digitalWrite(...., LOW);

	

}



ELSE {

					

//Schrittkette THC

	

	IF	SpindleEnable && NOT iStep {

		iStep = 1; 		// initial, wenn schrittkette auf 0
		
	}
	
	Elsif NOT SpindleEnable {
		iStep = 0;
	}

switch(iStep){

//Startsignal dann Schrittkette start, sonst disable move, Plasma aus

case 0:		//Alle ausgänge aus

//Programm pause

case 1:		digitalWrite(PauseProgram, HIGH);

		iStep = 2;

//Antasten

case 2:		while(NOT LimitDown){
	
		moveDown(iVelo);
		}	

		iStep = 3;
		
//Freifahren
		
case 3:		iDistRelease
		
		for(...)	{
		
			moveUp();
			
			iCountStepZ ++;
			
		}

		iStep = 4;
		
//Start Lichtbogen

case 4:		digitalWrite(ArcEnable, HIGH);

		iStep = 5;
		
//Einstechen

case 5:		

//End Programm Pause

case 6:        digitalWrite(PauseProgram, LOW);

               iStep = 7;

//LOOP moveUp(),moveDown()

case 7:        if

}

}


//CounterStepMaster



int moveDown(int PinDir, int PinStep){
  boolean Dir = 0;
  boolean Step;
  
  
  
}




boolean TON(int TimeValueMS, boolean IN){
 
  boolean OUT;
  
if (IN){
  newTime = millis();
    
    if (newTime - oldTime >= TimeValueMS){
      
     return 1;
      
    }
          
}
 
else {
 
  int oldTime = millis();
  int newTime = millis();
  return 0;
} 
  
}


