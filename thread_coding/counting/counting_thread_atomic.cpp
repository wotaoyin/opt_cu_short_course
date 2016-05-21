#include<iostream>
#include<thread>
#include<vector>
#include<atomic>

void increment(std::atomic<int> & x, int times){
  for(int i = 0 ; i < times; ++i){
    ++x;
  }
}

int main(){
  std::vector<std::thread> threads;
  std::atomic<int> x(0);
  int n = 100000;
  int nthreads = 4;
  int thread_n = n/nthreads;
  for(int i=0; i < nthreads; ++i){
    threads.push_back( std::thread(increment, std::ref(x) , thread_n ) );
  }
  for(int i=0; i < nthreads; ++i){
    threads[i].join();
  }
  std::cout << x << std::endl;
  return 0;
}
