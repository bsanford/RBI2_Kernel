#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "gpio_api.h"
#include "sys_time.h"
#include "gpio_aux_uart.h"

#define PIN18_ON "GPIO_18_ON"
#define PIN18_OFF "GPIO_18_OFF";


/*Test the gpio functionality using the api */


/*Test function to use the system clock*/
void sleep(uint32_t micros){

  volatile uint32_t curr = (get_sys_clock()->lo_32bits);

  while((get_sys_clock()->lo_32bits - curr) < micros);

}


/**Buffered Read for the UART **/
void uart_buff_read(char *ptr, int len){

char uart_read;
int read_ttl;

for(read_ttl = 0; read_ttl < (len - 3); read_ttl++){
    uart_read =  mini_uart_read();
    ptr[read_ttl] = uart_read;


}

   ptr[len -3] = '\r';
   ptr[len -2] = '\n';
   ptr[len -1] = '\0';
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

    char buffer[100];
    int len = 100;

       //Initialize the Uart for reading and writing;

    init_uart_pins(&pins[14], &pins[15]);

     mini_uart_init(115200, 8);

      printf("HELLO \r\n");
      printf("HELLO \r\n");
      printf("Welcome to the GPIO controller Interface \r\n");

       //if((set_gpio_fnct(&pins[18], OUTPUT)) == -1)
         //return (-1);

        while(1)
    {
        printf("Reading into buffer \r \n");
        uart_buff_read(buffer, len);

        printf("Writing buffer contents to UART \r\n");

        printf("%s", buffer);

        //mini_uart_write(mini_uart_read());

          //sleep(500000);

          // printf("Sending Light signal to pin 18 \r\n");
          // if((send_gpio_sig(&pin_set[18])) == -1) /*Send a 3.3v signal to pin 18*/
             //   return (-1);

        // sleep(500000);
        // printf("Sending clear signal to pin 18 \r\n");
         //if((clear_gpio_sig(&pin_set[18])) == -1) /*Clear the signal form pin 18*/
         // return (-1);
    }

    return (0);
}
