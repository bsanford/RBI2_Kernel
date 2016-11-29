#include "user_cntrl.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "gpio_api.h"

#define PIN18_ON "GPIO_18_ON"
#define PIN18_OFF "GPIO_18_OFF"
#define PIN20_ON "GPIO_20_ON"
#define PIN20_OFF "GPIO_20_OFF"
#define PIN23_ON  "GPIO_23_ON"
#define PIN23_OFF  "GPIO_23_OFF"



static bool str_match(char *buffer, int buf_len, char *match_string, int mtch_len){

int index;
for(index = 0; index < mtch_len; index++){
  if((buffer[index] != match_string[index]) || index >= buf_len)
    return false;

}
  return true;

}






/** gpio_sys calls that will execute
 *  different system calls for each
 *  command recieved by the uart
 *
 * Pre-conditions Uart must be initialized to send data or this will not work
 * correctly.
 *
 * This function is basically some a test code that allows the system to interact with
 * the GPIO facade.
 */
void gpio_sys(void){

    struct gpio_api_funcs *user = init_gpio_api_funcs();

    if((user->init_gpio(pin_set, PIN_SET_SIZE)) == -1)
          while(1); //Trap this for now


    user->init_uart_pins(&pin_set[14], &pin_set[15]); // Need to init the uart before the pins

    user->mini_uart_init(115200, 8);


 char buffer[30];
 int len = 30;
       //Initialize the Uart for reading and writing;
   printf("Welcome to the GPIO controller Interface \r\n");



 while(1){
        printf("Please Enter a command-> \r \n");
        uart_buff_read(buffer, len, ';');
        printf("Command -> %s received \r \n", buffer);

        if(str_match(buffer, len, PIN18_ON, 10)){
           printf("Setting GPIO Pin 18 to on \r \n");
           //set_gpio_pin_on(&pins[18]);
           user->set_gpio_pin_on(&pin_set[18]);
           continue;
        }

          if(str_match(buffer, len, PIN20_ON, 10)){
           printf("Setting GPIO Pin 20 to on \r \n");
           user->set_gpio_pin_on(&pin_set[20]);
           continue;
        }


          if(str_match(buffer, len, PIN23_ON, 10)){
           printf("Setting GPIO Pin 23 to on \r \n");
           user->set_gpio_pin_on(&pin_set[23]);
           continue;
        }


        if (str_match(buffer, len, PIN18_OFF, 11 )){
            printf("Clearning 3.3v signal from pin 18 \r \n");
            user->set_gpio_pin_off(&pin_set[18]);
            continue;
        }


         if (str_match(buffer, len, PIN20_OFF, 11 )){
            printf("Clearning 3.3v signal from pin 20 \r \n");
            user->set_gpio_pin_off(&pin_set[20]);
            continue;
        }

        if (str_match(buffer, len, PIN23_OFF, 11 )){

            printf("Clearning 3.3v signal from pin 23 \r \n");
            user->set_gpio_pin_off(&pin_set[23]);
            continue;
        }

         printf("Unkonwn command -> %s \r \n", buffer);



 }

}
