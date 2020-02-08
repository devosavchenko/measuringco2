#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>        //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step1-wifi
#include <ESP8266WebServer.h>   //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step2-webserver
#include <ESP8266SSDP.h>        //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step3-ssdp
#include <FS.h>                 //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step4-fswebserver
//                    ПЕРЕДАЧА ДАННЫХ НА WEB СТРАНИЦУ. Видео с уроком http://esp8266-arduinoide.ru/step5-datapages/
//                    ПЕРЕДАЧА ДАННЫХ С WEB СТРАНИЦЫ.  Видео с уроком http://esp8266-arduinoide.ru/step6-datasend/
#include <ArduinoJson.h>        //Установить из менеджера библиотек. https://arduinojson.org/
//                    ЗАПИСЬ И ЧТЕНИЕ ПАРАМЕТРОВ КОНФИГУРАЦИИ В ФАЙЛ. Видео с уроком http://esp8266-arduinoide.ru/step7-fileconfig/
#include <ESP8266HTTPUpdateServer.h>  //Содержится в пакете.  Видео с уроком http://esp8266-arduinoide.ru/step8-timeupdate/
#include <DNSServer.h> //Содержится в пакете.  // Для работы символьных имен в режиме AP отвечает на любой запрос например: 1.ru
#include <ESP8266mDNS.h>        // Include the mDNS library

#include "MHZ19.h"

#include "json.hpp"

typedef struct
{
   int16_t unlimited;
   int16_t limited;
}CO2Val_t;

// Объект для обнавления с web страницы
extern ESP8266HTTPUpdateServer httpUpdater;

// Web интерфейс для устройства
extern ESP8266WebServer HTTP;

extern CO2Val_t CO2;
extern float temperature;
extern MHZ19 myMHZ19;
int32_t InitMHZ19();
int32_t GetCO2Value(CO2Val_t *pCO2Val, float *pTemperature);


String GetTime();
String GetDate();

// Для файловой системы
extern File fsUploadFile;

// Для работы символьных имен в режиме AP
extern DNSServer dnsServer;

extern String configSetup;
extern String configJson;
const int port = 80;
extern ESP8266WebServer HTTP;
