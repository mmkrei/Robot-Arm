 /* 
Controls inventor.io "Robotic Arm Kit" using 2 joysticks:

    • left  joystick / left/right  => base
    • left  joystick / up/down     => up/down (left servo)
    • right joystick / left/right  => claw
    • right joystick / up/down     => in/out (right servo)
*/

#include <Arduino.h>
#include "MyServo.h"
#include "Joystick.h"

// Servo

const int baseOutputPin     = 3;
const int clawOutputPin     = 11;
const int leftOutputPin     = 9;
const int rightOutputPin    = 10;

MyServo base;
MyServo claw;
MyServo left;
MyServo right;

// Joysticks

const int LeftSWInputPin    = 12;
const int LeftXInputPin     = A2;
const int LeftYInputPin     = A3;
const int RightSWInputPin   = 13;
const int RightXInputPin    = A0;
const int RightYInputPin    = A1;

Joystick Left;
Joystick Right;

void setup () 
{
    // Servo

    base    = MyServo(baseOutputPin);
    claw    = MyServo(clawOutputPin);
    left    = MyServo(leftOutputPin);
    right   = MyServo(rightOutputPin);
    
    claw.SetLimits(0, 20);
    left.SetLimits(90, 180);

    ResetServos();

    // Joysticks
    
    Left    = Joystick(LeftSWInputPin,  LeftXInputPin,  LeftYInputPin);
    Right   = Joystick(RightSWInputPin, RightXInputPin, RightYInputPin);

    // Serial

    Serial.begin(115200);
}

int lastLeftSWState     = 1; // Initial state of SW press is high/input pull-up
int lastRightSWState    = 1;

void loop() 
{
    // Read joystick inputs

    Left.ReadInput();

    Serial.print(">Left SW: ");
    Serial.println(Left.GetSWInput());
    Serial.print(">Left X: ");
    Serial.println(Left.GetXInput());
    Serial.print(">Left Y: ");
    Serial.println(Left.GetYInput());

    Right.ReadInput();

    Serial.print(">Right SW: ");
    Serial.println(Right.GetSWInput());
    Serial.print(">Right X: ");
    Serial.println(Right.GetXInput());
    Serial.print(">Right Y: ");
    Serial.println(Right.GetYInput());

    // Adjust servo output

    if(Left.GetYInput() < 200) {    --base; }
    if(Left.GetYInput() > 1000) {   ++base; }

    Serial.print(">base: ");
    Serial.println(base.GetAngle());

    if(Left.GetXInput() < 200) {    ++left; }
    if(Left.GetXInput() > 1000) {   --left; }

    Serial.print(">left: ");
    Serial.println(left.GetAngle());

    if(Right.GetYInput() < 200) {   ++claw; }
    if(Right.GetYInput() > 1000) {  --claw; }

    Serial.print(">claw: ");
    Serial.println(claw.GetAngle());

    if(Right.GetXInput() < 200) {   ++right; }
    if(Right.GetXInput() > 1000) {  --right; }

    Serial.print(">right: ");
    Serial.println(right.GetAngle());

    // Re-center base servo on left joystick press
    if(Left.GetSWInput() != lastLeftSWState)
    {
        if(Left.GetSWInput() == 0) { base = 90; }       // High-to-low/negative edge transition
        lastLeftSWState = Left.GetSWInput();
    }   
    // Reset servos on right joystick press
    if(Right.GetSWInput() != lastRightSWState)
    {
        if(Right.GetSWInput() == 0) { ResetServos(); }  // High-to-low/negative edge transition
        lastRightSWState = Right.GetSWInput();
    }

    delay(10);
}

inline void ResetServos()
{
    base    = 90;
    claw    = 15;
    left    = 160;
    right   = 70;
}