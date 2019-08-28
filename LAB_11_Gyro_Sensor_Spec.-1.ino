#include <Wire.h>
const int MPU = 0x68; // I2C address of MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //gyro scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  //acc scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);
 }

void loop() {
 Wire.beginTransmission(MPU);
 Wire.write(0x3B);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU, 14, true);

AcX = Wire.read() << 8 | Wire.read(); // ACCEL_X
AcY = Wire.read() << 8 | Wire.read(); // ACCEL_Y
AcZ = Wire.read() << 8 | Wire.read(); // ACCEL_Z
Tmp = Wire.read() << 8 | Wire.read(); // Temperature
GyX = Wire.read() << 8 | Wire.read(); // GYRO_X
GyY = Wire.read() << 8 | Wire.read(); // GYRO_Y
GyZ = Wire.read() << 8 | Wire.read(); // GYRO_Z

int xAxis = (AcX - 1090);
int yAxis = (AcY - 930);
int zAxis = (AcZ - 1000);

  Serial.print("xAxis : ");
  Serial.print(xAxis);
  Serial.println();
  Serial.print("yAxis : ");
  Serial.print(yAxis);
  Serial.println();
  Serial.print("zAxis : ");
  Serial.print(zAxis);
  Serial.println();
  Serial.print("temp : ");
  Serial.print(Tmp);
  Serial.println();
  Serial.print("G X axis : ");
  Serial.print(GyX);
  Serial.println();
  Serial.print("G Y axis : ");
  Serial.print(GyY);
  Serial.println();
  Serial.print("G Z axis : ");
  Serial.print(GyZ);
  Serial.println();
  Serial.println();

delay(1000);
}
