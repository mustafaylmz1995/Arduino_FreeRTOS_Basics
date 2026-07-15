# Arduino_FreeRTOS_Basics

**FreeRTOS Fundamentals on Arduino — Hands-On Examples**

![Arduino](https://img.shields.io/badge/Board-Arduino_Uno-green)
![FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-blue)
![C++](https://img.shields.io/badge/Language-C++-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## 📖 Overview

A collection of basic FreeRTOS examples for Arduino Uno. Each project demonstrates a fundamental RTOS concept with minimal, focused code — perfect for beginners transitioning from bare-metal to real-time operating systems.

---

## 📦 Projects

| Project | Concept | Description |
|:--------|:--------|:------------|
| Task Creation | `xTaskCreate` | Creating and managing multiple tasks |
| Task Priority | Preemptive scheduling | Understanding task priorities |
| Queue | `xQueueSend` / `xQueueReceive` | Inter-task communication |
| Semaphore | `xSemaphoreGive` / `xSemaphoreTake` | Resource synchronization |
| Mutex | Priority inversion demo | Mutual exclusion |
| Software Timer | `xTimerCreate` | Timer-based callbacks |
| Interrupt | ISR-safe queue | Communication from ISR to task |

---

## 🛠 Hardware

| Component | Detail |
|:----------|:-------|
| **Board** | Arduino Uno (ATmega328P) |
| **RTOS** | FreeRTOS for Arduino |
| **IDE** | Arduino IDE |

---

## 🚀 Quick Start

```cpp
#include <Arduino_FreeRTOS.h>

void TaskBlink(void *pvParameters) {
    pinMode(LED_BUILTIN, OUTPUT);
    while (1) {
        digitalWrite(LED_BUILTIN, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        digitalWrite(LED_BUILTIN, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void setup() {
    xTaskCreate(TaskBlink, "Blink", 128, NULL, 1, NULL);
    vTaskStartScheduler();
}

void loop() { /* empty */ }
```

---

## 📄 License

MIT License.

---

## 📬 Contact

**Mustafa YILMAZ** — Embedded Software Engineer

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue)](https://linkedin.com/in/mustafaylmz1995)
