#if !defined(_LINESENSOR_H)
#define _LINESENSOR_H

#include "constants.h"

//this class store information for 3 line sensors with all their operations
class LineSensor {
  private:
    byte pin[NUMBER_OF_SENSORS]; // pins numbers (left,center,right)
    float bias[NUMBER_OF_SENSORS]; // values of bias for each sensor before joining the line
    
  public:
// Required function, class Constructor: 
    LineSensor (){
      // store pins numbers
      this->pin[LINE_LEFT_PIN_INDEX] =LINE_LEFT_PIN ;
      this->pin[LINE_CENTER_PIN_INDEX] =LINE_CENTRE_PIN ;
      this->pin[LINE_RIGHT_PIN_INDEX] =LINE_RIGHT_PIN ;      
      // assign the pins as inputs
      pinMode(pin[LINE_LEFT_PIN_INDEX], INPUT);
      pinMode(pin[LINE_CENTER_PIN_INDEX], INPUT);
      pinMode(pin[LINE_RIGHT_PIN_INDEX], INPUT);
      
    }

    int getSensorValueBeforBias(int sensorIndex)
    {
      return analogRead(this->pin[sensorIndex]);
    }
    
    float getCalibratedSensorValue(int sensorIndex)
    {
      
      return ( (float)analogRead(this->pin[sensorIndex]) - this->getSensorBiasValue(sensorIndex) );
    }

    float getSensorBiasValue(int sensorIndex)
    {
      return this->bias[sensorIndex];
    }
    
    void displayCalibratedSensorsOnSerialMonitor()
    {
          Serial.print (  this->getCalibratedSensorValue(LINE_LEFT_PIN_INDEX),1);
          Serial.print (  ", ");
          Serial.print (  this->getCalibratedSensorValue(LINE_CENTER_PIN_INDEX),1);
          Serial.print (  ", ");
          Serial.println ( this->getCalibratedSensorValue(LINE_RIGHT_PIN_INDEX),1);

    }

    void displayBiasOnSerialMonitor()
    {
          Serial.print (  this->getSensorBiasValue(LINE_LEFT_PIN_INDEX));
          Serial.print (  ", ");
          Serial.print (  this->getSensorBiasValue(LINE_CENTER_PIN_INDEX));
          Serial.print (  ", ");
          Serial.println ( this->getSensorBiasValue(LINE_RIGHT_PIN_INDEX));

    }

    //funtion to calibrateAll sensors bias
    void calibrateAll()
    {
      float leftSum=0,centerSum=0,rightSum=0;
      analogWrite( BUZZ, 1  ); // start calibiration
      for (int i = 0 ; i < CALIBIRATION_SAMPLES; i++)
      {
      leftSum+= this->getSensorValueBeforBias(LINE_LEFT_PIN_INDEX);
      centerSum+= this->getSensorValueBeforBias(LINE_CENTER_PIN_INDEX);
      rightSum+= this->getSensorValueBeforBias(LINE_RIGHT_PIN_INDEX);
      delay(CALIBIRATION_SAMPLE_TIME_MS); // 10ms by defualt
      
      }
      //assign the values for bias
      this->bias[LINE_LEFT_PIN_INDEX] = leftSum/CALIBIRATION_SAMPLES;
      this->bias[LINE_CENTER_PIN_INDEX] = centerSum/CALIBIRATION_SAMPLES;
      this->bias[LINE_RIGHT_PIN_INDEX] = rightSum/CALIBIRATION_SAMPLES;
      
      digitalWrite( BUZZ, LOW  ); // end calibiration
      
    }

    float WeightedLineSensingM ()
    {
      float total,p[3],M;
      total= fabs (this->getCalibratedSensorValue(LINE_LEFT_PIN_INDEX)) + fabs(this->getCalibratedSensorValue(LINE_CENTER_PIN_INDEX)) + fabs(this->getCalibratedSensorValue(LINE_RIGHT_PIN_INDEX));
      for(int i=0; i<NUMBER_OF_SENSORS; i++)
      {
        p[i] = this->getCalibratedSensorValue(i)/total;
      }
      M = p[LINE_LEFT_PIN_INDEX] - p[LINE_RIGHT_PIN_INDEX];
      return M; 
    }


    boolean isOnLine()
    {
      float l, c, r;
      l = this->getCalibratedSensorValue(LINE_LEFT_PIN_INDEX);
      c = this->getCalibratedSensorValue(LINE_CENTER_PIN_INDEX);
      r = this->getCalibratedSensorValue(LINE_RIGHT_PIN_INDEX);
      
        if(l > LINE_LEFT_PIN_THESOULD || r > LINE_RIGHT_PIN_THESOULD || c > LINE_CENTER_PIN_THESOULD)
          return true;
        return false;

    }
    boolean isOnLineCenter()
    {
      float l, c, r;
      l = this->getCalibratedSensorValue(LINE_LEFT_PIN_INDEX);
      c = this->getCalibratedSensorValue(LINE_CENTER_PIN_INDEX);
      r = this->getCalibratedSensorValue(LINE_RIGHT_PIN_INDEX);
      
        if(this->isOnLine() && c > LINE_CENTER_PIN_THESOULD)
          return true;
        return false;

    }

}; // don't forget the semicolon at the end of the class
#endif
