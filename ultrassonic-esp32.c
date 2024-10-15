#define BLYNK_TEMPLATE_ID           "TMPL22KB59kWj"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "QbFnbnuP4N46qRzD-VRcV-5PR-3DJXEc"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <NewPing.h>

// Your Wi-Fi credentials
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

// Your Blynk authentication token
char auth[] = "TL13ovYDvJkX4fLOSSsnlhVY7wpQxOae";

// Define the GPIO pins for the ultrasonic sensor
#define trigPin 2
#define echoPin 4

// Create an instance of the NewPing library
NewPing sonar(trigPin, echoPin);

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();

  // Trigger an ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the distance
  unsigned int distance_cm = sonar.ping_cm();
  //distance_cm = (distance_cm*10);

  // Send the distance data to Blynk
  Blynk.virtualWrite(V1, distance_cm);  // Use V1 as a display widget in your Blynk app
  
  Serial.print("Stem Displacement: ");
  Serial.print(distance_cm);
  Serial.println(" mm");

  delay(1000); // Delay between measurements
}
