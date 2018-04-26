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

	

	O:	PauseProgramm

		ArcEnable

		zDir

		zPuls

		

	_Var:

		countSteps

		iStep

		

		TIMER_PROGRAMMIEREN!!!

		
*/
		





/*
Funktionen:

				moveUp();

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

SpindleEnable	 = NOT digitalRead(Pinx);







//IF NH, THEN Ausgaenge aus, PauseProgramm (1s Impuls)



IF NH {

	digitalWrite(...., LOW);

	

}



ELSE {

					

//Schrittkette THC

	

	IF 



//Startsignal dann Schrittkette start, sonst disable move, Plasma aus



//Programm pause



//Antasten



//Freifahren



//Start Lichtbogen



//Einstechen



//End Programm Pause



//LOOP moveUp(),moveDown()










