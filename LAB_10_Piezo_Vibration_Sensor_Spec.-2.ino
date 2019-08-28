#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define sensor A0
#define touch 1

#define deviceID "Dian17D1566950162777"
#define authnRgtNo "12tf1j20x"
#define extrSysID "OPEN_TCP_001PTL001_1000007616"

#define WIFI_SSID "ICT-LAB-2.4G"
#define WIFI_PASS "12345678"
#define TAG_ID "vibration"

IoTMakers g_im;

void init_iotmakers()
 {
  while(1)
 {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
      }
      
      Serial.println(F("Success"));
      
      g_im.init(deviceID, authnRgtNo, extrSysID);

      Serial.print(F("Connect to platform..."));
      while(g_im.connect() < 0)
      {
      Serial.println(F("retrying"));
      delay(100);
      }
      Serial.println(F("Success..."));

      Serial.print(F("Auth..."));
      if(g_im.auth_device() >= 0)
      {
      Serial.println(F("Success..."));
      return;
      }
     }
    }

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  init_iotmakers();
  }

void loop() {
  int digitaltouch;
  int analogtouch;

 if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
   }

   analogtouch = analogRead(sensor);

   //Serial.println("Ready");
  if (analogtouch > 0)
  {
    Serial.println("TOUCH");
    Serial.print("Analog Measured : ");
    Serial.println(analogtouch);
    g_im.send_numdata(TAG_ID, (int)analogtouch);
  }
  else
  {
    Serial.println("NOT TOUCH");
  }
  delay(1000);
  g_im.loop();
}
