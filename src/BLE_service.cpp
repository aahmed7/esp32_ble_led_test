#include <Arduino.h>
#include <BLE_service.h>

/* Define our custom characteristic along with it's properties */
BLECharacteristic LED0_Characteristic(
    BLEUUID((uint16_t)0x1A00),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic LED1_Characteristic(
    BLEUUID((uint16_t)0x1A01),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic LED2_Characteristic(
    BLEUUID((uint16_t)0x1A02),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic LED3_Characteristic(
    BLEUUID((uint16_t)0x1A03),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic LED4_Characteristic(
    BLEUUID((uint16_t)0x1A04),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
BLECharacteristic LED5_Characteristic(
    BLEUUID((uint16_t)0x1A05),
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

/* This function handles the server callbacks */
bool deviceConnected = false;
class ServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
        Serial.println("Client Connected.");
    };
    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
        Serial.println("Client Connected.");
    }
};

class MyCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0)
        {
            Serial.print("New value: ");
            Serial.print(value.at(0));
            Serial.println();
            /* Write 0x30 hex byte to turn off LED. Otherwise on. */
            if (value.at(0) == '0')
            {
                if (pCharacteristic == &LED0_Characteristic)
                    digitalWrite(LED0, LOW);
                if (pCharacteristic == &LED1_Characteristic)
                    digitalWrite(LED1, LOW);
                if (pCharacteristic == &LED2_Characteristic)
                    digitalWrite(LED2, LOW);
                if (pCharacteristic == &LED3_Characteristic)
                    digitalWrite(LED3, LOW);
                if (pCharacteristic == &LED4_Characteristic)
                    digitalWrite(LED4, LOW);
                if (pCharacteristic == &LED5_Characteristic)
                    digitalWrite(LED5, LOW);
            }
            else
            {
                if (pCharacteristic == &LED0_Characteristic)
                    digitalWrite(LED0, HIGH);
                if (pCharacteristic == &LED1_Characteristic)
                    digitalWrite(LED1, HIGH);
                if (pCharacteristic == &LED2_Characteristic)
                    digitalWrite(LED2, HIGH);
                if (pCharacteristic == &LED3_Characteristic)
                    digitalWrite(LED3, HIGH);
                if (pCharacteristic == &LED4_Characteristic)
                    digitalWrite(LED4, HIGH);
                if (pCharacteristic == &LED5_Characteristic)
                    digitalWrite(LED5, HIGH);
            }
        }
    }
};

/************************************************************************
 *
 * Function:  BLE_init
 * --------------------
 *  This function initializes the BLE server.
 *
 *  returns: none
 *
 ************************************************************************/
void BLE_init()
{
    // Create and name the BLE Device
    BLEDevice::init(DEVICE_NAME);

    /* Create the BLE Server */
    BLEServer *MyServer = BLEDevice::createServer();
    MyServer->setCallbacks(new ServerCallbacks());

    /* Add a service the server */
    BLEService *customService =
        MyServer->createService(BLEUUID((uint16_t)0x1700));

    BLECharacteristicCallbacks *LED_callback = new MyCallbacks();
    /* Add LED0 characteristic to the service */
    customService->addCharacteristic(&LED0_Characteristic);
    LED0_Characteristic.setCallbacks(LED_callback);

    /* Add LED1 characteristic to the service */
    customService->addCharacteristic(&LED1_Characteristic);
    LED1_Characteristic.setCallbacks(LED_callback);

    /* Add LED2 characteristic to the service */
    customService->addCharacteristic(&LED2_Characteristic);
    LED2_Characteristic.setCallbacks(LED_callback);

    /* Add LED3 characteristic to the service */
    customService->addCharacteristic(&LED3_Characteristic);
    LED3_Characteristic.setCallbacks(LED_callback);

    /* Add LED4 characteristic to the service */
    customService->addCharacteristic(&LED4_Characteristic);
    LED4_Characteristic.setCallbacks(LED_callback);

    /* Add LED5 characteristic to the service */
    customService->addCharacteristic(&LED5_Characteristic);
    LED5_Characteristic.setCallbacks(LED_callback);

    /* Configure Advertising with the Services to be advertised */
    MyServer->getAdvertising()->addServiceUUID(serviceID);

    /* Start the service */
    customService->start();

    /* Start the Server/Advertising */
    MyServer->getAdvertising()->start();

    Serial.println("Waiting for a Client to connect...");
}
