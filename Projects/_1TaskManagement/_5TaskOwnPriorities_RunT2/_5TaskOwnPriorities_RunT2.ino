#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;

TaskProfiler redLEDProfiler;
TaskProfiler yellowLEDProfiler;
TaskProfiler greenLEDProfiler;

TaskHandle_t red_Handle, yellow_Handle, green_Handle;


void setup(){
  Serial.begin(9600);
  xTaskCreate(yellowLEDControllerTask, "YELLOW LED Task", 100, NULL, 1, &yellow_Handle);
  xTaskCreate(redLEDControllerTask, "RED LED Task", 100, NULL, 1, &red_Handle);
  xTaskCreate(greenLEDControllerTask, "GREEN LED Task", 100, NULL, 1, &green_Handle);

}

void yellowLEDControllerTask(void *pvParameter){
  pinMode(YELLOW, OUTPUT);
  while(1){
    yellowLEDProfiler++;
    Serial.print("Yellow Task Runtime :");
    Serial.println(yellowLEDProfiler);
    //digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskPrioritySet(NULL, 2);
    delay(300);  
  }
}
void redLEDControllerTask(void *pvParameter){
  pinMode(RED, OUTPUT);
  while(1){
    redLEDProfiler++;
    Serial.print("Red Task Runtime :");
    Serial.println(redLEDProfiler);
    //digitalWrite(RED,digitalRead(RED)^1);
    //vTaskPrioritySet(red_Handle, 1);
    delay(300);  
  }
}
void greenLEDControllerTask(void *pvParameter){
  pinMode(GREEN, OUTPUT);
  while(1){
    greenLEDProfiler++;
    Serial.print("Green Task Runtime :");
    Serial.println(greenLEDProfiler);
    //digitalWrite(GREEN,digitalRead(GREEN)^1);
    //vTaskPrioritySet(green_Handle, 1);
    delay(300);  
  }
}

void loop(){
  
}
