// библиотека для работы I²C
// #include <Library/Wire.h>
// библиотека для работы с модулями IMU
#include <barometer.h>
// создаём объект для работы с барометром

#include "application.h"
#include "math.h"



Barometer barometer;

float pressure;
float temperature;


void setup()
{


  // открываем последовательный порт
  Serial.begin(9600);

  // выводим сообщение о начале инициализации
  Serial.println("Begin init...");
  // инициализация барометра
  barometer.begin();
  // выводим сообщение об удачной инициализации
  Serial.println("Init completed");



  Particle.variable("varAlt",(double)pressure);
  Particle.variable("varTemp",(double)temperature);

}

void loop()
{
  char varString[16];


  // создаём переменную и присваиваем ей значения абсолютного давления
  float pressure = barometer.readPressureMillibars();
  // создаём переменную и присваиваем ей значения высоты над уровнем море
  float altitude = barometer.pressureToAltitudeMeters(pressure);
  // создаём переменную и присваиваем ей температуру окружающей среды
  float temperature = barometer.readTemperatureC();

  sprintf(varString, "p: %f    t: %f", pressure, temperature);
  Particle.publish("Pressure", varString, PRIVATE);

  // Вывод данных в Serial порт
  Serial.print("p: ");
  Serial.print(pressure);
  Serial.print(" mbar \t");
  Serial.print("h: ");
  Serial.print(altitude);
  Serial.print(" m \t");
  Serial.print("t: ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(30000);
}
