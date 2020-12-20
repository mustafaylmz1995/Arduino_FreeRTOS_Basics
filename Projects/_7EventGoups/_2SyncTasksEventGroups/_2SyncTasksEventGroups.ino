#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define   RED     6
#define   YELLOW  7
#define   GREEN   8

#define TASKA_BIT (1UL << 0UL)
#define TASKB_BIT (1UL << 1UL)
#define TASKC_BIT (1UL << 2UL)

EventGroupHandle_t  xEventGroup;

const EventBits_t allSyncBits = (TASKA_BIT | TASKB_BIT | TASKC_BIT);

const TickType_t xDelay50ms = pdMS_TO_TICKS(50);
const TickType_t xDelay70ms = pdMS_TO_TICKS(70);
const TickType_t xDelay120ms = pdMS_TO_TICKS(120);

void setup(){

  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  xEventGroup = xEventGroupCreate();

  xTaskCreate(TaskA, "TaskA", 128, NULL, 1, NULL);
  xTaskCreate(TaskB, "TaskB", 128, NULL, 1, NULL);
  xTaskCreate(TaskC, "TaskC", 128, NULL, 1, NULL);

}

void TaskA(void *pvParameters){

  EventBits_t uxReturn;
  
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKA_BIT, allSyncBits, portMAX_DELAY);

    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(RED, digitalRead(RED)^1);
      vTaskDelay(xDelay120ms);                                           
    }    
  }
}

void TaskB(void *pvParameters){
  EventBits_t uxReturn;
  
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKB_BIT, allSyncBits, portMAX_DELAY);

    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(YELLOW, digitalRead(YELLOW)^1);
      vTaskDelay(xDelay70ms);                                           
    }    
  }
}

void TaskC(void *pvParameters){
  EventBits_t uxReturn;
  
  while(1){
    uxReturn = xEventGroupSync(xEventGroup, TASKC_BIT, allSyncBits, portMAX_DELAY);

    if((uxReturn & allSyncBits) == allSyncBits){
      digitalWrite(GREEN, digitalRead(GREEN)^1);
      vTaskDelay(xDelay50ms);                                           
    }    
  }
}



void loop(){
  
}
