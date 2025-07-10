#include <WiFi.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <NewPing.h>

// WiFi credentials
const char *ssid = "Airtel_Ram-G";
const char *password = "Riya0798@123";

// Define pins and constants
const int trigPin = 5;
const int echoPin = 18;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define TIMEOUT 3000
#define MAX_DISTANCE 400

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

// Variables for distance
long duration;
float distanceCm;
float distanceInch;
float dis2;

// Create AsyncWebServer object
AsyncWebServer server(80);

// Function to measure distance
void measureDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, TIMEOUT);

    // if (duration == 0) {
    //   // Timeout occurred
    //   distanceCm = -1; // Indicate an invalid reading
    // } else {
    distanceCm = duration * SOUND_SPEED / 2;
    distanceCm = round(distanceCm * 100.0) / 100.0;

    // }
    Serial.print("Measured Distance (cm): ");
    Serial.println(distanceCm, 2);

    Serial.print("arjun:");
    // Serial.println(distanceCm);
}

// Function to handle POST requests
void handlePostRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    StaticJsonDocument<200> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, data, len);

    if (error)
    {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        request->send(400, "application/json", "{\"message\":\"Invalid JSON\"}");
        return;
    }

    String receivedData = jsonDoc["data"];
    String receivedMessage = jsonDoc["message"];

    Serial.println("Data received:");
    Serial.println("data: " + receivedData);
    Serial.println("message: " + receivedMessage);

    String responseMessage = "{\"message\":\"Data received successfully\"}";
    request->send(200, "application/json", responseMessage);
}

// Function to handle GET requests
void handleGetRequest(AsyncWebServerRequest *request)
{
    // Measure distance
    measureDistance();

    // Serial.println("get req");
    Serial.println(dis2);
    // Prepare response
    StaticJsonDocument<200> jsonResponse;
    jsonResponse["dis"] = dis2 + 1.3;
    jsonResponse["message"] = "Distance measured successfully";

    String responseMessage;
    serializeJson(jsonResponse, responseMessage);
    request->send(200, "application/json", responseMessage);
}

void setup()
{
    // Start Serial communication
    Serial.begin(115200);

    // Set pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());
    Serial.println("Connected to WiFi");

    // Define server route for GET requests
    server.on("/", HTTP_GET, handleGetRequest);

    // Start server
    server.begin();
}

void loop()
{
    // Main loop does nothing as AsyncWebServer handles everything
    // Serial.println("helloo");
    // delay(4000);
    // measureDistance();
    delay(50);
    unsigned int time = sonar.ping();
    dis2 = (float)time / US_ROUNDTRIP_CM;
    dis2 = round(dis2 * 100.0) / 100.0;
    delay(1000);9
    Serial.print("Distance (cm): ");
    Serial.println(dis2, 2);
    // Serial.println(dis2,2);
}
