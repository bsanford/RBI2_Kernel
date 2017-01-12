#  Design Patterns on an Embedded System

  >A baremetal system implementation targeting Software design patterns for the Raspberry PI 2 v1.1 hardware.

**Design Patterns**
   >Facade: 
	     The GPIO system api utilizes a facade so all entry to the GPIO sub system requires the use of the singleton API
	     The api is a structure with a set of function pointers to all available sub system calls. There is a get api function call
	     that initializes all the addresses to the functions and returns the singleton address
  
   >Proxy: 
	     The gpio sub system initialization is controlled through a proxy. Any process that calls the initilization of the
	     GPIO sub system with first be sent through the proxy, the proxy will determine if the the subsystem has been initialized and
	     return the start address of the GPIO pin peripheral set.

   >State:   The GPIO pin set structure has a mutex structure which controls the state of each pin. The pin is either in state locked or state unlocked.


   >Singleton: 
		The mini UART peripheral according to the BCM2835/6 are built on a set of registers which start at a certain base address.
	        The implementation wraps a structure around the hardware registers the driver for the mini uart makes a call
		to a function which returns the singleton start address of the hardware registers

  >Iterator:
		A general iterator was implemented to control the the iteration over the set of GPIO pins. This will allow for finer grain
		control over the interation of the GPIO sub system registers.
		 
 


**What the Kernel currently does:**

    Kernel will initialize the the GPIO peripheral, intialize the UART pins (14 and 15) for reiceve and transmit with no CTS, RTS.
	The system will except commands from a serial connection attached through the mini_uart.

	GPIO pins 18 20 and 23 can be toggled between high and low by sending serial commands through the UART the command
	 delimeter is the ';' character.

                 The system currently supports the following commands
                 GPIO18_ON;
                 GPIO18_OFF;
                 GPIO20_ON;
                 GPIO20_OFF;
                 GPIO23_ON;
                 GPIO23_OFF;

	
	For example  GPIO18_ON; sent through the UART will initialize GPIO PIN 18 so that it can be set to a HIGH/LO signal
			     the call will then set that PIN to a HIGH value on the rail
		         GPIO18_OFF; will clear the signal and set the signal on the rail to LO;

		         The parser recognizes ; as the delimiter or it as an upper bound of 30 characters that can be received
		         through the UART.

	System is currently limited as the input parser is naive and currently only works for PINS 18,20 and 23.

	GPIO PIN 21 is set up as a physical IRQ line for a soft reset. This uses a low level detect event which
	            sends a signal to the IRQ controller. On initialization the pin is set to high and can be
	            pulled down by jumping to ground or adding a switch ect.


**Requirements:**
  >In order to build the system requires Cmake and the ARM-EABI-NONE GCC cross compiler
  I have been using CLION as an IDE which seems to work really well with the build system

**Notes:**
  >www.valvers.com has great tutorials on the compiler and build system and using the broadcom datasheets.





**Goals:**
  >Working on rolling a weather station, I would like to launch it in a weather balloon and have
   one of the higher power xbee modules communicate sensor data to a ground station.
