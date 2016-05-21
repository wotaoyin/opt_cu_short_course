#include<iostream>
#include<thread>
#include<vector>

void increment(int & x, int times){
  for(int i = 0 ; i < times; ++i){
    x=x+1;
  }
}

int main(){
  std::vector<std::thread> threads;
  
  int x = 0;
  int n = 100000;

  int nthreads = 4;
  int thread_times = n/nthreads;

  for(int i=0; i < nthreads; ++i){
    threads.push_back( std::thread(increment, std::ref(x) , thread_times ) );
  }
  // see http://en.cppreference.com/w/cpp/utility/functional/ref for std:ref()

  for(int i=0; i < nthreads; ++i){
    threads[i].join();
  }

  std::cout << x << std::endl;
  
  return 0;
}
