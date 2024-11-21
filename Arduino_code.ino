// const int trigPin = 5;
// const int echoPin = 18;

// //define sound speed in cm/uS
// #define SOUND_SPEED 0.034
// #define CM_TO_INCH 0.393701

// long duration;
// float distanceCm;
// float distanceInch;

// void setup() {
//   Serial.begin(115200); // Starts the serial communication
//   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//   pinMode(echoPin, INPUT); // Sets the echoPin as an Input
// }

// void loop() {
//   // Clears the trigPin
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   // Sets the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
  
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   duration = pulseIn(echoPin, HIGH);
  
//   // Calculate the distance
//   distanceCm = duration * SOUND_SPEED/2;
  
//   // Convert to inches
//   distanceInch = distanceCm * CM_TO_INCH;
  
//   // Prints the distance in the Serial Monitor
//   Serial.print("Distance (cm): ");
//   Serial.println(distan-ceCm);
//   Serial.print("Distance (inch): ");
//   Serial.println(distanceInch);
  
//   delay(1000);
// }

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "Neelesh";
const char* password = "19-12-1973";

// Define pins and constants
const int trigPin = 5;
const int echoPin = 18;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

// Variables for distance
long duration;
float distanceCm;
float distanceInch;

// Create AsyncWebServer object
AsyncWebServer server(80);

// Function to measure distance
void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED / 2;
  Serial.println(distanceCm);
  
}

// Function to handle POST requests
void handlePostRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  StaticJsonDocument<200> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, data, len);

  if (error) {
    Serial.print("JSON parsing failed: ");
    Serial.println(error.c_str());
    request->send(400, "application/json", "{\"message\":\"Invalid JSON\"}");
    return;
  }

  // Measure distance
  measureDistance();

  // Prepare response with distance
  StaticJsonDocument<200> jsonResponse;
  jsonResponse["distance_cm"] = distanceCm;
  // jsonResponse["distance_inch"] = distanceInch;
  jsonResponse["message"] = "Data received successfully";

  String responseMessage;
  serializeJson(jsonResponse, responseMessage);
  request->send(200, "application/json", responseMessage);
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Set pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("Connected with local IP: ");
  String localIp = WiFi.localIP().toString();
  Serial.println(WiFi.localIP());
  Serial.println();

  // Define server route for POST requests
  server.on(
    "/",
    HTTP_GET,
    [](AsyncWebServerRequest *request) {}, // Empty onRequest handler
    nullptr,                              // No onUpload handler
    handlePostRequest                     // onBody handler
  );

  // Start server
  server.begin();
}

void loop() {
  // Main loop does nothing as AsyncWebServer handles everything
  Serial.println(distanceCm);
  delay(10000);
}


// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <ArduinoJson.h>

// // WiFi credentials
// const char* ssid = "Aditya Goyal";
// const char* password = "1234567890";

// // Define pins and constants
// const int trigPin = 5;
// const int echoPin = 18;

// #define SOUND_SPEED 0.034
// #define CM_TO_INCH 0.393701

// // Variables for distance
// long duration;
// float distanceCm;
// float distanceInch;

// // Create AsyncWebServer object
// AsyncWebServer server(80);

// // Function to measure distance
// void measureDistance() {
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);

//   duration = pulseIn(echoPin, HIGH);
//   distanceCm = duration * SOUND_SPEED / 2;
//   distanceInch = distanceCm * CM_TO_INCH;
// }

// // Function to handle POST requests
// void handlePostRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
//   StaticJsonDocument<200> jsonDoc;
//   DeserializationError error = deserializeJson(jsonDoc, data, len);

//   if (error) {
//     Serial.print("JSON parsing failed: ");
//     Serial.println(error.c_str());
//     request->send(400, "application/json", "{\"message\":\"Invalid JSON\"}");
//     return;
//   }

//   String receivedData = jsonDoc["data"];
//   String receivedMessage = jsonDoc["message"];

//   Serial.println("Data received:");
//   Serial.println("data: " + receivedData);
//   Serial.println("message: " + receivedMessage);

//   String responseMessage = "{\"message\":\"Data received successfully\"}";
//   request->send(200, "application/json", responseMessage);
// }

// void setup() {
//   // Start Serial communication
//   Serial.begin(115200);

//   // Set pins
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");

//   // Define server routes
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//     measureDistance(); // Measure distance before sending response

//     StaticJsonDocument<200> jsonResponse;
//     jsonResponse["distance_cm"] = distanceCm;
//     jsonResponse["distance_inch"] = distanceInch;

//     String response;
//     serializeJson(jsonResponse, response);
//     request->send(200, "application/json", response);
//   });

//   server.on(
//     "/",
//     HTTP_POST,
//     [](AsyncWebServerRequest *request) {}, // Empty onRequest handler
//     nullptr,                              // No onUpload handler
//     handlePostRequest                     // onBody handler
//   );

//   // Start server
//   server.begin();
// }

// void loop() {
//   // Main loop does nothing as AsyncWebServer handles everything
// }
