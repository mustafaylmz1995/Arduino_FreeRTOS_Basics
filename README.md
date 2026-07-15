# Arduino_FreeRTOS_Basics

**FreeRTOS Fundamentals on Arduino — 10 Hands-On Projects**

![Arduino](https://img.shields.io/badge/Board-Arduino_Uno-green)
![FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-blue)
![C++](https://img.shields.io/badge/Language-C++-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

---

## 📖 Overview

A complete FreeRTOS tutorial series for Arduino Uno — 10 progressively challenging projects covering every major RTOS concept. Each project is self-contained with documented code, perfect for embedded engineers transitioning from super-loop to real-time operating systems.

---

## 📦 Repository Structure

```
Arduino_FreeRTOS_Basics/
├── Projects/
│   ├── _0GettingStarted/    # First RTOS project
│   ├── _1TaskManagement/    # Task creation & priorities
│   ├── _2QueueManagement/   # Queue communication
│   ├── _3QueuSet/           # Queue sets & polling
│   ├── _4SoftwareTimers/    # Timer callbacks
│   ├── _5Semaphores/        # Binary & counting semaphores
│   ├── _6Mutex/             # Mutual exclusion
│   ├── _7EventGoups/        # Event groups
│   ├── _8Interrupts/        # ISR-safe communication
│   └── _9Preemption/        # Preemptive scheduling demo
├── LICENSE
└── README.md
```

---

## 📚 Project Details

| # | Project | RTOS Concept | Key APIs |
|:-:|:--------|:-------------|:---------|
| **0** | Getting Started | First RTOS app, scheduler start | `xTaskCreate()`, `vTaskStartScheduler()` |
| **1** | Task Management | Task creation, priorities, delays | `xTaskCreate()`, `vTaskDelay()`, `uxTaskPriorityGet()` |
| **2** | Queue Management | Inter-task communication with queues | `xQueueCreate()`, `xQueueSend()`, `xQueueReceive()` |
| **3** | Queue Set | Multiple queue monitoring | `xQueueCreateSet()`, `xQueueSelectFromSet()` |
| **4** | Software Timers | One-shot & periodic timers | `xTimerCreate()`, `xTimerStart()`, `xTimerReset()` |
| **5** | Semaphores | Binary & counting semaphores | `xSemaphoreCreateBinary()`, `xSemaphoreGive/Take()` |
| **6** | Mutex | Priority inheritance, deadlock avoidance | `xSemaphoreCreateMutex()`, priority inversion demo |
| **7** | Event Groups | Multi-event synchronization | `xEventGroupCreate()`, `xEventGroupSetBits()`, `xEventGroupWaitBits()` |
| **8** | Interrupts | ISR-safe queue operations | `xQueueSendFromISR()`, `portYIELD_FROM_ISR()` |
| **9** | Preemption | Preemptive vs cooperative scheduling | `configUSE_PREEMPTION`, priority scheduling demo |

---

## 🛠 Requirements

| Component | Detail |
|:----------|:-------|
| **Board** | Arduino Uno (ATmega328P) |
| **IDE** | Arduino IDE |
| **Library** | Arduino_FreeRTOS (install via Library Manager) |

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
[![GitHub](https://img.shields.io/badge/GitHub-Follow-black)](https://github.com/mustafaylmz1995)
