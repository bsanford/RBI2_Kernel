#include"sys_time.h"


#define SYS_CLK_BASE 0x20003000



/*Function: get_sys_clock
 *Return the address to the structure type pointing
 *at the base address of the s
 */
struct sys_time_reg *get_sys_clock(void){

static struct sys_time_reg *system_clock = (struct sys_time_reg *) SYS_CLK_BASE;

return system_clock;

}

