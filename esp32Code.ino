
#include "connect_to_wifi.h"
#include "firebase_setup.h"


void setup() {

  Serial.begin(115200);
  ConnectToWiFi();
  setupOutputPins();
  connectToFirebase();
  streamData();
}

void loop() {
}
