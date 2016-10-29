#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "gpio_api.h"
#include "sys_time.h"
#include "gpio_aux_uart.h"




/*Test the gpio functionality using the api */


/*Test function to use the system clock*/
void sleep(uint32_t micros){

  volatile uint32_t curr = (get_sys_clock()->lo_32bits);

  while((get_sys_clock()->lo_32bits - curr) < micros);

}



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


       //Initialize the Uart for reading and writing;

    init_uart_pins(&pins[14], &pins[15]);

     mini_uart_init(115200, 8);

      printf("HELLO \r\n");
      printf("HELLO \r\n");
      printf("Welcome to the GPIO controller Interface \r\n");

       if((set_gpio_fnct(&pins[18], OUTPUT)) == -1)
         return (-1);

        while(1)
    {
          sleep(500000);

           printf("Sending Light signal to pin 18 \r\n");
           if((send_gpio_sig(&pin_set[18])) == -1) /*Send a 3.3v signal to pin 18*/
                return (-1);

         sleep(500000);
         printf("Sending clear signal to pin 18 \r\n");
      if((clear_gpio_sig(&pin_set[18])) == -1) /*Clear the signal form pin 18*/
           return (-1);
    }

    return (0);
}
