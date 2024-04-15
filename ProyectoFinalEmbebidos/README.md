# FreeRTOS Multitasking


With the help of FreeRTOS and the STM32F103 microcontroller, we developed an embedded system application that simulates a vehicle transmission control. The hardware implementation consisted of two potentiometers to emulate the pedals, a two bit deepswitch to emulate the gearbox options, and led to show the intensity of the output and the LCD display to show the current velocity in km/hr. The software modules were mainly built with the help of tasks and queues. We wrote five tasks each addressing the queues inputs and outputs needed to fulfill their needs.

Link to a video of the solution running on the STM32F1038CT6 hardware.
[https://drive.google.com/file/d/1cuUTk8nihORNWoZ1-8J9fjZgoEqFkQd h/view?usp=sharing
](https://drive.google.com/file/d/1cuUTk8nihORNWoZ1-8J9fjZgoEqFkQdh/view)
