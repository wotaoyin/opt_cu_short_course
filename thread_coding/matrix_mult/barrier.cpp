#include "barrier.h"


spin_barrier::spin_barrier(int thread_count):thread_count(thread_count){
    counter[0].store(0);counter[1].store(0);
    lock[0]=lock[1]=cur_idx=0;
  }
void spin_barrier::wait(){
  //int idx= cur_idx.load();
  int idx= cur_idx;
  //if the current lock is not locked, lock it
  //if(lock[idx].load() == 0){
  if(lock[idx] == 0){
    //lock[idx].store(1);
    lock[idx] = 1;
  }
  //val is equal to the value of the counter before increment
  int val= counter[idx].fetch_add(1);
  
  //if wait has been called at least thread_count many times
  if( val >= thread_count-1){
    counter[idx].store(0); //counter for current idx has reached its max
    lock[idx]=0;
    cur_idx= cur_idx ^ 1;
    //cur_idx.fetch_xor(1); //replace 0 with 1 and 1 with 0
    //lock[idx].store(0); //deactive lock associated with the old active idx
  }
while(lock[idx] == 1);
//while(lock[idx].load() == 1 ); //spin while waiting for other threads to hit barrier

}
