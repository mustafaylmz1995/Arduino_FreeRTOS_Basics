#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;

TaskProfiler redLEDProfiler;
TaskProfiler yellowLEDProfiler;
TaskProfiler greenLEDProfiler;

const uint16_t *redLed    = (uint16_t *)RED;
const uint16_t *yellowLed = (uint16_t *)YELLOW;
const uint16_t *greenLed  = (uint16_t *)GREEN;


void setup(){
  Serial.begin(9600);
  xTaskCreate(LEDControllerTask,
              "RED LED Task",
              100,
              (void *)redLed,
              1,
              NULL
              );
  xTaskCreate(LEDControllerTask,
              "YELLOW LED Task",
              100,
              (void *)yellowLed,
              1,
              NULL
              );
  xTaskCreate(LEDControllerTask,
              "GREEN LED Task",
              100,
              (void *)greenLed,
              1,
              NULL
              );  
}

void LEDControllerTask(void *pvParameter){
  
  pinMode((uint8_t)pvParameter, OUTPUT);
  while(1){
    digitalWrite((uint8_t)pvParameter,digitalRead((uint8_t)pvParameter)^1);
    delay(100);
  }
}

void loop(){
  
}
