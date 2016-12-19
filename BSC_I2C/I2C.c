#include "I2C.h"
//
// Created by bbot on 12/16/16.
//

/** Implementation of the Broadcom Serial Controller
 *  Which is Philips I2C compliant bus controller
 */




/** Function get_bsc0
 * @brief  returns the static address of bsc_i2c structure BSC controller 0
 *
 * @return bsc_i2c_t *
 */
struct bsc_i2c_t * get_bsc0(void){

  static struct bsc_i2c_t *bsc0 = (struct bsc_i2c_t *) (BSC0);
  return bsc0;

}


/** Function get_bsc1
 * @brief returns the static address of the bsc_i2C structure for BSC controller 1
 * @return bsc_i2C_t *
 */

struct bsc_i2c_t * get_bsc1(void){

  static struct bsc_i2c_t  *bsc1 = (struct bsc_i2c_t *) (BSC1);
  return bsc1;

}






/**Function: set_clock_speed
 * @brief Sets the I2C clock speed
 *
 * @arg clk_spd of the device to write to
 */
void set_clock_speed(void){


}



/**Function get_dlen
 * @brief gets the dlen value from the register
 *        how much data is to be read from the register
 *
 * @return returns the short dlen value
 */

short get_dlen(void) {

  return 0;
}


/**Function set_dlen
 * @brief writes the dlen value to the register ie
 *        how much data will be written on to the i2C line
 *
 * @return returns nothing
 */
void set_dlen(int length){


}







