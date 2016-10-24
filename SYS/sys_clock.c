#include"sys_time.h"
#define SYS_CLK_BASE 0x4000001c

/*Function: get_sys_clock
 *Return the address to the structure type pointing
 *
 *Singleton just returns the address to the structure
 */

struct sys_time_reg *get_sys_clock(void){

static struct sys_time_reg *system_clock = (struct sys_time_reg *) SYS_CLK_BASE;

return system_clock;

}




