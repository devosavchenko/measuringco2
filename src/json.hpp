#pragma once

// ------------- Чтение значения json
String jsonRead(String &json, String name);

// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name);

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume);

// ------------- Запись значения json int
String jsonWrite(String &json, String name, int volume);

void saveConfig();

// ------------- Чтение файла в строку
String readFile(String fileName, size_t len);

// ------------- Запись строки в файл
String writeFile(String fileName, String strings);

// Перегрузка функций
// ------------- Создание данных для графика
template <typename T>
String graf(T datas)
{
  String root = "{}"; // Формировать строку для отправки в браузер json формат
  // {"data":[1]}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject &json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray &data = json.createNestedArray("data");
  data.add(datas);
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}

template <typename T>
String grafTempl(T datas)
{
  String root = "{}"; // Формировать строку для отправки в браузер json формат
  // {"data":[1]}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject &json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray &data = json.createNestedArray("temperature");
  data.add(datas);
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}

// ------------- Создание данных для графика
String graf(int datas, int datas1);
// ------------- Создание данных для графика
String graf(int datas, int datas1, int datas2);
