/*
    CPP Library for the MPU6050 gyroscope, accelerometer and temperature sensor.
    This library is a wrapper for the MPU6050 singlefile code, originally written by Krodal

*/

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

// Use the #region folding for VS Code extension to enable folding
/* #region Setters and Getters for Global Variables */

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

/* #endregion */

void GY521::set_last_read_angle_data(unsigned long time, float x, float y, float z, float x_gyro, float y_gyro, float z_gyro){
    set_last_read_time(time);
    set_last_x_angle(x);
    set_last_y_angle(y);
    set_last_z_angle(z);
    set_last_gyro_x_angle(x_gyro);
    set_last_gyro_y_angle(y_gyro);
    set_last_gyro_z_angle(z_gyro);
}

int GY521::read_gyro_accel_vals(uint8_t* accel_t_gyro_ptr) {
  // Read the raw values.
  // Read 14 bytes at once, 
  // containing acceleration, temperature and gyro.
  // With the default settings of the MPU-6050,
  // there is no filter enabled, and the values
  // are not very stable.  Returns the error value

  accel_t_gyro_union* accel_t_gyro = (accel_t_gyro_union *) accel_t_gyro_ptr;

  int error = MPU6050_read(MPU6050_ACCEL_XOUT_H, (uint8_t *) accel_t_gyro, sizeof(*accel_t_gyro));

  // Swap all high and low bytes.
  // After this, the registers values are swapped, 
  // so the structure name like x_accel_l does no 
  // longer contain the lower byte.
    uint8_t swap;
    #define SWAP(x,y) swap = x; x = y; y = swap

    SWAP ((*accel_t_gyro).reg.x_accel_h, (*accel_t_gyro).reg.x_accel_l);
    SWAP ((*accel_t_gyro).reg.y_accel_h, (*accel_t_gyro).reg.y_accel_l);
    SWAP ((*accel_t_gyro).reg.z_accel_h, (*accel_t_gyro).reg.z_accel_l);
    SWAP ((*accel_t_gyro).reg.t_h, (*accel_t_gyro).reg.t_l);
    SWAP ((*accel_t_gyro).reg.x_gyro_h, (*accel_t_gyro).reg.x_gyro_l);
    SWAP ((*accel_t_gyro).reg.y_gyro_h, (*accel_t_gyro).reg.y_gyro_l);
    SWAP ((*accel_t_gyro).reg.z_gyro_h, (*accel_t_gyro).reg.z_gyro_l);

    return error;
}
    
// The sensor should be motionless on a horizontal surface 
//  while calibration is happening
void GY521::calibrate_sensors() {
    int                   num_readings = 10;
    float                 x_accel = 0;
    float                 y_accel = 0;
    float                 z_accel = 0;
    float                 x_gyro = 0;
    float                 y_gyro = 0;
    float                 z_gyro = 0;
    accel_t_gyro_union    accel_t_gyro;
    //Serial.println("Starting Calibration");

    // Discard the first set of values read from the IMU
    read_gyro_accel_vals((uint8_t *) &accel_t_gyro);

    // Read and average the raw values from the IMU
    for (int i = 0; i < num_readings; i++) {
        read_gyro_accel_vals((uint8_t *) &accel_t_gyro);
        x_accel += accel_t_gyro.value.x_accel;
        y_accel += accel_t_gyro.value.y_accel;
        z_accel += accel_t_gyro.value.z_accel;
        x_gyro += accel_t_gyro.value.x_gyro;
        y_gyro += accel_t_gyro.value.y_gyro;
        z_gyro += accel_t_gyro.value.z_gyro;
        delay(100);
    }
    x_accel /= num_readings;
    y_accel /= num_readings;
    z_accel /= num_readings;
    x_gyro /= num_readings;
    y_gyro /= num_readings;
    z_gyro /= num_readings;

    // Store the raw calibration values globally
    set_base_x_accel(x_accel);
    set_base_y_accel(y_accel);
    set_base_z_accel(z_accel);
    set_base_x_gyro(x_gyro);
    set_base_y_gyro(y_gyro);
    set_base_z_gyro(z_gyro);
  //Serial.println("Finishing Calibration");
}

int GY521::MPU6050_read(int start, uint8_t *buffer, int size){
    int i, n, error;

    Wire.beginTransmission(MPU6050_I2C_ADDRESS);
    n = Wire.write(start);
    if (n != 1)
    return (-10);

    n = Wire.endTransmission(false);    // hold the I2C-bus
    if (n != 0)
    return (n);

    // Third parameter is true: relase I2C-bus after data is read.
    Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
    i = 0;
    while(Wire.available() && i<size)
    {
    buffer[i++]=Wire.read();
    }
    if ( i != size)
    return (-11);

    return (0);  // return : no error
}

