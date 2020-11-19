#ifndef _MOTOR_H
#define _MOTOR_H


#include "constants.h"

// A class to neatly contain commands for the 
// motors, to take care of +/- values, a min/max
// power value, & pin setup.

class Motor {
  private:
  byte pwmPin;
  byte dirPin;
  
  public:
    Motor(byte pwmPin, byte dirPin)
    {
        //store the pins in the attributes
        this->pwmPin = pwmPin;
        this->dirPin = dirPin;
        
        // Set our motor driver pins as outputs.
        pinMode( pwmPin, OUTPUT );
        pinMode( dirPin, OUTPUT ); 
            
    }

    void move (float power)
    {
      int actualPower = (int) power;

      //check if the power out of band
      if (actualPower > 255)
      {
        actualPower = 255;
      }
      else if (actualPower < -255)
      {
        actualPower = -255;
      }

//      Serial.print("The power is: ");
//      Serial.println(actualPower);
      if (actualPower > 0) // move forward
      {
        digitalWrite( this->dirPin, LOW  );
        analogWrite( this->pwmPin,actualPower);
      }
      else if (actualPower < 0) // move backward
      {
        digitalWrite( this->dirPin, HIGH  );
        analogWrite( this->pwmPin,-1*actualPower); // since the power should be positive
        
      }
      else // stop
      {
         analogWrite( this->pwmPin,actualPower);
      }
      
    }
    
};

#endif
