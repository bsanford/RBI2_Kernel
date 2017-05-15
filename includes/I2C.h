//
// Created by bbot on 12/19/16.
//

#ifndef ARMC_KERNEL_I2C_H
#define ARMC_KERNEL_I2C_H

#define BSC0  0x3F205000UL          /*( 0x3F000000UL + 0x205000 ) The address to the BSC register set 1 */
#define BSC2  0x3F805000UL          /* ( 0x3F000000UL + 0x805000 ) The address to the BSC register set 2 */


/*Broadcom Serial Controller Structure, these
 * registers are used to implement the
 * I2C on the Raspberry PI2
 */

struct bsc_i2c_t{
    volatile int control; /* used to enable interrupts, clear the FIFO, define a R/W operation */
    volatile int  status;  /* status register is used to record activity status, errors and interrupt requests*/
    volatile int  dlen;    /*defines the number of bytes of data to transmit or receive I2C transfer */
    volatile int  slave_addr; /*The bits 6:0 specify the address of the slave address */
    volatile int  data_fifo; /*Used to access FIFO, writes set 16 byte write buffer */
    volatile int  clk_div; /*Used to specify the clock speed */
    volatile int  dat_delay; /*Fine controll over sampling and launching of data*/
    volatile int  clkt; /*Clock stretch time out */
};


/* Control register attributes locations*/
#define C_I2CEN   (15) /*Enable BSC Controller*/
#define C_INT_RX  (10) /*0 No Interrupt on RX condition*/
#define C_INT_TX  (9) /*0 No TXW condition, 1 enables*/
#define C_INT_DN  (8) /*Enable/Disable Interrupt*/
#define C_ST_TFR  (7) /*Starts a new BSC transfer*/
/*bit 6 is reserved*/
#define C_CLEAR   (4) /*Clears the fifo*/
/*bit 3:1 are reserved*/
#define C_READ    (0) /*specifies type of transfer*/



/*Status register attribute locations*/
#define CLKT      (9) /*Clock Stretch Timeout*/
#define ERR       (8) /*Ack Err 0 - No error detected, slave didn't ack address*/
#define RXF       (7) /*0 RX-FIFO not full, 1 RX-FIFO is full*/
#define TXE       (6) /*TXE - FIFO Empty 0 FIFO not empty 1 FIFO is empty*/
#define RXD       (5) /*RXD - 0 FIFO is empty, 1 FIFO contains as least one byte*/
#define TXD       (4) /*TXD - 0 FIFO is full, 1 FIFO Can accept more data*/
#define RXR       (3) /*RXR - 0 FIFO is less than full (read is underway)*/
#define TXW       (2) /*TXW - 0 FIFO is at least full and a write is underway, 1 FIFO
                       *is less then full and a write is under way. Cleared by writing
                       * suffcient data*/
#define DONE      (1) /*Transfer Complete - 1, not complete - 0, cleared by writing 1*/
#define TA        (0) /*Transfer Active  - 1, not active = 0*/

#endif //ARMC_KERNEL_I2C_H