// --------------------------------------------------------
// MPU6050_write
//
// This is a common function to write multiple bytes to an I2C device.
//
// If only a single register is written,
// use the function MPU_6050_write_reg().
//
// Parameters:
//   start : Start address, use a define for the register
//   pData : A pointer to the data to write.
//   size  : The number of bytes to write.
//
// If only a single register is written, a pointer
// to the data has to be used, and the size is
// a single byte:
//   int data = 0;        // the data to write
//   MPU6050_write (MPU6050_PWR_MGMT_1, &c, 1);
//
int GY521::MPU6050_write(int start, const uint8_t *pData, int size){
    int n, error;

    Wire.beginTransmission(MPU6050_I2C_ADDRESS);
    n = Wire.write(start);        // write the start address
    if (n != 1)
    return (-20);

    n = Wire.write(pData, size);  // write data bytes
    if (n != size)
    return (-21);

    error = Wire.endTransmission(true); // release the I2C-bus
    if (error != 0)
    return (error);

    return (0);         // return : no error
}

// --------------------------------------------------------
// MPU6050_write_reg
//
// An extra function to write a single register.
// It is just a wrapper around the MPU_6050_write()
// function, and it is only a convenient function
// to make it easier to write a single register.
//
int GY521::MPU6050_write_reg(int reg, uint8_t data){
    int error;

    error = MPU6050_write(reg, &data, 1);

    return (error);
}

// Initialize the sensor
void GY521::initialize() {
    // Wire.beginTransmission(0x68); // MPU-6050 I2C address
    // Wire.write(0x6B); // PWR_MGMT_1 register
    // Wire.write(0);    // Wake up the MPU-6050
    // Wire.endTransmission(true);
    // Serial.println("GY-521 initialized.");
    int error;
    uint8_t c;


    Serial.begin(19200);
    /*
    Serial.println(F("InvenSense MPU-6050"));
    Serial.println(F("June 2012"));
    */
    // Initialize the 'Wire' class for the I2C-bus.
    Wire.begin();


    // default at power-up:
    //    Gyro at 250 degrees second
    //    Acceleration at 2g
    //    Clock source at internal 8MHz
    //    The device is in sleep mode.
    //

    error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
    /*
    Serial.print(F("WHO_AM_I : "));
    Serial.print(c,HEX);
    Serial.print(F(", error = "));
    Serial.println(error,DEC);
    */

    // According to the datasheet, the 'sleep' bit
    // should read a '1'. But I read a '0'.
    // That bit has to be cleared, since the sensor
    // is in sleep mode at power-up. Even if the
    // bit reads '0'.
    error = MPU6050_read (MPU6050_PWR_MGMT_2, &c, 1);
    /*
    Serial.print(F("PWR_MGMT_2 : "));
    Serial.print(c,HEX);
    Serial.print(F(", error = "));
    Serial.println(error,DEC);
    */

    // Clear the 'sleep' bit to start the sensor.
    MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);

    //Initialize the angles
    calibrate_sensors();  
    set_last_read_angle_data(millis(), 0, 0, 0, 0, 0, 0);
}

// Read and print accelerometer data
void GY521::printAccelerometerData() {
    // int accelX = readWord(0x68, 0x3B);
    // int accelY = readWord(0x68, 0x3D);
    // int accelZ = readWord(0x68, 0x3F);

    // Serial.print("Accel X: ");
    // Serial.println(wordToScaledFloat(accelX, 16384.0));
    // Serial.print("Accel Y: ");
    // Serial.println(wordToScaledFloat(accelY, 16384.0));
    // Serial.print("Accel Z: ");
    // Serial.println(wordToScaledFloat(accelZ, 16384.0));
    int error;
    double dT;
    accel_t_gyro_union accel_t_gyro;

    // Read the raw values.
    error = read_gyro_accel_vals((uint8_t*) &accel_t_gyro);

    // Get the time of reading for rotation computations
    unsigned long t_now = millis();
    float dt =(t_now - get_last_read_time())/1000.0;
    /*
    Serial.print(F("Read accel, temp and gyro, error = "));
    Serial.println(error,DEC);
    */

    // Print the raw acceleration values
    Serial.print(F("accel x,y,z: "));
    Serial.print(accel_t_gyro.value.x_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_accel, DEC);
    Serial.println(F("")); 

    // Get raw acceleration values
    //float G_CONVERT = 16384;
    float accel_x = accel_t_gyro.value.x_accel;
    float accel_y = accel_t_gyro.value.y_accel;
    float accel_z = accel_t_gyro.value.z_accel;

    // Get angle values from accelerometer
    float RADIANS_TO_DEGREES = 180/3.14159;
    //  float accel_vector_length = sqrt(pow(accel_x,2) + pow(accel_y,2) + pow(accel_z,2));
    float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;

    float accel_angle_z = 0;

    // Send the data to the serial port
    Serial.print(F("DEL:"));              //Delta T
    Serial.print(dt, DEC);
    Serial.print(F("#ACC:"));              //Accelerometer angle
    Serial.print(accel_angle_x, 2);
    Serial.print(F(","));
    Serial.print(accel_angle_y, 2);
    Serial.print(F(","));
    Serial.print(accel_angle_z, 2);

    // Delay so we don't swamp the serial port
    // delay(5);

}

