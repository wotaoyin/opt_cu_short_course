#include<iostream>
#include<thread>
#include<vector>

void increment(int & x, int times){
  for(int i = 0 ; i < times; ++i){
    x=x+1;
  }
}

// main function
int main(){
  // a vector to hold threads
  std::vector<std::thread> threads;
  
  // starting number
  int x = 0;
  // # of increments
  int n = 1000000000;

  // # of threads
  int nthreads = 4;
  // # of increments per thread
  int thread_times = n/nthreads;

  // spawn n threads
  for(int i=0; i < nthreads; ++i){
    threads.push_back( std::thread(increment, std::ref(x) , thread_times ) );
  }
  // see http://en.cppreference.com/w/cpp/utility/functional/ref for std:ref()

  // wait for all n threads to finish
  for(int i=0; i < nthreads; ++i){
    threads[i].join();
  }
 
  // display result
  std::cout << x << std::endl;
  
  return 0;
}
