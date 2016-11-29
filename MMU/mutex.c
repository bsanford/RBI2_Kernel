#include "mutex.h"


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




char init_lock(struct mutex *self){

  self->locked = 0;
  self->islocked = &is_locked;
  self->rmv_mutex_lock = &rmv_mutex_lock;
  self->set_mutex_lock = &set_mutex_lock;
  return self->locked;

}
