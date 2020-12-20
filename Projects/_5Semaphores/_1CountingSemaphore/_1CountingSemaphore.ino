#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED     6
#define YELLOW  7
#define GREEN   8

SemaphoreHandle_t xCountingSem;


void setup(){

  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  xCountingSem = xSemaphoreCreateCounting(1, 0);

  xTaskCreate(redLedController, "Red LED Task", 128, NULL, 1, NULL);
  xTaskCreate(yellowLedController, "Yellow LED Task", 128, NULL, 1, NULL);
  xTaskCreate(greenLedController, "Green LED Task", 128, NULL, 1, NULL);
   
  xSemaphoreGive(xCountingSem);
}

void redLedController(void *pvParameters){
  
  while(1){
    xSemaphoreTake(xCountingSem, portMAX_DELAY);
    Serial.println("This is RED task");
    digitalWrite(RED, digitalRead(RED)^1);
    xSemaphoreGive(xCountingSem);
    vTaskDelay(1);    
  }
}

void yellowLedController(void *pvParameters){

  while(1){
    xSemaphoreTake(xCountingSem, portMAX_DELAY);
    Serial.println("This is YELLOW task");
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    xSemaphoreGive(xCountingSem);    
    vTaskDelay(1);
  }
}


void greenLedController(void *pvParameters){

  while(1){
    xSemaphoreTake(xCountingSem, portMAX_DELAY);
    Serial.println("This is GREEN task");
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    xSemaphoreGive(xCountingSem);    
    vTaskDelay(1);
  }
}

void loop(){
  
}
