#include "GY521.h"

// Constructor
GY521::GY521() 
    :   last_read_time(0),
        last_x_angle(0),
        last_y_angle(0),
        last_z_angle(0),
        last_gyro_x_angle(0),
        last_gyro_y_angle(0),
        last_gyro_z_angle(0),
        base_x_accel(0),
        base_y_accel(0),
        base_z_accel(0),
        base_x_gyro(0),
        base_y_gyro(0),
        base_z_gyro(0)
{
    // Initialization tasks if needed
}

// Setters and Getters for Global Variables
    // last_read_time
void GY521::set_last_read_time(unsigned long value){
    last_read_time = value;
}
unsigned long GY521::get_last_read_time(){
    return last_read_time;
}

    // last_x_angle
void GY521::set_last_x_angle(float value){
    last_x_angle = value;
}
float GY521::get_last_x_angle(){
    return last_x_angle;
}

// last y angle
void GY521::set_last_y_angle(float value){
    last_y_angle = value;
}
float GY521::get_last_y_angle(){
    return last_y_angle;
}

// last z angle
void GY521::set_last_z_angle(float value){
    last_z_angle = value;
}
float GY521::get_last_z_angle(){
    return last_z_angle;
}

// last gyro x angle
void GY521::set_last_gyro_x_angle(float value){
    last_gyro_x_angle = value;
}
float GY521::get_last_gyro_x_angle(){
    return last_gyro_x_angle;
}

// last gyro y angle
void GY521::set_last_gyro_y_angle(float value){
    last_gyro_y_angle = value;
}
float GY521::get_last_gyro_y_angle(){
    return last_gyro_y_angle;
}

// last gyro z angle
void GY521::set_last_gyro_z_angle(float value){
    last_gyro_z_angle = value;
}
float GY521::get_last_gyro_z_angle(){
    return last_gyro_z_angle;
}

// base x accel
void GY521::set_base_x_accel(float value){
    base_x_accel = value;
}
float GY521::get_base_x_accel(){
    return base_x_accel;
}

// base y accel
void GY521::set_base_y_accel(float value){
    base_y_accel = value;
}
float GY521::get_base_y_accel(){
    return base_y_accel;
}

// base z accel
void GY521::set_base_z_accel(float value){
    base_z_accel = value;
}
float GY521::get_base_z_accel(){
    return base_z_accel;
}

// base x gyro
void GY521::set_base_x_gyro(float value){
    base_x_gyro = value;
}
float GY521::get_base_x_gyro(){
    return base_x_gyro;
}

// base y gyro
void GY521::set_base_y_gyro(float value){
    base_y_gyro = value;
}
float GY521::get_base_y_gyro(){
    return base_y_gyro;
}

// base z gyro
void GY521::set_base_z_gyro(float value){
    base_z_gyro = value;
}
float GY521::get_base_z_gyro(){
    return base_z_gyro;
}

// Initialize the sensor
void GY521::initialize() {
    Wire.beginTransmission(0x68); // MPU-6050 I2C address
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // Wake up the MPU-6050
    Wire.endTransmission(true);
    Serial.println("GY-521 initialized.");
}

// Read and print accelerometer data
void GY521::printAccelerometerData() {
    int accelX = readWord(0x68, 0x3B);
    int accelY = readWord(0x68, 0x3D);
    int accelZ = readWord(0x68, 0x3F);

    Serial.print("Accel X: ");
    Serial.println(wordToScaledFloat(accelX, 16384.0));
    Serial.print("Accel Y: ");
    Serial.println(wordToScaledFloat(accelY, 16384.0));
    Serial.print("Accel Z: ");
    Serial.println(wordToScaledFloat(accelZ, 16384.0));
}

// Read and print gyroscope data
void GY521::printGyroscopeData() {
    int gyroX = readWord(0x68, 0x43);
    int gyroY = readWord(0x68, 0x45);
    int gyroZ = readWord(0x68, 0x47);

    Serial.print("Gyro X: ");
    Serial.println(wordToScaledFloat(gyroX, 131.0));
    Serial.print("Gyro Y: ");
    Serial.println(wordToScaledFloat(gyroY, 131.0));
    Serial.print("Gyro Z: ");
    Serial.println(wordToScaledFloat(gyroZ, 131.0));
}

// Read and print temperature
void GY521::printTemperature() {
    int tempRaw = readWord(0x68, 0x41);
    float temperature = tempRaw / 340.0 + 36.53; // Formula from MPU-6050 datasheet

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
}

// Helper to read a word (two bytes) from the sensor
int GY521::readWord(int address, int reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, 2);

    int high = Wire.read();
    int low = Wire.read();
    return (high << 8) | low;
}

// Helper to scale raw values to float
float GY521::wordToScaledFloat(int rawValue, float scale) {
    return rawValue / scale;
}

