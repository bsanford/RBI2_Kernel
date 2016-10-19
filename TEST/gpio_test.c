#include "gpio_api.h"


/*Test the gpio functionality using the api */



/*Function gpio_test
 *
 *recieves the offset to the pin array and the array size
 *
 *Using this test to coninuously integrate the system from a known good test.
 *Test that is setting GPIO pin 18 to an output
 *and putting 3.3v to the pin on and then off.
 */
int gpio_test(struct gpio_pin *pins, int size)
{
 volatile unsigned int tim;

    /* Assign the address of the GPIO peripheral (Using ARM Physical Address) */
   //volatile unsigned int *gpio = (unsigned int*)GPIO_BASE;

    /* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    //gpio[LED_GPFSEL] |= (OUTPUT << LED_GPFBIT); /*LED_GPFSEL should be in the function, and LED_GPFBIT*

      if((set_gpio_out(&pins[18], 1)) == -1)
            return (-1);

    /* Never exit as there is no OS to exit to! */
    while(1)
    {
        for(tim = 0; tim < 500000; tim++);

        /* Set the LED GPIO pin low ( Turn OK LED on for original Pi, and off
           for plus models )*/
        //gpio[LED_GPCLR] = (1 << LED_GPIO_BIT);
        *(pins[18].gpio_clr_reg) = (1 << pins[18].p_nmb);

        for(tim = 0; tim < 900000; tim++);

        /* Set the LED GPIO pin high ( Turn OK LED off for original Pi, and on
           for plus models )*/
        *(pins[18].gpio_out_reg) = (1 << pins[18].p_nmb);
    }

    return (0);
}
