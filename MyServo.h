/* Controls a 180 degree servo and allows for limitations on angle of rotation at runtime. */

#ifndef MyServo_h
#define MyServo_h

#include <Servo.h>

class MyServo : Servo
{
private:
    unsigned short _angle;
    unsigned short _outputPin;
	unsigned short _lowLimit	= 0;
	unsigned short _highLimit	= 180;	

public:
	unsigned short GetAngle(void);
	unsigned short GetLowLimit();
	unsigned short GetHighLimit();

	// Increase angle
    Servo&	operator++();		// Prefix increment
    Servo 	operator++(int);	// Postfix increment

	// Decrease angle
	Servo& 	operator--();		// Prefix decrement
	Servo 	operator--(int);	// Postfix decrement

	// Set angle
	void 	operator=(int);

	MyServo();
    MyServo(unsigned short OutputPin);
	~MyServo();

	// Sets limits on the angle of rotation and adjusts current angle of rotation if necessary
	void SetLimits(unsigned short Min, unsigned short Max);
};

#endif