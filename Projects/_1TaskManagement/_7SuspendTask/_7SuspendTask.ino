#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

TaskHandle_t yellow_Handle, red_Handle, green_Handle;

typedef int TaskProfiler;
TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

uint32_t suspend_monitor;

void setup(){
  Serial.begin(9600);
  xTaskCreate(yellowLEDControllerTask, "YELLOW LED Task", 128, NULL, 1, &yellow_Handle);
  xTaskCreate(redLEDControllerTask, "RED LED Task", 128, NULL, 1, &red_Handle);
  xTaskCreate(greenLEDControllerTask, "GREEN LED Task", 128, NULL, 1, &green_Handle);

}

void yellowLEDControllerTask(void *pvParameter){
  pinMode(YELLOW, OUTPUT);
  while(1){
    suspend_monitor++;
    //digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.print("Yellow Run Time:");
    Serial.println(YellowLEDProfiler);
    vTaskDelay(100);
  }
}

void redLEDControllerTask(void *pvParameter){
  pinMode(RED, OUTPUT);
  while(1){
    //digitalWrite(RED, digitalRead(RED)^1);
    RedLEDProfiler++;
    Serial.print("Red Run Time:");
    Serial.println(RedLEDProfiler);
    vTaskDelay(100);
  }
}

void greenLEDControllerTask(void *pvParameter){
  pinMode(GREEN, OUTPUT);
  while(1){
    //digitalWrite(GREEN, digitalRead(GREEN)^1);
    GreenLEDProfiler++;
    Serial.print("Green Run Time:");
    Serial.println(GreenLEDProfiler);  
    
    if(suspend_monitor >=5){
      vTaskSuspend(NULL);
    }

    vTaskDelay(100);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
