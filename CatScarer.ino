#include <MicroView.h>			// include MicroView library
#include <Servo.h>

MicroViewWidget *widget;		// create widget pointer

// PIR sensor inputs
int sensorPin_Left = A1;    // select the input pin for the potentiometer
int sensorPin_Right = A0;    // select the input pin for the potentiometer

int sensorValue_Left = 0;  // variable to store the value coming from the sensor
int sensorValue_Right = 0;

int relayPin = 2;     // set relayPin as pin 2 of Arduino
int servoPin = 6;

Servo servo;

int count = 60;
#define SERVO_LEFT 60
#define SERVO_MID 90
#define SERVO_RIGHT 120
#define BLAST_LENGTH 100 // Number of loops to keep air on for

int blast_count = 0;

void setup()
{
        servo.attach(6);

  	digitalWrite(sensorPin_Left, HIGH);		// Internal Pull-up
    	digitalWrite(sensorPin_Right, HIGH);		// Internal Pull-up
	pinMode(sensorPin_Left, INPUT);			// make pin as INPUT
        pinMode(sensorPin_Right, INPUT);			// make pin as INPUT
	pinMode(relayPin, OUTPUT);	// initialize the digital pin as an output.
	uView.begin();						// start MicroView
	uView.clear(PAGE);					// clear page

        // Let PIR sensors warm up for a minute
        while (count > 0) {
            uView.clear(PAGE);
            uView.setCursor(0,0);
            uView.print(count);
            uView.display();
            delay(1000);
            count--;
        }
        
//        widget = new MicroViewGauge(32, 24, 0, BLAST_LENGTH, WIDGETSTYLE1);
//	uView.display();					// display the content in the screen buffer
}

// Turn air on and start the counter ticking
// If air is already on, do nothing.
void turn_air_on()
{
  if (blast_count > 0) return;

  digitalWrite(relayPin, HIGH);
  blast_count = BLAST_LENGTH;
  count++;
}

void turn_air_off()
{
  digitalWrite(relayPin, LOW);
}
    
void loop()
{
        // Try to determine where the cat is      
	sensorValue_Left = analogRead(sensorPin_Left);	// read sensorPin
	sensorValue_Right = analogRead(sensorPin_Right);	// read sensorPin


        // Track cat using servo
        // Turn air on, if it's not already on
        // Check how long air has been on. If it's been long enough, turn off and sleep
        if (sensorValue_Left > 500) {
          if (sensorValue_Right > 500) {
            // Centre
            turn_air_on();
            servo.write(SERVO_MID);
//            uView.setCursor(0,0);
//            uView.print("MID  ");
           } else {
            // Left
            turn_air_on();
            servo.write(SERVO_LEFT);
//            uView.setCursor(0,0);
//            uView.print("LEFT ");
          }
        } else if (sensorValue_Right > 500) {
            // Right
            turn_air_on();
            servo.write(SERVO_RIGHT);
//            uView.setCursor(0,0);
//            uView.print("RIGHT");
        }
        
        if (blast_count > 0) {
          blast_count--;
          uView.clear(PAGE);
          uView.setCursor(0,0);
          uView.print("CATS BLASTED:");          
          uView.setCursor(0,40);
          uView.print(count);

          uView.display();	
       	  
          if (blast_count == 0) {
             // Pause between reloads.
             turn_air_off();
//             uView.setCursor(0,0);
//             uView.print("     ");
//             uView.display();	
             delay(5000);
 
          }
        } 
        
}



