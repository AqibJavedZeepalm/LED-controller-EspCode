#ifndef FIREBASE_SETUP_H
#define FIREBASE_SETUP_H

#include <Firebase_ESP_Client.h>
#include <Arduino.h>
enum Color { UNDEF,
             RED,
             BLUE,
             WHITE };

void setupOutputPins();
void connectToFirebase();
void streamData();
void handleLEDColor(Color clr);
void assignColor(String clr);
#endif