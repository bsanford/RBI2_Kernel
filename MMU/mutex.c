#include "mutex.h"





char init_lock(struct mutex *self){

  self->locked = 0;
  return self->locked;

}




char set_mutex_lock(struct mutex *self){

  self->locked = 1;
  return self->locked;

}




char rmv_mutex_lock(struct mutex *self){

  self->locked = 0;

  return self->locked;

}



bool is_locked(struct mutex *self){

  if(self->locked == 1)
        return true;

  return false;
}


