#include "gpio.h"
#include "gpio_test.h"


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

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{

    /*Holds the set of GPIO Pins*/

    if((init_gpio(pin_set, PIN_SET_SIZE)) == -1) //Initialization test, needs to move to a controller
         while(1); //Trap this for now

    /*Initialize the gpio pins based on location and*/
    if((gpio_test(pin_set, PIN_SET_SIZE)) == -1)
         while(1); //trap for now

}








