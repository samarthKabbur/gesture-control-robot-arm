#include "flex_sensor.h"

Flex_Sensor::Flex_Sensor(){
    // Constructor
}

void Flex_Sensor::initialize(){
    // Initialization tasks if needed
    pinMode(get_flexPin(), INPUT);
}

void Flex_Sensor::calibrate_sensors(){
    // Calibration tasks if needed
}

void Flex_Sensor::printFlexData(){
    // Print data if needed
    Serial.print("Flex Value: ");
    Serial.println(readFlex_Sensor());
}

FlexSensor_t Flex_Sensor::returnFlexData(){
    FlexSensor_t flex_sensor;
    flex_sensor.flex_value = readFlex_Sensor();
    flex_sensor.finger = getFinger_State();
    return flex_sensor;
}

void Flex_Sensor::printFingerState(){
    Serial.print("Finger State: ");
    Serial.println(getFinger_State().is_bent);
}

int Flex_Sensor::readFlex_Sensor(){
    int flex_value = analogRead(get_flexPin());
    return flex_value;
}

bool Flex_Sensor::isBent(){
    if(readFlex_Sensor() < finger.threshold){
        setBend_State(true);
    } else {
        setBend_State(false);
    }
    return finger.is_bent;
}

void Flex_Sensor::setThreshold(int threshold){
    finger.threshold = threshold;
}

/* #region Setters and Getters for Global-Private Variables*/
void Flex_Sensor::set_flexPin(int value){
    flexPin = value;
}
int Flex_Sensor::get_flexPin(){
    return flexPin;
}

void Flex_Sensor::setBend_State(bool value){
    finger.is_bent = value;
}

Finger_State_t Flex_Sensor::getFinger_State(){
    Finger_State_t finger;
    finger.is_bent = isBent();
    finger.threshold = finger.threshold;
    return finger;
}

/* #endregion*/