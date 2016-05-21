#ifndef BARRIER_H
#define BARRIER_H

#include<atomic>
#include<mutex>
   
class spin_barrier{
 public:
  void wait();
  spin_barrier(const spin_barrier&)= delete; //dangerous, so disallow
  spin_barrier(int thread_count);
 private:
  std::atomic<int> counter[2];
  int lock[2];
  int cur_idx;
  int thread_count;

};

/*
void spin_barrier::wait(){

  int idx= cur_idx;
  if(lock[idx]==0){
    lock[idx]=1; //lock the cur_idx
  }
  int waiting= counter[idx].fetch_add(1);
  if( waiting == thread_count-1  ){
    counter[idx].load(0);
    lock[idx]=0;
    cur_idx^=1;
  }
  while(lock[idx]==1);
  //three threads, 2 waiting load lock[idx] checking if it is 1
  //third thread lock[idx]=0
  //we call wait again

}
*/
//spin is barrier is good, if everything is doing one task


#endif
