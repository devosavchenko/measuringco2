#include "set.hpp"

// Здесь код зависит от версии arduino IDE.
// Если не компелируется раскомментируйте следующую строку
//HTTP = new ESP8266WebServer (port);
ESP8266WebServer HTTP(port);  // и закомментируйте эту


String configSetup = "{}";
String configJson = "{}";

CO2Val_t CO2;
float temperature;

void GRAF_init(void);
void HTTP_init(void);
void SSDP_init(void);
void Time_init(void);
void WIFIinit(void);
void FS_init(void);

void setup() {

  int32_t err;
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  Serial.begin(115200);
  delay(5);
  Serial.println("");

  //Запускаем файловую систему
  Serial.println("Start FS");
  FS_init();

  Serial.println("Read Config File");
  configSetup = readFile("config.json", 4096);
  jsonWrite(configJson, "SSDP", jsonRead(configSetup, "SSDP"));
  Serial.println(configSetup);

  Serial.println("Start WIFI");
  WIFIinit();

  Serial.println("Start Time");
  // Получаем время из сети
  Time_init();

  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start SSDP");
  SSDP_init();

  // Настраиваем датчик СО2
  Serial.println("Initialize MHZ19");
  err = InitMHZ19();
  if(err)
  {
    Serial.println("FAILED, REBOOTING ;( ");
    delay(500);
    ESP.restart();
  }
  else
  {
    Serial.println("SUCCESS");
  }

  // Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();
  GRAF_init();

  Serial.println("Initialise finished");
}

void loop()
{
  if (GetCO2Value(&CO2, &temperature))
  {
    // err was detected, reinit MHZ
    myMHZ19.recoveryReset();
    delay(30000);
    // restart ESP
    ESP.restart();
    delay(30000);
  }
  HTTP.handleClient();
  delay(1);

  dnsServer.processNextRequest();

  // Allow MDNS processing
  MDNS.update();
}
