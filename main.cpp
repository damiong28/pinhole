// arduino camera code
// ggomez1@yc.edu
// https://www.arduino.cc/reference/en/
// https://docs.arduino.cc/built-in-examples/digital/Button
// board setup: stepper motor wired to pins 8,9,10,11
// servo wired to pins: 2
// s1 button wired to: 1
// 28BYJ-48 - 5V Stepper Motor https://components101.com/motors/28byj-48-stepper-motor


#include Servo
#include Stepper

// set ports
const int button = 1; //using S1 built in to board
const int shutter_motor = 2;

// setup stepper motor (how many steps is a revolution for your motor)
const int stepsPerRevolution = 64;

Servo shutterServo;
Stepper rollerStepper(stepsPerRevolution, 8, 9, 10, 11);

// set amount of time for exposure in seconds here:
const int shutter_time = 5;
// set open angle of shutter servo here:
const int shutter_angle = 90;
// set number of steps needed to eject the photo here:
const int number_of_steps = 0;

int buttonState = 0;  // variable for reading the pushbutton status

void setup()
{
    // initialize the button as input
    pinMode(button, INPUT);

    // initialize the shutter servo and attach to pin above
    shutterServo.attach(shutter_motor);

    // set speed of steppermotor to 30 RPMS
    rollerStepper.setSpeed(30);

}

void loop()
{
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
        // opens shutter for hardcoded amount of time (servo)
        shutterServo.write(shutter_angle);
        delay(15); // wait 15ms for shutter to reach final position
        delay(shutter_time * 1000); // wait for preset exposure time
        shutterServo.write(0); // close shutter
        delay(15); // wait 15ms for shutter
        delay(1000); // wait 1s for photo development

        // print the photo (stepper motor)
        rollerStepper.step(number_of_steps);
    }
    else
    {
        // do nothing 
    }
}

