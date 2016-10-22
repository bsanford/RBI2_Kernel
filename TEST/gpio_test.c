#include "gpio_api.h"
#include "sys_time.h"


/*Test the gpio functionality using the api */


/*Test function to use the system clock*/
void sleep(int micros){

  int curr = *(get_sys_clock()->lo_32bits) + micros;

  while(*(get_sys_clock()->lo_32bits) < curr);

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
 //volatile unsigned int tim;

      if((set_gpio_fnct(&pins[18], 1)) == -1)
            return (-1);

        while(1)
    {
        //for(tim = 0; tim < 500000; tim++);
          sleep(5000000);

           if((send_gpio_sig(&pins[18])) == -1) /*Send a 3.3v signal to pin 18*/
                return (-1);

         // for(tim = 0; tim < 900000; tim++);

         sleep(5000000);

      if((clear_gpio_sig(&pins[18])) == -1) /*Clear the signal form pin 18*/
            return (-1);

    }

    return (0);
}
