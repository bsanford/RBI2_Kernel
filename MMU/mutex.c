#include "mutex.h"


/**Function set_mutex_lock
 *
 * set_mutex_lock - sets the lock
 * on the specified mutex structure
 */
char set_mutex_lock(struct mutex *self){

  self->locked = 1;
  return self->locked;

}


/**Function rmv_mutex_lock
 *
 * removes the lock on the specified
 * lock structure
 */

char rmv_mutex_lock(struct mutex *self){

  self->locked = 0;

  return self->locked;

}


/** Function is_locked
 *
 *  Tests the lock structure for its
 *  lock status
 */

bool is_locked(struct mutex *self){

  if(self->locked == 1)
        return true;

  return false;
}


/** Function: init_lock
 *
 *  passes lock structure to self and initializes
 *  the addresses of the function pointers
 *  and sets the initial lock value to 0
 */

char init_lock(struct mutex *self){

  self->locked = 0;
  self->islocked = &is_locked;
  self->rmv_mutex_lock = &rmv_mutex_lock;
  self->set_mutex_lock = &set_mutex_lock;
  return self->locked;

}
