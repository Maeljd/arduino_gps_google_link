#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(5, 6);

String gps_url = String("");

void setup()
{
  Serial.begin(9600);
  
  Serial.println("Setup done!");
  Serial.println();

  ss.begin(9600);
}

void loop(){
  get_gps();
  Serial.println(gps_url);
}

void get_gps() {
  float latitude = 1000.00;
  float longitude = 1000.00;
  
  while ((latitude == 1000.00) || (longitude == 1000.00))
  {
    while (ss.available()) 
    {
      int c = ss.read();
      gps.encode(c);
    }
    gps.f_get_position(&latitude, &longitude, NULL);
  }
  gps_url = String("https://www.google.com/maps/search/?api=1&query=") + String(latitude,7) + "," + String(longitude,7);
}
