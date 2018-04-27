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

		countSteps

		iStep

		iVelo //mm/min
		

		TIMER_PROGRAMMIEREN!!!

		
*/
		





/*
Funktionen:

				moveUp();

				moveDown();

*/

//digitalRead



NH				 = NOT digitalRead(Pinx);

LimitDown		 = NOT digitalRead(Pinx);

zDir 			 = NOT digitalRead(Pinx);

zPuls			 = NOT digitalRead(Pinx);

THCUp			 = NOT digitalRead(Pinx);

THCDown			 = NOT digitalRead(Pinx);

THCArc			 = NOT digitalRead(Pinx);

SpindleEnable	 = NOT digitalRead(Pinx);







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

Case [iStep]

//Startsignal dann Schrittkette start, sonst disable move, Plasma aus

0:		//Alle ausgänge aus

//Programm pause

1:		digitalWrite(PauseProgramm, HIGH);


//Antasten

2:		while(NOT LimitDown){
	
		moveDown(iVelo);
		}	

//Freifahren
		
		


//Start Lichtbogen



//Einstechen



//End Programm Pause



//LOOP moveUp(),moveDown()



}


//CounterStepMaster






