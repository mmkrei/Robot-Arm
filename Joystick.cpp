#include <math.h>
#include "Joystick.h"

/* Anonymous namespace declarations

Note:

An anonymous namespace allows distinct, instance-scoped variables and method declarations.

Statically-declared variables (outside of an anonymous namespace) are shared between ALL class instances.
*/
namespace
{
	int swTempInput;
	int xTempInput;
	int yTempInput;
};

// Class accessors

int Joystick::GetSWInput()	{ return _swInput; }
int Joystick::GetXInput()	{ return _xInput; }
int Joystick::GetYInput()	{ return _yInput; }

// Class constructors

Joystick::Joystick() { }
Joystick::Joystick(unsigned short SWInputPin, unsigned short XPInputPin, unsigned short YInputPin) :
	_swInputPin(SWInputPin),
	_xInputPin(XPInputPin),
	_yInputPin(YInputPin)
{
	pinMode(_swInputPin, INPUT_PULLUP); // 1 by default, 0 when pressed
	pinMode(_xInputPin,  INPUT);
	pinMode(_yInputPin,  INPUT);
}

// Class methods

void Joystick::ReadInput()
{
	swTempInput  = digitalRead(_swInputPin);
	xTempInput   = analogRead(_xInputPin);
	yTempInput   = analogRead(_yInputPin);

    if(_swInput != swTempInput)
	{
		_swInput = swTempInput;
	}
	if(abs(_xInput - xTempInput) > 25) // Brute-force noise filtration
	{
		_xInput = xTempInput;
	}
	if(abs(_yInput - yTempInput) > 25)
	{
		_yInput = yTempInput;
	}
}