/*
 * Code For Arduino
 * 
 * Servo Steering Platform Controller
 * Command format:
 *   {x:<value>,y:<value>}\n
 * Example:
 *   {x:120,y:70}\n
 *
 * Notice:
 *   Range of value: 0 - 180
 *   Out of range will not move
 *
 * 2016.11.2
 *
 * https://github.com/mo10/
 *
 *           0w0geng@gamil.com
 */
#include <Servo.h>

#define X_Pin 11 //Your X Servo Pin
#define Y_Pin 10 //Your Y Servo Pin

Servo servoX;
Servo servoY;
String inRaw="";
short inX=-1,inY=-1,inEnd=-1;
int x,y;
void setup() {
	servoX.attach(X_Pin);
	servoY.attach(Y_Pin);
	Serial.begin(115200);

	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	//Servo init
	servoX.write(90);
	delay(15);
	servoY.write(90);
	delay(15);
}

void loop() {
	while (Serial.available() > 0) {
		char inChar = Serial.read();
		if (inChar == '\n'){
			if ( (inRaw.indexOf("{x:"))!=-1 && (inEnd=inRaw.indexOf("}"))!=-1 && (inX=inRaw.indexOf("{x:"))!=-1 && (inY=inRaw.indexOf(",y:"))!=-1 ) {
				x=inRaw.substring(inX + 3, inY).toInt();
				y=inRaw.substring(inY + 3, inEnd).toInt();
				if(x <= 180 && x >= 0) {servoX.write(x); delay(15);}
				if(y <= 180 && y >= 0) {servoY.write(y); delay(15);}

				Serial.println(inRaw);
				Serial.println(x);
				Serial.println(y);
				inRaw="";
				return;
			}
		}
		inRaw += inChar;
	}
}
