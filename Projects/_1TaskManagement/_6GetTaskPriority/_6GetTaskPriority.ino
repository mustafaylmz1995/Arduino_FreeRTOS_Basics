#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

typedef int TaskProfiler;

TaskProfiler redLEDProfiler;
TaskProfiler yellowLEDProfiler;
TaskProfiler greenLEDProfiler;

TaskHandle_t red_Handle, yellow_Handle, green_Handle;

int yellowTaskPrio, greenTaskPrio, redTaskPrio;

void setup(){
  Serial.begin(9600);
  xTaskCreate(yellowLEDControllerTask, "YELLOW LED Task", 100, NULL, 1, &yellow_Handle);
  xTaskCreate(redLEDControllerTask, "RED LED Task", 100, NULL, 1, &red_Handle);
  xTaskCreate(greenLEDControllerTask, "GREEN LED Task", 100, NULL, 1, &green_Handle);

}

void yellowLEDControllerTask(void *pvParameter){
  pinMode(YELLOW, OUTPUT);
  while(1){
    //yellowLEDProfiler++;
    yellowTaskPrio = uxTaskPriorityGet(yellow_Handle);
    
    Serial.print("Yellow Task Priority :");
    Serial.println(yellowTaskPrio);
    delay(300);  
  }
}
void redLEDControllerTask(void *pvParameter){
  pinMode(RED, OUTPUT);
  while(1){
//    redLEDProfiler++;
    redTaskPrio = uxTaskPriorityGet(red_Handle);
    Serial.print("Red Task Priority :");
    Serial.println(redTaskPrio);
    delay(300);  
  }
}
void greenLEDControllerTask(void *pvParameter){
  pinMode(GREEN, OUTPUT);
  while(1){
//    greenLEDProfiler++;
    greenTaskPrio = uxTaskPriorityGet(green_Handle);
    Serial.print("Green Task Priority :");
    Serial.println(greenTaskPrio);
    delay(300);  
  }
}

void loop(){
  
}
