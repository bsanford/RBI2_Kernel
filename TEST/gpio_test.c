#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "gpio_api.h"
#include "sys_time.h"
#include "gpio_aux_uart.h"

#define PIN18_ON "GPIO_18_ON"
#define PIN18_OFF "GPIO_18_OFF"
#define PIN20_ON "GPIO_20_ON"
#define PIN20_OFF "GPIO_20_OFF"
#define PIN23_ON  "GPIO_23_ON"
#define PIN23_OFF  "GPIO_23_OFF"



/**Naive string matching algorithm to check for a command**/
bool str_match(char *buffer, int buf_len, char *match_string, int mtch_len){

int index;
for(index = 0; index < mtch_len; index++){
  if((buffer[index] != match_string[index]) || index >= buf_len)
    return false;

}
  return true;

}
/*Test the gpio functionality using the api */


/*Test function to use the system clock*/
void sleep(uint32_t micros){

  volatile uint32_t curr = (get_sys_clock()->lo_32bits);

  while((get_sys_clock()->lo_32bits - curr) < micros);

}






/**Function gpio_test
 *
 *recieves the offset to the pin array and the array size
 *
 *Using this test to coninuously integrate the system from a known good test.
 *Test that is setting GPIO pin 18 to an output
 *and putting 3.3v to the pin on and then off.
 */
int gpio_test(struct gpio_pin *pins, int size)
{

    char buffer[30];
    int len = 30;

       //Initialize the Uart for reading and writing;

    init_uart_pins(&pins[14], &pins[15]);

     mini_uart_init(115200, 8);

      printf("HELLO \r \n");
      printf("HELLO \r \n");
      printf("Welcome to the GPIO controller Interface \r\n");


    while(1)
    {
        printf("Please Enter a command-> \r \n");
        uart_buff_read(buffer, len, ';');
        printf("Parsing Command \r\n");


        if(str_match(buffer, len, PIN18_ON, 10)){
           printf("Setting GPIO Pin 18 to on \r \n");
           set_gpio_fnct(&pins[18], OUTPUT);
          // set_gpio_fnct(&pins[20], OUTPUT);
          // set_gpio_fnct(&pins[23], OUTPUT);
           sleep(500000);

           printf("Sending 3.3V signal to GPIO 18 \r \n");
           send_gpio_sig(&pin_set[18]);
           //send_gpio_sig(&pin_set[20]);
           //send_gpio_sig(&pin_set[23]);
           continue;
        }



          if(str_match(buffer, len, PIN20_ON, 10)){
          printf("Command -> %s received \r \n", buffer);

           printf("Setting GPIO Pin 20 to on \r \n");
           set_gpio_fnct(&pins[20], OUTPUT);
          // set_gpio_fnct(&pins[20], OUTPUT);
          // set_gpio_fnct(&pins[23], OUTPUT);
           sleep(500000);

           printf("Sending 3.3V signal to GPIO 20 \r \n");
           send_gpio_sig(&pin_set[20]);
           continue;
        }


          if(str_match(buffer, len, PIN23_ON, 10)){
          printf("Command -> %s received \r \n", buffer);

           printf("Setting GPIO Pin 23 to on \r \n");
           set_gpio_fnct(&pins[23], OUTPUT);
          // set_gpio_fnct(&pins[20], OUTPUT);
          // set_gpio_fnct(&pins[23], OUTPUT);
           sleep(500000);

           printf("Sending 3.3V signal to GPIO 23 \r \n");
           send_gpio_sig(&pin_set[23]);
           continue;
        }



        if (str_match(buffer, len, PIN18_OFF, 11 )){
            printf("Command -> %s received \r \n", buffer);

            printf("Clearning 3.3v signal from pin 18 \r \n");
            sleep(500000);
            clear_gpio_sig(&pin_set[18]);
            continue;
        }


         if (str_match(buffer, len, PIN20_OFF, 11 )){
            printf("Command -> %s received \r \n", buffer);

            printf("Clearning 3.3v signal from pin 20 \r \n");
            sleep(500000);
            clear_gpio_sig(&pin_set[20]);
            continue;
        }

        if (str_match(buffer, len, PIN23_OFF, 11 )){
            printf("Command -> %s received \r \n", buffer);

            printf("Clearning 3.3v signal from pin 23 \r \n");
            sleep(500000);
            clear_gpio_sig(&pin_set[23]);
            continue;
        }

         printf("Unkonwn command -> %s \r \n", buffer);


        //mini_uart_write(mini_uart_read());

       //   sleep(500000);

       //   printf("Sending Light signal to pin 18 \r\n");
       //    if((send_gpio_sig(&pin_set[18])) == -1) /*Send a 3.3v signal to pin 18*/
         //       return (-1);

     //   sleep(500000);
       //  printf("Sending clear signal to pin 18 \r\n");
         //if((clear_gpio_sig(&pin_set[18])) == -1) /*Clear the signal form pin 18*/
          //return (-1);
    }

    return (0);
}