// Read and print gyroscope data
void GY521::printGyroscopeData() {
    // int gyroX = readWord(0x68, 0x43);
    // int gyroY = readWord(0x68, 0x45);
    // int gyroZ = readWord(0x68, 0x47);

    // Serial.print("Gyro X: ");
    // Serial.println(wordToScaledFloat(gyroX, 131.0));
    // Serial.print("Gyro Y: ");
    // Serial.println(wordToScaledFloat(gyroY, 131.0));
    // Serial.print("Gyro Z: ");
    // Serial.println(wordToScaledFloat(gyroZ, 131.0));
    int error;
    double dT;
    accel_t_gyro_union accel_t_gyro;

    /*
    Serial.println(F(""));
    Serial.println(F("MPU-6050"));
    */

    // Read the raw values.
    error = read_gyro_accel_vals((uint8_t*) &accel_t_gyro);

    // Get the time of reading for rotation computations
    unsigned long t_now = millis();

    // Print the raw gyro values.
    Serial.print(F("raw gyro x,y,z : "));
    Serial.print(accel_t_gyro.value.x_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_gyro, DEC);
    Serial.print(F(", "));
    Serial.println(F(""));

    // Convert gyro values to degrees/sec
    float FS_SEL = 131;
    /*
    float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro)/FS_SEL;
    float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro)/FS_SEL;
    float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro)/FS_SEL;
    */
    float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro)/FS_SEL;
    float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro)/FS_SEL;
    float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro)/FS_SEL;

    // Compute the (filtered) gyro angles
    float dt =(t_now - get_last_read_time())/1000.0;
    float gyro_angle_x = gyro_x*dt + get_last_x_angle();
    float gyro_angle_y = gyro_y*dt + get_last_y_angle();
    float gyro_angle_z = gyro_z*dt + get_last_z_angle();

    // Compute the drifting gyro angles
    float unfiltered_gyro_angle_x = gyro_x*dt + get_last_gyro_x_angle();
    float unfiltered_gyro_angle_y = gyro_y*dt + get_last_gyro_y_angle();
    float unfiltered_gyro_angle_z = gyro_z*dt + get_last_gyro_z_angle();

    // Send the data to the serial port
    Serial.print(F("DEL:"));              //Delta T
    Serial.print(dt, DEC);
    Serial.print(F("#GYR:"));
    Serial.print(unfiltered_gyro_angle_x, 2);        //Gyroscope angle
    Serial.print(F(","));
    Serial.print(unfiltered_gyro_angle_y, 2);
    Serial.print(F(","));
    Serial.print(unfiltered_gyro_angle_z, 2);

    // Delay so we don't swamp the serial port
    // delay(5);
}

// Read and print temperature
void GY521::printTemperature() {
    // int tempRaw = readWord(0x68, 0x41);
    // float temperature = tempRaw / 340.0 + 36.53; // Formula from MPU-6050 datasheet

    // Serial.print("Temperature: ");
    // Serial.print(temperature);
    // Serial.println(" °C");
    int error;
    double dT;
    accel_t_gyro_union accel_t_gyro;

    /*
    Serial.println(F(""));
    Serial.println(F("MPU-6050"));
    */

    // Read the raw values.
    error = read_gyro_accel_vals((uint8_t*) &accel_t_gyro);

    // Get the time of reading for rotation computations
    unsigned long t_now = millis();

    // The temperature sensor is -40 to +85 degrees Celsius.
    // It is a signed integer.
    // According to the datasheet: 
    //   340 per degrees Celsius, -512 at 35 degrees.
    // At 0 degrees: -512 - (340 * 35) = -12412 
    Serial.print(F("temperature: "));
    dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
    Serial.print(dT, 3);
    Serial.print(F(" degrees Celsius"));
    Serial.println(F(""));
}

