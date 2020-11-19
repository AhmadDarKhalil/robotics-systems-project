#if !defined(_CONSTANTS_H)
#define _CONSTANTS_H


//class Constants {
extern const int NUMBER_OF_SENSORS = 3;
extern const byte L_PWM_PIN = 10;
extern const byte L_DIR_PIN = 16;
extern const byte R_PWM_PIN = 9;
extern const byte R_DIR_PIN = 15;
extern const byte POWER_FACTOR_FOR_ROTATION = 15; // best is 50, 200 for 90deg 150-160 [145-150]
extern const byte POWER_FACTOR_FOR_MOVEMENT = 15; // best is 40, 10 for 90deg 15 [15] and I = 5, D = 0
extern const byte POWER_FACTOR_FOR_ENCOERS = 15; 
extern const byte LINE_LEFT_PIN = A2;
extern const byte LINE_CENTRE_PIN = A3;
extern const byte LINE_RIGHT_PIN = A4;
extern const int LINE_LEFT_PIN_THESOULD  = 150;
extern const int LINE_CENTER_PIN_THESOULD  = 150;
extern const int LINE_RIGHT_PIN_THESOULD =  150;

extern const int LINE_LEFT_PIN_INDEX = 0;
extern const int LINE_CENTER_PIN_INDEX = 1;
extern const int LINE_RIGHT_PIN_INDEX = 2;
extern const int BUZZ = 6;
extern const int CALIBIRATION_SAMPLES = 50;
extern const int CALIBIRATION_SAMPLE_TIME_MS = 20;
extern const int WHEEL_RADIUS_MM = 35;
extern const int ENCODER_COUNT_PER_REV = 1440;

extern const int E1_A_PIN = 7;
extern const int E1_B_PIN = 23;
extern const int E0_A_PIN = 26;


//};

#endif
