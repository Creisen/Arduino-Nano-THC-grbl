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

*/	

	//O:
        int PauseProgram    = 11;
		int ArcEnable       = 12;
		int zDir            = 13;
		int zPuls           = A0;

		

	//_Var:

		int icountSteps = 0;
		int iStep = 0;
		int iVelo = 0;	//mm/min
		int iDistRelease = 0;	//mm Freifahren
        int iDistPlunge = 0;    //mm Einstechtiefe
		int StepsPermm = 40;	// Schrittweite
        int iReleaseCurrent = 0;
		boolean ReleaseReset;
		int iReleasePlunge = 0;
		boolean PlungeReset;
		




void setup(){

	  pinMode(3, INPUT);
	  digitalWrite(3, HIGH);	//activate pullup
	  pinMode(4, INPUT);
	  digitalWrite(4, HIGH);	//activate pullup
	  pinMode(5, INPUT);
	  digitalWrite(5, HIGH);	//activate pullup
	  pinMode(6, INPUT);
	  digitalWrite(6, HIGH);	//activate pullup
	  pinMode(7, INPUT);
	  digitalWrite(7, HIGH);	//activate pullup
	  pinMode(8, INPUT);
	  digitalWrite(8, HIGH);	//activate pullup
	  pinMode(9, INPUT);
	  digitalWrite(9, HIGH);	//activate pullup
	  pinMode(10, INPUT);
	  digitalWrite(10, HIGH);	//activate pullup
	
	
	  pinMode(PauseProgram, OUTPUT);
	  pinMode(ArcEnable, OUTPUT);
	  pinMode(zDir, OUTPUT);
	  pinMode(zPuls, OUTPUT);

	  iDistRelease = iDistRelease * StepsPermm;
	  iDistPlunge = iDistPlunge * StepsPermm;
	
	
}


//digitalRead


void   loop(){

  //int!!
  
boolean NH				 = ! digitalRead(3);
boolean LimitDown		 = ! digitalRead(4);
boolean zDir 			 = ! digitalRead(5);
boolean zPuls			 = ! digitalRead(6);
boolean THCUp			 = ! digitalRead(7);
boolean THCDown			 = ! digitalRead(8);
boolean THCArc			 = ! digitalRead(9);
boolean SpindleEnable	 = ! digitalRead(10);






//IF NH, THEN Ausgaenge aus, PauseProgramm (1s Impuls)



if (NH) {

	digitalWrite(PauseProgram, LOW);
	digitalWrite(ArcEnable, LOW);
	iStep = 0;
}



else   {

					

//Schrittkette THC

	

	if (SpindleEnable && iStep == 0 && ! NH) {

		iStep = 1; 		// initial, wenn schrittkette auf 0
		
	}
	
	else if (! SpindleEnable) {
  
		iStep = 0;
                digitalWrite(ArcEnable, LOW);

	}



switch(iStep){

//Startsignal dann Schrittkette start, sonst disable move, Plasma aus

case 0:		                                    //Alle ausgänge aus
                digitalWrite(PauseProgram, LOW);
	        digitalWrite(ArcEnable, LOW);       
                
                iStep = 1;

case 1:		                                    //Programm pause
        digitalWrite(PauseProgram, HIGH);   

		iStep = 2;



case 2:		                                    //Antasten    
                if(!LimitDown){      
	
		 		  moveDown(zDir,zPuls, true);
		
                  break;
                
                }


		else {
				  ReleaseReset = false;
                  iStep = 3;
              
                }
                
		
case 3:		                                    //Freifahren
     
		
		while(iDistRelease <= iReleaseCurrent)	{
		
			iReleaseCurrent = moveUp(zDir,zPuls,ReleaseReset);
			
			break;
		}

		ReleaseReset = true;
		iStep = 4;
		


case 4:		                                     //Start Lichtbogen
                digitalWrite(ArcEnable, HIGH);     
                
                if (THCArc){          //continue when Arc is on
		  iStep = 5;
		}

                break;

case 5:		                                    //Einstechen
		   while(! THCUp){
			
			 moveDown(zDir,zPuls, true);
			 break;
			   
		   }
		
			iStep = 6;
		


case 6:                                             //End Programm Pause
               digitalWrite(PauseProgram, LOW);    

               iStep = 7;



case 7:                                             //LOOP moveUp(),moveDown()
          
          
               if (THCUp){
                 
                moveUp(zDir,zPuls, true); 
                
                break;
                
               }
               
               else if (THCDown){
                 
                moveDown(zDir,zPuls, true);
               
                break;
                
               }


}

}

}



int moveDown(int PinDir, int PinStep, boolean Reset){			//Funktion Z-Achse senken
  digitalWrite(PinDir, LOW);
  
  boolean Step;
  
  delay(1);
	
  digitalWrite(PinStep, Step);
  
  Step =! Step;
  
  int iCount;
	iCount++;
	
  if (Reset){
    iCount = 0;
  }
  
  return iCount;
  
}

int moveUp(int PinDir, int PinStep, boolean Reset){				//Funktion Z-Achse anheben
  digitalWrite(PinDir, HIGH);
  
  boolean Step;
	
  delay(1);
  
  digitalWrite(PinStep, Step);
  
  Step =! Step;
  
  int iCount;
	iCount++;
  
  if (Reset){
    iCount = 0;
  }
  
  return iCount;
  
}



boolean TON(long TimeValueMS, boolean IN){						// Timer
  long oldTime;
  long newTime;
  boolean OUT;
  
if (IN){
  newTime = millis();
    
    if (newTime - oldTime >= TimeValueMS){
      
     return 1;
      
    }
          
}
 
else {
 
  oldTime = millis();
  newTime = millis();
  return 0;
} 
  
}

