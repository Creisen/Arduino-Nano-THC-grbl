// THC Moritz Rehberg 26.04.2018



#include <AFMotor.h>

AF_Stepper motor(200, 1);

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
    int PauseProgram        = 11;
		int ArcEnable           = 12;
		int zDir                = 14;
		int ProgramResume       = 15;

		

	//_Var:

		int iStep = 0;
		int iVelo = 100;	//mm/min
		int iDistRelease = 20;	//mm Freifahren
    //int iDistPlunge = 10;    //mm Einstechtiefe
		int StepsPermm = 100;	// Schrittweite
    //int iReleaseCurrent = 0;
		int iReleasePlunge = 0;
    boolean ReleaseReset = 1;
		




void setup(){

    Serial.begin(9600);

    motor.setSpeed(iVelo); 

  
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
	  pinMode(ProgramResume, OUTPUT);

	  iDistRelease = iDistRelease * StepsPermm;
	 // iDistPlunge = iDistPlunge * StepsPermm;
	
	
}


//digitalRead


void   loop(){

  //int!!

  
boolean NH				 = !digitalRead(3);
boolean LimitDown		 = ! digitalRead(4); // Negation nach Test wieder einfuegen!!!
boolean IzDir 			 =  digitalRead(5);
boolean IzPuls			 =  digitalRead(6);
boolean THCUp			   = ! digitalRead(7);
boolean THCDown			 = ! digitalRead(8);
boolean THCArc			 = ! digitalRead(9);
boolean SpindleEnable	 =  digitalRead(10);





//IF NH, THEN Ausgaenge aus, PauseProgramm (1s Impuls)



if (NH) {
        
	digitalWrite(ArcEnable, LOW);
	Serial.println("Not-Halt");

	iStep = 0;
}



else   {

					

//Schrittkette THC

	

	if (SpindleEnable && (iStep == 0) && ! NH) {

		iStep = 1; 		// initial, wenn schrittkette auf 0
		
	}
	
	else if (! SpindleEnable) {

              digitalWrite(ArcEnable, LOW);


              if(ReleaseReset){

                Serial.println("Initiales Freifahren");   

                digitalWrite(PauseProgram, LOW);   //Pause  

                digitalWrite(zDir, LOW);
                motor.step(iDistRelease, FORWARD, SINGLE); 

                digitalWrite(ProgramResume, LOW); //Resume
                ReleaseReset = 0;
                
              }


         /*     Serial.println("Pin Durchschaltung");

    
              if(PIND & (1 << PD5)){      //Signale von grbl Durchschalten;

                 PORTC |= (1 << PC0);
              }
    
              else {
                 PORTC &= ~(1 << PC0);            
              }

              if(PIND & (1 << PD6)){      //Signale von grbl Durchschalten;

                 PORTB |= (1 << PB5);                 
              }
    
              else {
                 PORTB &= ~(1 << PB5);               
              }
         */
             
                
	          	iStep = 0;
	}



switch(iStep){

//Startsignal dann Schrittkette start, sonst disable move, Plasma aus

case 0:		                                    //Alle ausgänge aus
                digitalWrite(PauseProgram, HIGH);
                digitalWrite(ProgramResume, HIGH);
	              digitalWrite(ArcEnable, LOW);       
                Serial.println("Schritt 0");
                if (SpindleEnable){
                iStep = 1;
                }
                break;
            
case 1:		                                    //Programm pause

                Serial.println("Schritt 1");
                ReleaseReset = true;  
		            iStep = 2;



case 2:		                                    //Antasten    
                Serial.println("Schritt 2");

                digitalWrite(PauseProgram, LOW);   //Pause  

             


                if(LimitDown){      
	                                            //Spindel ab
                  digitalWrite(zDir, HIGH);
                  
                  motor.step(1, BACKWARD, SINGLE); 
		
                  break;
                
                }


		else {
                  iStep = 3;
              
                }
                
		
case 3:		                                    //Freifahren
     
                Serial.println("Schritt 3");		
                digitalWrite(PauseProgram, HIGH);   //Pause  
		//if (iDistRelease >= iReleaseCurrent)	{
		
                //Motor bewegen
                digitalWrite(zDir, LOW);
                motor.step(iDistRelease, FORWARD, SINGLE); 
			
   //                    iReleaseCurrent++;

          //      Serial.println(digitalRead(PinStep));	

    //                  if (ReleaseReset){
    //                  iReleaseCurrent = 0;
    //                  }


      //                  Serial.println(iReleaseCurrent);

		//	break;
		//}

	   //	ReleaseReset = true;
		            iStep = 4;
		


case 4:		                                     //Start Lichtbogen
                Serial.println("Schritt 4");

                digitalWrite(ArcEnable, HIGH);     
                
                if (THCArc){          //continue when Arc is on
		  iStep = 5;
		}

                break;

case 5:		                                    //Einstechen

                  Serial.println("Schritt 5");

		   if(! THCUp){
			                                                          
          digitalWrite(zDir, HIGH);
                  
          motor.step(100, BACKWARD, SINGLE); 

			 break;
			   
		   }
		
			iStep = 6;
		


case 6:                                             //End Programm Pause

               Serial.println("Schritt 6");

               digitalWrite(ProgramResume, LOW); //Resume
  
               iStep = 7;



case 7:                                             //LOOP moveUp(),moveDown()

//!!!!!Abfrage ArcOn else Pause, Schritt 0?

                  Serial.println("Schritt 7");

               digitalWrite(ProgramResume, HIGH); //Resume


               if (THCUp){
                 
                  digitalWrite(zDir, LOW);
                  
                  motor.step(1, BACKWARD, SINGLE); 
                
                  Serial.println("Up");                
                
                break;
                
               }
               
               else if (THCDown){
                 
                  digitalWrite(zDir, HIGH);
                  
                  motor.step(1, BACKWARD, SINGLE); 
               
                  Serial.println("Down");    
               
                break;
                
               }


}

}

}


/*


int moveDown(int PinDir, int PinStep){			//Funktion Z-Achse senken
  digitalWrite(PinDir, HIGH);
  
  
  delay(1);
	
  digitalWrite(PinStep, !digitalRead(PinStep));
 
  
}

int moveUp(int PinDir, int PinStep){				//Funktion Z-Achse anheben
  digitalWrite(PinDir, LOW);
  
	
  delay(1);
  
  digitalWrite(PinStep, !digitalRead(PinStep));
  

  
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
*/
