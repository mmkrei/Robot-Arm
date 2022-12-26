/* Wrapper class for reading joystick input. */

#ifndef Joystick_h
#define Joystick_h

class Joystick
{
private:
    unsigned short 	_swInputPin;
    unsigned short 	_xInputPin;
    unsigned short 	_yInputPin;

    int 			_swInput;
    int 			_xInput;
    int 			_yInput;

public :
    // Note: call the "ReadInput" method before using the following "Get..." accessors
    int GetSWInput();
    int GetXInput();
    int GetYInput();

    // Constructors

	Joystick();
    Joystick(unsigned short SWInputPin, unsigned short XPInputPin, unsigned short YInputPin);

    // Methods
    
    void ReadInput(); // Read and store the current input
};

#endif