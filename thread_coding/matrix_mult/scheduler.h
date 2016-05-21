#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<atomic>
#include<functional>
#include<vector>
#include<iostream>

class scheduler{
 public:
  scheduler( std::vector< std::function<void()> >& v ){
    std::swap(tasks,v);
    current_task.store(0);
    std::cout << "number of tasks is " << tasks.size() <<std::endl;
  };
  bool request_task(std::function<void()> &);
 private:
  std::vector< std::function<void()> > tasks;
  std::atomic<int> current_task;
 
};


bool scheduler::request_task( std::function<void()>& received_task){
  int idx=current_task.fetch_add(1); //uniqueness
  if(idx < tasks.size()){
    received_task=tasks[idx];
    return true;
  }
  return false;
}

/*
void worker(scheduler* s){
  std::function<void()> funky;
  while(s->request_task(funky)){
    funky();
  }
}
*/



#endif
