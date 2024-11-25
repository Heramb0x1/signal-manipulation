#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <ESP8266WiFi.h> 

// Define custom SDA and SCL pins
#define SDA_PIN D2 
#define SCL_PIN D1 

// WiFi credentials
const char* ssid = "*****";         // Replace with your WiFi SSID
const char* password = "*****";     // Replace with your WiFi Password

// Server details
const char* host = "192.168.ABC.XYZ";    // Python server IP
const int port = 23456;                  // Mac port number

// VL53L0X setup
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200); // Start serial communication for debugging
  delay(500);
  // Initialize I2C with custom SDA and SCL pins
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize VL53L0X
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X. Check your wiring!");
    delay(500);
    while (1);
  }
  Serial.println("VL53L0X initialized.");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Get distance data from VL53L0X
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  // Check if distance is valid
  if (measure.RangeStatus != 4) { // 4 means "out of range"
    float distance = measure.RangeMilliMeter / 10.0; // mm to cm

    // Send data to Python server
    sendDataToServer(distance);
  } else {
    Serial.println("Out of range");
  }

  delay(1); // 1 ms delay (1kHz)
}

void sendDataToServer(float distance) {
  // Connect to the Python server
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("Connection to server failed!");
    return;
  }

  // Send distance data
  client.print(String(distance));
  Serial.println("Sent data: " + String(distance));

  // Close the connection
  client.stop();
}