void GY521::printFilteredAngle(){
        int error;
    double dT;
    accel_t_gyro_union accel_t_gyro;

    /*
    Serial.println(F(""));
    Serial.println(F("MPU-6050"));
    */

    // Read the raw values.
    error = read_gyro_accel_vals((uint8_t*) &accel_t_gyro);

    // Get the time of reading for rotation computations
    unsigned long t_now = millis();

    /*
    Serial.print(F("Read accel, temp and gyro, error = "));
    Serial.println(error,DEC);


    // Print the raw acceleration values
    Serial.print(F("accel x,y,z: "));
    Serial.print(accel_t_gyro.value.x_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_accel, DEC);
    Serial.println(F(""));
    */ 

    // The temperature sensor is -40 to +85 degrees Celsius.
    // It is a signed integer.
    // According to the datasheet: 
    //   340 per degrees Celsius, -512 at 35 degrees.
    // At 0 degrees: -512 - (340 * 35) = -12412
    /*  
    Serial.print(F("temperature: "));
    dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
    Serial.print(dT, 3);
    Serial.print(F(" degrees Celsius"));
    Serial.println(F(""));


    // Print the raw gyro values.
    Serial.print(F("raw gyro x,y,z : "));
    Serial.print(accel_t_gyro.value.x_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_gyro, DEC);
    Serial.print(F(", "));
    Serial.println(F(""));
    */

    // Convert gyro values to degrees/sec
    float FS_SEL = 131;
    /*
    float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro)/FS_SEL;
    float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro)/FS_SEL;
    float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro)/FS_SEL;
    */
    float gyro_x = (accel_t_gyro.value.x_gyro - base_x_gyro)/FS_SEL;
    float gyro_y = (accel_t_gyro.value.y_gyro - base_y_gyro)/FS_SEL;
    float gyro_z = (accel_t_gyro.value.z_gyro - base_z_gyro)/FS_SEL;


    // Get raw acceleration values
    //float G_CONVERT = 16384;
    float accel_x = accel_t_gyro.value.x_accel;
    float accel_y = accel_t_gyro.value.y_accel;
    float accel_z = accel_t_gyro.value.z_accel;

    // Get angle values from accelerometer
    float RADIANS_TO_DEGREES = 180/3.14159;
    //  float accel_vector_length = sqrt(pow(accel_x,2) + pow(accel_y,2) + pow(accel_z,2));
    float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;

    float accel_angle_z = 0;

    // Compute the (filtered) gyro angles
    float dt =(t_now - get_last_read_time())/1000.0;
    float gyro_angle_x = gyro_x*dt + get_last_x_angle();
    float gyro_angle_y = gyro_y*dt + get_last_y_angle();
    float gyro_angle_z = gyro_z*dt + get_last_z_angle();

    // Compute the drifting gyro angles
    float unfiltered_gyro_angle_x = gyro_x*dt + get_last_gyro_x_angle();
    float unfiltered_gyro_angle_y = gyro_y*dt + get_last_gyro_y_angle();
    float unfiltered_gyro_angle_z = gyro_z*dt + get_last_gyro_z_angle();

    // Apply the complementary filter to figure out the change in angle - choice of alpha is
    // estimated now.  Alpha depends on the sampling rate...
    float alpha = 0.96;
    float angle_x = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
    float angle_y = alpha*gyro_angle_y + (1.0 - alpha)*accel_angle_y;
    float angle_z = gyro_angle_z;  //Accelerometer doesn't give z-angle

    // Update the saved data with the latest values
    set_last_read_angle_data(t_now, angle_x, angle_y, angle_z, unfiltered_gyro_angle_x, unfiltered_gyro_angle_y, unfiltered_gyro_angle_z);

    // Send the data to the serial port
    // Serial.print(F("DEL:"));              //Delta T
    // Serial.print(dt, DEC);
    // Serial.print(F("#ACC:"));              //Accelerometer angle
    // Serial.print(accel_angle_x, 2);
    // Serial.print(F(","));
    // Serial.print(accel_angle_y, 2);
    // Serial.print(F(","));
    // Serial.print(accel_angle_z, 2);
    // Serial.print(F("#GYR:"));
    // Serial.print(unfiltered_gyro_angle_x, 2);        //Gyroscope angle
    // Serial.print(F(","));
    // Serial.print(unfiltered_gyro_angle_y, 2);
    // Serial.print(F(","));
    // Serial.print(unfiltered_gyro_angle_z, 2);
    Serial.print(F("#FIL:"));             //Filtered angle
    Serial.print(angle_x, 2);
    Serial.print(F(","));
    Serial.print(angle_y, 2);
    Serial.print(F(","));
    Serial.print(angle_z, 2);
    Serial.println(F(""));

    // Delay so we don't swamp the serial port
    // delay(5);
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


