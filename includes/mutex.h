#ifndef MUTEX_H_INCLUDED
#define MUTEX_H_INCLUDED
#include <stdbool.h>



/** Simple mutex locking mechanism
  * Use case is for the GPIO pin mechanism.
  * This will allow for the UART to be initialized
  * and not clobbered by other users
  *
  * Also can be used to set up and create single or sets of pins
  * For a specific pupose.
  */

struct mutex{
volatile char locked;
bool (* islocked)(struct mutex *self);
char (* set_mutex_lock)(struct mutex *self);
char (* rmv_mutex_lock)(struct mutex *self);
};


extern char init_lock(struct mutex *self);
#endif // MUTEX_H_INCLUDED
