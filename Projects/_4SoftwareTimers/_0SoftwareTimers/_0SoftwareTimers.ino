#include <Arduino_FreeRTOS.h>
#include <timers.h>

#define ONE_SHOT_TIMER_PERIOD     (pdMS_TO_TICKS(500))
#define AUTO_RELOAD_TIMER_PERIOD  (pdMS_TO_TICKS(300))


TimerHandle_t xTimer1, xTimer2;

BaseType_t xTimer1Started, xTimer2Started;


void setup(){
  Serial.begin(9600);
  
  xTimer1 = xTimerCreate("One Shot",
                          ONE_SHOT_TIMER_PERIOD, 
                          pdFALSE, //one-shot
                          0,  //timerID
                          prvOneShotTimerCallback
                          ); 

  xTimer2 = xTimerCreate("Auto Reload",
                          AUTO_RELOAD_TIMER_PERIOD, 
                          pdTRUE, //auto-reload
                          0,  //timerID
                          prvAutoReloadCallback
                          ); 
  if( (xTimer1 != NULL) && (xTimer2 != NULL) ){

    xTimer1Started = xTimerStart(xTimer1, 0);
    xTimer2Started = xTimerStart(xTimer2, 0);
    
  }

  while( (xTimer1Started != pdPASS) && (xTimer2Started != pdPASS) ){
    //do nothing
  }

}

void prvOneShotTimerCallback(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  xTimeNow = xTaskGetTickCount();

  Serial.print("One Shot Timer Callback Execution : ");
  Serial.println(xTimeNow);


}

void prvAutoReloadCallback(TimerHandle_t xTimer){
  static TickType_t xTimeNow;
  static int i= 1;
  xTimeNow = xTaskGetTickCount();


  Serial.print(i);
  Serial.print("Auto Reload Timer Callback Execution : ");
  Serial.println(xTimeNow);
  i++;
}



void loop(){

  
}
