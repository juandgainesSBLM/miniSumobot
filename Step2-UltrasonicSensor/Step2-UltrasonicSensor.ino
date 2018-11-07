#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(12, 11);  // Initialize sensor that uses digital pins 13 and 12.

int distance;

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.

    distance=distanceSensor.measureDistanceCm();
    Serial.println();
    delay(500);
}
