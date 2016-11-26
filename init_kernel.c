#include "gpio_api.h"
#include "user_cntrl.h"





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

     init_uart_pins(&pin_set[14], &pin_set[15]);
     mini_uart_init(115200, 8);

    /*Initialize the gpio pins based on location and*/
   // if((gpio_test(pin_set, PIN_SET_SIZE)) == -1)

      gpio_sys(pin_set, PIN_SET_SIZE);

        while(1); //trap for now


        while(1); /**Can't exit from here we have nothing to exit too **/


}








