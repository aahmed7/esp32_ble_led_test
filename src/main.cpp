#include <Arduino.h>
#include <BLE_service.h>

void setup()
{
    Serial.begin(9600);
    Serial.println("Serial Initialized.");

    /* Enable BLE communication */
    BLE_init();

    /* Set the pinmode for LED pins. */
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);

    /* Turn off all LEDs at the start. */
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
}

void loop()
{
}