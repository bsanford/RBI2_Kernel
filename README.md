# A Raspberry PI 2 Kernel

  A first attempt at a kernel for the Raspberry Pi 2.
  Initial focus on hardware abstraction for GPIO and UART.

**What the Kernel currently does**
  This will blink an LED on pin 18 of the GPIO rail
  
**Requirements**
  In order to build the system requires cmake and the ARM-EABI-NONE GCC cross compiler
  I have been using codeblocks as an IDE which seems to work really well with the build system

**Notes**
  Much of this experiment/learning is based off the Bare Metal tutorials on www.valvers.com


**Goals**
  Build a single user multiprocess kernel
