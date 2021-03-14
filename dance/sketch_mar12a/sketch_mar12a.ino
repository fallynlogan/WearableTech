// Includes.
#include <LSM303AGR_ACC_Sensor.h>
#include <LSM303AGR_MAG_Sensor.h>

#if defined(ARDUINO_SAM_DUE)
#define DEV_I2C Wire1   //Define which I2C bus is used. Wire1 for the Arduino Due
#define SerialPort Serial
#else
#define DEV_I2C Wire    //Or Wire
#define SerialPort Serial
#endif

// Components.
LSM303AGR_ACC_Sensor Acc(&DEV_I2C);

String data;
String x;
String y;

void setup() {
  // Led.
  pinMode(13, OUTPUT);

  // Initialize serial for output.
  SerialPort.begin(9600);
  
  // Initialize I2C bus.
  DEV_I2C.begin();

  // Initlialize components.
  Acc.begin();
  Acc.Enable();
}

void loop() {
  // Read accelerometer LSM303AGR.
  int32_t accelerometer[3];
  Acc.GetAxes(accelerometer);

  x = String(accelerometer[0]);
  y = String(accelerometer[1]);
  // Output data.
  data = x + "," + y;
  Serial.println(data);
  delay(500);

}
