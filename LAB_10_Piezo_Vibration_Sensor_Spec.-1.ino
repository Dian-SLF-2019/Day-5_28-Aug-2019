#define sensor A0
#define touch 1

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  }

void loop() {
  int digitaltouch;
  int analogtouch;
  //Serial.println("Ready");
  if (analogRead(sensor)>0)
  {
    Serial.println("TOUCH");
    Serial.print("Analog Measured : ");
    Serial.println(analogRead(sensor));
  }
  else
  {
    Serial.println("NOT TOUCH");
  }
  delay(1000);
  
}
