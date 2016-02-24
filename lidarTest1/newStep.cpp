#include "Arduino.h"
#include "newStep.h"
#include "scan.h"


stepMotor::stepMotor(){
    read_iteration = 0;
	direction = 0;
	int speed = 0;
	step_delay = 0;
	number_of_steps = 200;
	last_step_angle = 0;
	last_step_time = 0;
	step_number = 0;
	degree = 0;

	pinMode(output_pins[0], OUTPUT);
    pinMode(output_pins[1], OUTPUT);
    pinMode(output_pins[2], OUTPUT);
    pinMode(output_pins[3], OUTPUT);
}
void stepMotor::increaseStep(int currentStep){

	int angleCounter = 0;
	int degreeInc = 0;
    int output_pins[] = {8,9,10,11};
   

	// currently configured for pins 8,9,10,11
        // output_pins[0-3]// 


	switch(currentStep){
		case 0: // 1010
			digitalWrite(output_pins[0], 1);
			digitalWrite(output_pins[1], 0);
			digitalWrite(output_pins[2], 1);
			digitalWrite(output_pins[3], 0);
		break;
		case 1: // 0110
			digitalWrite(output_pins[0], 0);
			digitalWrite(output_pins[1], 1);
			digitalWrite(output_pins[2], 1);
			digitalWrite(output_pins[3], 0);
		break;
		case 2: // 0101
			digitalWrite(output_pins[0], 0);
			digitalWrite(output_pins[1], 1);
			digitalWrite(output_pins[2], 0);
			digitalWrite(output_pins[3], 1);
		break;
		case 3: // 1001
			digitalWrite(output_pins[0], 1);
			digitalWrite(output_pins[1], 0);
			digitalWrite(output_pins[2], 0);
			digitalWrite(output_pins[3], 1);
		break;
	}
        
        // reverse: decreases the angle
	if(direction == 0)
		degreeInc = -0.597;
	else if(direction == 1)
		degreeInc = 0.597;

	degree += degreeInc;

	scan scan1;
	int distance = scan1.getDistance();
	Serial.println("Here's the distance: ");
  	Serial.print(distance);
  	// Serial.println(degree + " =  degree");

}
void stepMotor::setSpeed(int desiredSpeed){
	step_delay = 60L * 1000L * 1000L / number_of_steps / desiredSpeed;
	// step_delay = 60 * 1000 * 1000;
	// debug(step_delay);
}
void stepMotor::step(int steps_to_move){

	// TODO: absolute value in arduino?
        // uncomment line below when solved
	int steps_left = abs(steps_to_move);
	// int steps_left = 0;

	if(steps_to_move > 0){
		direction = 1;
	}
	else{
		Serial.println("NEGATIVE");
		direction = 0;
	}
	while(steps_left > 0){
                
		unsigned long current_step_time = micros();
		if(current_step_time - last_step_time >= step_delay){
			last_step_time = current_step_time;
			if(direction == 1){
				step_number++;
				
				if(step_number == number_of_steps)
					step_number = 0;
			
			}
			else{
				if(step_number == 0)
					step_number = number_of_steps;
				step_number--;
			}
			steps_left--;
			increaseStep(step_number % 4);
		}

	}

}
void stepMotor::debug(int someValue){
	Serial.println(someValue);
}

