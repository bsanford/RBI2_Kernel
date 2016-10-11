#include "GPIO/gpio.h"


/*Func: Kernel_Main
 *
 * ARGS: r0, r1 and atags. TODO get definitions from arm processor manual
 *
 * Modified from the baremetal tutorials on Valvers.com
 *
 * Entry point for the kernel image,
 * Initializes the GPIO pin and sets it to on waits for some time
 * Sets it to off and waits for some time.
 */

/* GPIO Register set */
//volatile unsigned int* gpio;

/** Simple loop variable */
//volatile unsigned int tim;

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{

    /*Holds the set of GPIO Pins*/


    /*Initialize the gpio pins based on location and*/
   volatile unsigned int tim;

    /* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
   volatile unsigned int *gpio = (unsigned int*)GPIO_BASE;

    /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    gpio[LED_GPFSEL] |= (OUTPUT << LED_GPFBIT);

    /* Never exit as there is no OS to exit to! */
    while(1)
    {
        for(tim = 0; tim < 500000; tim++)
            ;

        /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off
           for plus models )*/
        gpio[LED_GPCLR] = (1 << LED_GPIO_BIT);

        for(tim = 0; tim < 900000; tim++)
            ;

        /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on
           for plus models )*/
        gpio[LED_GPSET] = (1 << LED_GPIO_BIT);
    }
}








