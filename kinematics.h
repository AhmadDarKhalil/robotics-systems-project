#ifndef _KINEMATICS_H
#define _KINEMATICS_H
#include "encoders.h"
#include "math.h"

class Kinematics {
  private:
  float theta;
  float x;
  float y;

  
  public:

  


  Kinematics() {
    this->x = 0;
    this->y = 0;
    this->theta = 0;
  
} // end of constructor.

float printParamenters ()
{
      Serial.print(this->x,2);
   Serial.print(",");
    Serial.print(this->y,2);
   Serial.print(",");
    Serial.println(this->theta,2);
  
}
// kinematics 
void update(long count_e0_n, long count_e1_n,long old_count_e0, long old_count_e1) {
  long e0_diff = count_e0_n - old_count_e0;
  long e1_diff = count_e1_n - old_count_e1;

    float left_distance = count2mm((float)e0_diff);
    float right_distance = count2mm((float)e1_diff);
//    Serial.print(left_distance,2);
//    Serial.print(",");
//    Serial.println(right_distance,2);
    
    this->theta = this->theta + (left_distance - right_distance)/143.5; // 140mm distancce between wheels
    this->x = this->x + ((left_distance + right_distance)/2)* cos( this->theta);
    this->y = this->y + ((left_distance + right_distance)/2)* sin( this->theta);
    
   
//    Serial.print(this->x,2);
//   Serial.print(",");
//    Serial.print(this->y,2);
//   Serial.print(",");
//    Serial.println(this->theta/6.28*360,2);
}

}; // End of class definition.

#endif
