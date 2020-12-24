#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <string.h>

#define DEVICE_NAME "ESP32_LED_HUB"

#define LED0 16
#define LED1 17
#define LED2 5
#define LED3 18
#define LED4 19
#define LED5 21

/* Define the UUID for our Custom Service */
#define serviceID BLEUUID((uint16_t)0x1700)

/* Initialize BLE function. */
void BLE_init();

#endif