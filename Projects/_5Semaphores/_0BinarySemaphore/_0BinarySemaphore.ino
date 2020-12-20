#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;
TaskProfiler RedTaskProfiler;
TaskProfiler YellowTaskProfiler;
TaskProfiler GreenTaskProfiler;

SemaphoreHandle_t xBinarySem;

void setup(){

  Serial.begin(9600);
  
  xBinarySem = xSemaphoreCreateBinary();

  xTaskCreate(redLedController, "Red LED Task", 128, NULL, 1, NULL);
  xTaskCreate(yellowLedController, "Yellow LED Task", 128, NULL, 1, NULL);
  xTaskCreate(greenLedController, "Green LED Task", 128, NULL, 1, NULL);
  
}

void redLedController(void *pvParameters){

  pinMode(RED, OUTPUT);
  xSemaphoreGive(xBinarySem);
  
  while(1){
    xSemaphoreTake(xBinarySem, portMAX_DELAY);
    Serial.println("This is RED task");
    xSemaphoreGive(xBinarySem);
    vTaskDelay(1);
    digitalWrite(RED, digitalRead(RED)^1);    
  }
}

void yellowLedController(void *pvParameters){

  pinMode(YELLOW, OUTPUT);
  
  while(1){
    xSemaphoreTake(xBinarySem, portMAX_DELAY);
    Serial.println("This is YELLOW task");
    xSemaphoreGive(xBinarySem);    
    vTaskDelay(1);
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
  }
}


void greenLedController(void *pvParameters){

  pinMode(GREEN, OUTPUT);

  while(1){
    xSemaphoreTake(xBinarySem, portMAX_DELAY);
    Serial.println("This is GREEN task");
    xSemaphoreGive(xBinarySem);    
    vTaskDelay(1);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
  }
}

void loop(){
  
}
