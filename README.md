# A Raspberry PI 2 Kernel

  >A first attempt at a kernel for the Raspberry Pi 2.
  Initial focus on hardware abstraction for GPIO and UART.

**What the Kernel currently does:**
  >Kernel will initialize the the GPIO peripheral, intialize the UART pins (14 and 15) for reiceve and transmit with no CTS, RTS.
	The system will except commands from a serial connection attached through the mini_uart.
	
	For example;  GPIO_PIN18_ON sent through the UART will initialize GPIO PIN 18 so that it can be set to a HIGH/LO signal
			the call will then set that PIN to a HIGH value on the rail
		      GPIO_PIN18_OFF will clear the signal and set the signal on the rail to LO;

	System is currently limited as the input parser is naive and currently only works for PINS 18,20 and 23.

  
**Requirements:**
  >In order to build the system requires Cmake and the ARM-EABI-NONE GCC cross compiler
  I have been using codeblocks as an IDE which seems to work really well with the build system

**Notes:**
  >Much of this experiment/learning is based off the Bare Metal tutorials on www.valvers.com


**Goals:**
  >Build a single user multiprocess kernel or a really awesome christmas tree controller.
