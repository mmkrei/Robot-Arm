#include "MyServo.h"

// Class accessors

unsigned short MyServo::GetAngle() 		{ return _angle; }
unsigned short MyServo::GetLowLimit() 	{ return _lowLimit;  }
unsigned short MyServo::GetHighLimit()	{ return _highLimit; } 

// Class operators

Servo&	MyServo::operator++()
{
	if(_angle >= _highLimit) { return *this; }

	_angle++;
	write(_angle);
	return *this;
}
Servo 	MyServo::operator++(int)
{
	if(_angle >= _highLimit) { return *this; }

	Servo temp = *this;
	++*this;
	return temp;
}
Servo& 	MyServo::operator--()
{
	if(_angle <= _lowLimit) { return *this; }

	_angle--;
	write(_angle);
	return *this;
}
Servo 	MyServo::operator--(int)
{
	if(_angle <= _lowLimit) { return *this; }

	Servo temp = *this;
	--*this;
	return temp;
}
void 	MyServo::operator=(int Value)
{
	if(Value <= _lowLimit || Value >= _highLimit) { return; }

	_angle = Value;
	write(_angle);
}

// Class (de)constructors

MyServo::MyServo() { }
MyServo::MyServo(unsigned short OutputPin) :
	_outputPin(OutputPin)
{ 
	attach(_outputPin);
}
MyServo::~MyServo() { }

// Class methods

void MyServo::SetLimits(unsigned short Min, unsigned short Max)
{
	// Minimum
	if(Min >= 0 && Min <= 180 && Min <= Max)
	{ 
		_lowLimit = Min;

		if(_angle < _lowLimit) { *this = _lowLimit; }	// Adjust angle of rotation if current exceeds minimum
	}

	// Maximum
	if(Max >= 0 && Max <= 180 && Max >= Min)
	{
		_highLimit	= Max;

		if(_angle > _highLimit) { *this = _highLimit; }	// Adjust angle of rotation if current exceeds maximum
	}
}