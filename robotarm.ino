#include <Servo.h>

Servo base;
Servo left;
Servo right;
Servo claw;

void setup () {
    base.attach(3);
    left.attach(9);
    right.attach(10);
    claw.attach(11);
}

void loop() {
    base.write(90);
    left.write(170);
    right.write(90);
    claw.write(30);

    int i = 0;

    // Move from right-to-left (base servo), in-to-out (right servo)
    for (; i < 180; ++i)
    {
        base.write(i);
        right.write(i);

        // Move arm up-to-down (left servo) starting at 120 degrees on the right servo to prevent binding
        if(i > 120)
        {
            left.write(i);
        }

        claw.write(i%30); // Claw closes-and-opens between 0 and 30 degrees

        delay(50);
    }

    // Move from left-to-right (base servo), out-to-in (right servo)
    for(i = 180; i > 0; --i)
    {
        base.write(i);
        right.write(i);

        // Move arm down-to-up (left servo) until 120 degrees on the right servo to prevent binding
        if(i > 120)
        {
            left.write(i);
        }

        claw.write(i%30);  // Claw closes-and-opens between 0 and 30 degrees

        delay(50);
    }
}