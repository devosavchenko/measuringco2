#include "set.hpp"

#include <Wire.h>
#include <SoftwareSerial.h> //  <--- Remove if using HardwareSerial / ESP32

// D5
#define RX_PIN 14
// D6
#define TX_PIN 12

#define BAUDRATE 9600 // Native to the sensor (do not change)

MHZ19 myMHZ19;
SoftwareSerial mySerial(RX_PIN, TX_PIN);

unsigned long getDataTimer = 0;


int32_t InitMHZ19()
{
  int32_t repeat = 16;

  mySerial.begin(BAUDRATE);
  myMHZ19.begin(mySerial); // *Imporant, Pass your Stream reference here

  while ( (RESULT_OK != myMHZ19.errorCode) )
  {
    delay(1000);
    myMHZ19.begin(mySerial); // *Imporant, Pass your Stream reference here

    if (!repeat--)
    {
      Serial.print("Response Code: ");
      Serial.println(myMHZ19.errorCode);          // Get the Error Code value
      return 1;
    }
  }

  myMHZ19.autoCalibration(false); // Turn ABC OFF

  /* use to show communication between MHZ19 and  Device
  void printCommunication(bool isDec = true, bool isPrintComm = true);*/
  myMHZ19.printCommunication(false, true);

  return 0;
}

int32_t GetCO2Value(CO2Val_t *pCO2Val, float *pTemperature = nullptr)
{
  static int32_t LedState = HIGH;
  int32_t retVal = 0;

  if (millis() - getDataTimer >= 30000)
  {
    /* get sensor readings as signed integer */
    int16_t tmpVal = myMHZ19.getCO2(true, true);
    /* In testing - let me know if it works for you! */
    float temperature = myMHZ19.getTemperature(true, false);

    if(myMHZ19.errorCode != RESULT_OK)              // RESULT_OK is an alis for 1. Either can be used to confirm the response was OK.
    {
        Serial.println("/nFailed to recieve CO2 value - Error");
        Serial.print("Response Code: ");
        Serial.println(myMHZ19.errorCode);          // Get the Error Code value

        retVal = myMHZ19.errorCode;
    }else
    {
        pCO2Val->unlimited = tmpVal;
        if(pTemperature)
        {
            *pTemperature = temperature;
        }

        // digitalWrite(LED_BUILTIN, LedState = (LedState == HIGH)?(LOW):(HIGH));

        if (tmpVal > 1000)
        {
          digitalWrite(LED_BUILTIN, LedState = LOW);
        }
        else
        {
          digitalWrite(LED_BUILTIN, LedState = HIGH);
        }
    }

    // Serial.print("CO2 PPM Unlim: ");
    Serial.print(GetTime());
    Serial.print(", ");
    Serial.print(GetDate());
    Serial.print("  Unlimited CO2 = ");
    Serial.print(/*CO2.unlimited*/ tmpVal);

    Serial.print(", Temperature (C): ");
    Serial.print(temperature); // (request decimal value, new value request not needed !see request curbing)
    Serial.println(".");

    getDataTimer = millis(); // Update interval
  }

  return retVal;
}
