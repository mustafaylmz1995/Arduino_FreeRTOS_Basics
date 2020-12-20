#include <Arduino_FreeRTOS.h>
#include "semphr.h"

//#define RED     6
#define YELLOW  7
#define GREEN   8

SemaphoreHandle_t xMutex;


void setup(){

  Serial.begin(9600);
//  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  xMutex = xSemaphoreCreateMutex();

  xTaskCreate(outputTask, "Printer Task 1", 128, (void *)"Task1 ################ Task1\r\n", 1, NULL);
  xTaskCreate(outputTask, "Printer Task 2", 128, (void *)"Task2 ################ Task2\r\n", 2, NULL);

}

void outputTask(void *pvParameters){
  char *pcStringToPrint = (char *)pvParameters;
  
  while(1){
    printer(pcStringToPrint);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    vTaskDelay(2);    
  }
}

void printer(const char* pcString){

  xSemaphoreTake(xMutex, portMAX_DELAY);
  Serial.println(pcString);
  digitalWrite(YELLOW, digitalRead(YELLOW)^1);
  xSemaphoreGive(xMutex);    
  
}


void loop(){
  
}
