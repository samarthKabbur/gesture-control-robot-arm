/*
@Author : Samarth Kabbur
@Date : 12/2024
@Description : Full custom library for the Adafruit Flex Sensor to 
    to be able to tell when a finger is bent or not.


*/

#ifndef flex_sensor_H
#define flex_sensor_H

   
#include <Arduino.h>
#include <Wire.h>

typedef struct Finger_State {
    bool is_bent;
    int threshold;
} Finger_State_t;

typedef struct FlexSensor {
    int flex_value;
    Finger_State_t finger;
} FlexSensor_t;

class Flex_Sensor {
public:

    Flex_Sensor(); // Constructor
    void initialize();
    void calibrate_sensors();
    void printFlexData();
    int readFlex_Sensor();
    bool isBent();
    void printFingerState();
    FlexSensor_t returnFlexData();

    

    /* #region Setters and Getters */
    void set_flexPin(int value);
    int get_flexPin();

    void setThreshold(int threshold);

    void setBend_State(bool value);
    Finger_State_t getFinger_State();
    /* #endregion */
private:
    int flexPin;
    Finger_State_t finger;
};

#endif