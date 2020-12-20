#include <Arduino_FreeRTOS.h>

#define RED     6
#define YELLOW  7
#define GREEN   8

TaskHandle_t yellow_Handle, red_Handle, green_Handle;

typedef int TaskProfiler;
TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler GreenLEDProfiler;

const TickType_t _500ms = pdMS_TO_TICKS(500);

uint32_t suspend_monitor;
uint32_t resume_monitor;
bool _suspended = false;

void setup(){
  Serial.begin(9600);
  xTaskCreate(yellowLEDControllerTask, "YELLOW LED Task", 128, NULL, 1, &yellow_Handle);
  xTaskCreate(redLEDControllerTask, "RED LED Task", 128, NULL, 1, &red_Handle);
  xTaskCreate(greenLEDControllerTask, "GREEN LED Task", 128, NULL, 1, &green_Handle);

}

void yellowLEDControllerTask(void *pvParameter){
  pinMode(YELLOW, OUTPUT);
  while(1){
    
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.println(); 
    Serial.print("Yellow Run Time:");
    Serial.println(YellowLEDProfiler);
    vTaskDelay(10);

    if(_suspended){
      resume_monitor++;
      
      if(resume_monitor>=10){
        vTaskResume(green_Handle);
        resume_monitor = 0;
        _suspended = false;
      }
    }
    
  }
}

void redLEDControllerTask(void *pvParameter){
  pinMode(RED, OUTPUT);
  while(1){
    digitalWrite(RED, digitalRead(RED)^1);
    RedLEDProfiler++;
    Serial.print("Red Run Time:");
    Serial.println(RedLEDProfiler);
    vTaskDelay(_500ms);
  }
}

void greenLEDControllerTask(void *pvParameter){
  pinMode(GREEN, OUTPUT);
  while(1){
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    GreenLEDProfiler++;
    Serial.print("Green Run Time:");
    Serial.println(GreenLEDProfiler); 
    
    suspend_monitor++;
    if(suspend_monitor >=20){
      _suspended = true;
      suspend_monitor = 0;
      vTaskSuspend(green_Handle);
    }

    vTaskDelay(10);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
