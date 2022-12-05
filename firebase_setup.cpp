#include "firebase_setup.h"
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>
// firebase secrets
#define FIREBASE_HOST "add database url here"  
#define FIREBASE_AUTH "add auth api here"

#define USER_EMAIL "add email here"
#define USER_PASSWORD "add password"


//variables
FirebaseData stream;
FirebaseAuth auth;
FirebaseConfig config;


int redPin = 32;
int greenPin = 33;
int bluePin = 25;
Color color = RED;
void setupOutputPins() {
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}
void streamCallback(FirebaseStream data) {
  printResult(data);  
  Serial.println();
  String colorFromDb = data.to<String>();
  assignColor(colorFromDb);
  handleLEDColor(color);
}

void streamTimeoutCallback(bool timeout) {
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

  if (!stream.httpConnected())
    Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}


void connectToFirebase() {
  config.api_key = FIREBASE_AUTH;
  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  /* Assign the RTDB URL (required) */
  config.database_url = FIREBASE_HOST;
  Firebase.begin(&config, &auth);
}

void streamData() {

  if (!Firebase.RTDB.beginStream(&stream, "/color"))
    Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.RTDB.setStreamCallback(&stream, streamCallback, streamTimeoutCallback);
}

void handleLEDColor(Color clr) {
  switch (clr) {
    case RED:
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      break;
    case WHITE:
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(bluePin, LOW);
      break;
    case BLUE:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, LOW);
      break;
    default:
      digitalWrite(redPin, HIGH);
      digitalWrite(greenPin, HIGH);
      digitalWrite(bluePin, HIGH);
      break;
  }
}

void assignColor(String clr) {
  if (clr == "red") {
    color = RED;
  } else if (clr == "white") {
    color = WHITE;
  } else {
    color = BLUE;
  }
}
