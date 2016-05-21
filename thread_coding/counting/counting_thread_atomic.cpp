#include<iostream>
#include<thread>
#include<vector>
#include<atomic>

void increment(std::atomic<int> & x, int times){
  for(int i = 0 ; i < times; ++i){
    ++x;
  }
}

// main function
int main(){
  // vector to hold threads
  std::vector<std::thread> threads;
  // shared x, declared as atomic type, initialized as 0
  std::atomic<int> x(0);
  // # of increments
  int n = 1000000000;
  // # of threads
  int nthreads = 4;
  // # of increments per thread
  int thread_n = n/nthreads;
  // spawn n threads
  for(int i=0; i < nthreads; ++i){
    threads.push_back( std::thread(increment, std::ref(x) , thread_n ) );
  }
  // wait for all threads to finish
  for(int i=0; i < nthreads; ++i){
    threads[i].join();
  }
  // display result
  std::cout << x << std::endl;
  return 0;
}
