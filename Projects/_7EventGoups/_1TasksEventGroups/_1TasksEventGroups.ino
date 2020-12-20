#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

#define   RED     6
#define   YELLOW  7
#define   GREEN   8


EventGroupHandle_t  xEventGroup;
#define TASK1_BIT (1UL << 0UL)
#define TASK2_BIT (1UL << 1UL)
#define TASK3_BIT (1UL << 2UL)

const TickType_t xDelay50ms = pdMS_TO_TICKS(50);

void setup(){
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  xEventGroup = xEventGroupCreate();

  xTaskCreate(InputTask1, "InputTask1", 128, NULL, 1, NULL);
  xTaskCreate(InputTask2, "InputTask2", 128, NULL, 1, NULL);
  xTaskCreate(InputTask3, "InputTask3", 128, NULL, 1, NULL);

  xTaskCreate(OutputTask, "OutputTask", 128, NULL, 1, NULL);

}

void InputTask1(void *pvParameters){

  while(1){
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    vTaskDelay(xDelay50ms);

  }
}

void InputTask2(void *pvParameters){

  while(1){
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    vTaskDelay(xDelay50ms);
  }
}

void InputTask3(void *pvParameters){

  while(1){
    xEventGroupSetBits(xEventGroup, TASK3_BIT);
    vTaskDelay(xDelay50ms);
  }
}


void OutputTask(void *pvParameters){
  
  const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT);
  EventBits_t xEventGroupValue;
  
  while(1){
   xEventGroupValue = xEventGroupWaitBits(xEventGroup, 
                                           xBitsToWaitFor,
                                           pdTRUE,
                                           pdTRUE,
                                           portMAX_DELAY
                                           );

    if((xEventGroupValue & TASK1_BIT) != 0){
      digitalWrite(RED, digitalRead(RED)^1);                                           
    }
    
    if((xEventGroupValue & TASK2_BIT) != 0){
      digitalWrite(YELLOW, digitalRead(YELLOW)^1);                                           
    }

    if((xEventGroupValue & TASK3_BIT) != 0){
      digitalWrite(GREEN, digitalRead(GREEN)^1);                                           
    }
  }
}


void loop(){
  
}
