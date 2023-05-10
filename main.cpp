// arduino camera code
// ggomez1@yc.edu
// https://www.arduino.cc/reference/en/
// https://docs.arduino.cc/built-in-examples/digital/Button
// board setup: stepper motor wired to pins 0,1,2,3
// servo wired to pins: 4
// s1 button wired to: 11
// 28BYJ-48 - 5V Stepper Motor https://components101.com/motors/28byj-48-stepper-motor


#include <Servo.h>
#include <Stepper.h>

// set ports
const int button = 7; //using S1 built in to board
const int shutter_motor = 4;

// setup stepper motor (how many steps is a revolution for your motor)
const int stepsPerRevolution = 64;

Servo shutterServo;
Stepper rollerStepper(stepsPerRevolution, 0,1,2,3);
//Stepper reverseStepper(stepsPerRevolution, 3, 2, 1, 0);

// set amount of time for exposure in seconds here:
const int shutter_time = 5;
const int open_shutter_angle = 0;
const int closed_shutter_angle = 90;

const int number_of_steps = 4000; // set number of steps needed to eject the photo here:

int buttonState = 0;  // variable for reading the pushbutton status

void setup()
{
    // initialize the button as input
    pinMode(button, INPUT_PULLUP);

    // initialize the shutter servo and attach to pin above
    shutterServo.attach(shutter_motor);

    // set speed of steppermotor to 300 RPMS
    rollerStepper.setSpeed(150);
    
    Serial.begin(9600); // output to console
    Serial.println(" setup complete");
}

void loop()
{
    buttonState = digitalRead(button);

    // check if the pushbutton is pressed
    if (buttonState == HIGH)
    { 
        shutterServo.write(open_shutter_angle); // open shutter
        Serial.println(" open shutter");
        delay(15); // wait 15ms for shutter
        delay(shutter_time * 1000); // wait for preset exposure time
        shutterServo.write(closed_shutter_angle); // close shutter
        Serial.println(" close shutter");
        delay(15); // wait 15ms for shutter
        delay(1000); // wait 1s for photo development 

        Serial.println("forward");
        rollerStepper.step(number_of_steps); //forward stepper
        delay(5000); // let the photo print
        delay(5000); // allow grabbing polaroid
        Serial.println("reverse");
        rollerStepper.step(-number_of_steps); // reverse the stepper
        delay(5000); // allow stepper to get in to position for new picture
        Serial.println("complete");
    }
    else
    {
        // do nothing 
    }
}
