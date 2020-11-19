#include "constants.h"
#include "lineSensor.h"
#include "motor.h"
#include "encoders.h"
#include "kinematics.h"
// Pin definitions, to make the
// code easier to read.



LineSensor sensors; // sensor array
Motor leftMotor (L_PWM_PIN, L_DIR_PIN); // left motor
Motor rightMotor(R_PWM_PIN, R_DIR_PIN);  // right motor
Kinematics kinematics;
unsigned long timestamp;
long last_millis;
float M ;
float lastM;
float last_error = 0;
int endTrials = 0;
long last_count_e0;
long last_count_e1;

// Setup, only runs once when powered on.
void setup() {
  setupEncoder0();
  last_count_e0 = count_e0;
  setupEncoder1();
  last_count_e1 = count_e1;
  
  pinMode( BUZZ, OUTPUT );
  // Start up the Serial for debugging.
  Serial.begin(9600);
  delay(1000);
  // Print reset so we can catch any reset error.
  Serial.println(" ***Reset*** ");
  timestamp = millis();
  last_millis = millis();
  sensors.calibrateAll(); // it takes 1 sec
  start();
  //delay(3000); // for placing the robot on the map
  // lastM = sensors.WeightedLineSensingM();

}




void loop() {


  if (sensors.isOnLine()) {

    //if (millis() - timestamp > 5){ // try 5

    //sensors.displayBiasOnSerialMonitor();
    M = sensors.WeightedLineSensingM();
    //float MTotal = (M + lastM)/2;
    //lastM = M;
    float PID_output = updatePID(M, 0, POWER_FACTOR_FOR_ROTATION, 10, 0);
    //Serial.println (M*6);
    rightMotor.move(PID_output + POWER_FACTOR_FOR_MOVEMENT );
    leftMotor.move(-PID_output + POWER_FACTOR_FOR_MOVEMENT);
    //kinematics.update(count_e0,count_e1,last_count_e0,last_count_e1);
    //last_count_e0 = count_e0;
    //last_count_e1 = count_e1; 

  }
   //}
  else
  {
//    if (endTrials == 1) // this case, the robot reaches the end of the path (the return home should be there but I had some problems with it
//    {
//      rightMotor.move(0);
//      leftMotor.move(0);
//      analogWrite(BUZZ, 200);
//      delay(10000);
//    }
//
//    move_mm(45, leftMotor, rightMotor, POWER_FACTOR_FOR_MOVEMENT); // move for 4.5cm (extra 0.5cm for confidence)
//    if (!sensors.isOnLine()) // if not on the line, rotate 180 degree
//    {
//      rotate (180, leftMotor, rightMotor, 1 ); // rotate 180 degree
//    }
//    else
//    {
//      endTrials = 1; // next time, this case will end the path
//    }

      analogWrite(BUZZ, 2);
    int flag = 0 ; // 0: corner, 1: end of the map
    move_mm(6, leftMotor, rightMotor, POWER_FACTOR_FOR_MOVEMENT); // move for 6mm
    if (!sensors.isOnLine())
    {
      move_mm(8, leftMotor, rightMotor, POWER_FACTOR_FOR_MOVEMENT); // move for 8mm to find the line
      if (sensors.isOnLine()){ // if true then end of the map
        flag = 1; //end of the map
        //here we can put the logic to display the shape
      for (int i = 0 ; i< 500; i++){
        rightMotor.move(0);
        leftMotor.move(0);
      digitalWrite(BUZZ, HIGH);
      delay(8);
      digitalWrite(BUZZ, LOW);
      delay(2);
      }
    }
    }
    if (flag == 0){ // corner
     int i =0 ; // variable used to make sure that the robot on the line

    while (!sensors.isOnLineCenter() || (i++ != 2)) //if online, read 3 reading to make sure it is online
    {
      rotate (2, leftMotor, rightMotor, -1 ); // rotate 180 degree
    }
    
      analogWrite(BUZZ, 0);
    }
  }




}

void start()
{
  while (!sensors.isOnLine()) {
    rightMotor.move(POWER_FACTOR_FOR_MOVEMENT);
    leftMotor.move(POWER_FACTOR_FOR_MOVEMENT);

  }
  move_mm(30, leftMotor, rightMotor, POWER_FACTOR_FOR_MOVEMENT); // this is for joining the line
  rotate (90, leftMotor, rightMotor, 1 ); // rotate 90 degree

}
float updatePID(float demand, float measurement, int Kp, int Ki , int Kd) {

  //Calculate how much time (in milliseconds) has
  // bassed since the last update call
  // Note, we do this in type "long", and then
  // typecast the final result to "float".
  long time_now = millis();
  long diff_time = time_now - last_millis;
  last_millis = time_now;

  float time_delta = (float)diff_time;

  // Calculate error between demand and measurement.
  float error = demand - measurement;

  //This represents the error derivative
  float error_delta = (error - last_error) / diff_time ;
  last_error = error;

  // Integral term.
  float integral_error = integral_error + error * diff_time;

  //Calculate P,I,D Term contributions.
  float Kp_output = Kp * error;
  float Kd_output = Kd * error_delta;
  float Ki_output = Ki * integral_error;

  //Add the three components to get the total output
  float output_signal = Kp_output + Kd_output +  Ki_output;

  // Pass the result back.
  return output_signal;
}
