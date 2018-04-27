// THC Moritz Rehberg 26.04.2018






void Setup(){

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
        	int PauseProgramm   = 11;
		int ArcEnable       = 12;
		int zDir            = 13;
		int zPuls           = A0;

		

	//_Var:

		int countSteps = 0;
		int iStep = 0;
		int iVelo = 0;	//mm/min
		int iDistRelease = 0;	//mm

		
}


//digitalRead


void Loop{

NH			 = NOT digitalRead(3);
LimitDown		 = NOT digitalRead(4);
zDir 			 = NOT digitalRead(5);
zPuls			 = NOT digitalRead(6);
THCUp			 = NOT digitalRead(7);
THCDown			 = NOT digitalRead(8);
THCArc			 = NOT digitalRead(9);
SpindleEnable	         = NOT digitalRead(10);







//IF NH, THEN Ausgaenge aus, PauseProgramm (1s Impuls)



if (NH) {

	digitalWrite(PauseProgram, LOW);
	digitalWrite(ArcEnable, LOW);
}



else   {

					

//Schrittkette THC

	

	if (SpindleEnable && iStep == 0 && NOT NH) {

		iStep = 1; 		// initial, wenn schrittkette auf 0
		
	}
	
	else if NOT SpindleEnable {
  
		iStep = 0;
                digitalWrite(ArcEnable, LOW);

	}



switch(iStep){

//Startsignal dann Schrittkette start, sonst disable move, Plasma aus

case 0:		//Alle ausgänge aus



case 1:		                                    //Programm pause
                digitalWrite(PauseProgram, HIGH);   

		iStep = 2;



case 2:		                                    //Antasten    
                while(NOT LimitDown){      
	
		moveDown(iVelo);
		}	

		iStep = 3;
		

		
case 3:		                                    //Freifahren
                iDistRelease
		
		for(...)	{
		
			moveUp();
			
			iCountStepZ ++;
			
		}

		iStep = 4;
		


case 4:		                                     //Start Lichtbogen
                digitalWrite(ArcEnable, HIGH);     
                
                if (THCArc){          //continue when Arc is on
		  iStep = 5;
		}


case 5:		                                    //Einstechen



case 6:                                             //End Programm Pause
               digitalWrite(PauseProgram, LOW);    

               iStep = 7;



case 7:                                             //LOOP moveUp(),moveDown()
          
          
               if (THCUp){
                 
                moveUp(); 
                
               }
               
               else if (THCDown){
                 
                moveDown();
               
               }


}

}

}



int moveDown(int PinDir, int PinStep){
  boolean Dir = 0;
  boolean Step;
  
  Step =! Step;
  
  return Step;
  
}

int moveUp(int PinDir, int PinStep){
  boolean Dir = 1;
  boolean Step;
  
   Step =! Step;
  
  return Step;
  
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


