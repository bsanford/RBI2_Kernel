#include "gpio_api.h"
#include "gpio_test.h"




/*Func: Kernel_Main
 *
 * ARGS: r0, r1 and atags. TODO get definitions from arm processor manual
 *
 *Currently just initializes the GPIO in set and runs a GPIO test
 */

void kernel_main(unsigned int r0, unsigned int r1, unsigned int atags)
{

    /*Holds the set of GPIO Pins*/

    if((init_gpio(pin_set, PIN_SET_SIZE)) == -1)
         while(1); //Trap this for now

    /*Initialize the gpio pins based on location and*/
    if((gpio_test(pin_set, PIN_SET_SIZE)) == -1)
        while(1); //trap for now


        while(1);


}








