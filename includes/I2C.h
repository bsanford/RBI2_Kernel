//
// Created by bbot on 12/19/16.
//

#ifndef ARMC_KERNEL_I2C_H
#define ARMC_KERNEL_I2C_H

#define BSC0  0x3F205000UL          /*( 0x3F000000UL + 0x205000 ) The address to the BSC register set 1 */
#define BSC1  0x3F805000UL          /* ( 0x3F000000UL + 0x805000 ) The address to the BSC register set 2 */


/*Broadcom Serial Controller Structure, these
 * registers are used to implement the
 * I2C on the Raspberry PI2
 */

struct bsc_i2c_t{
    volatile int  control; /* used to enable interrupts, clear the FIFO, define a R/W operation */
    volatile int  status;  /* status register is used to record activity status, errors and interrupt requests*/
    volatile int  dlen;    /*defines the number of bytes of data to transmit or receive I2C transfer */
    volatile int  slave_addr; /*The bits 6:0 specify the address of the slave address */
    volatile int  data_fifo; /*Used to access FIFO, writes set 16 byte write buffer */
    volatile int  clk_div; /*Used to specify the clock speed */
    volatile int  data_del; /*Fine controll over sampling and launching of data*/
};




#endif //ARMC_KERNEL_I2C_H
